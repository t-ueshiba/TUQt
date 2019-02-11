/*!
 *  \file	ImageView.h
 */
#ifndef TU_QT_IMAGEVIEW_H
#define TU_QT_IMAGEVIEW_H

#include <QGraphicsView>
#include <QImage>
#include <QMenu>
#include "TU/Image++.h"

namespace TU
{
namespace qt
{
/************************************************************************
*  class ImageView							*
************************************************************************/
class ImageView : public QGraphicsView
{
  public:
    ImageView(QWidget* parent)						;

    template <class T>
    ImageView&	operator <<(const Image<T>& image)			;
    template <class T>
    void	display(const T* data, size_t width, size_t height)	;

  private:
    void	paintEvent(QPaintEvent* event)				;
    void	setScale(qreal scale)					;
    void	showContextMenu(const QPoint& p)			;

  private:
    QVector<RGB>	_rgb;
    QImage		_qimage;
    QVector<QRgb>	_colors;
    QVector<QRgb>	_colorsF;
    QMenu*	const	_menu;
    bool		_fit;
    qreal		_scale;
};

template <class T> inline ImageView&
ImageView::operator <<(const Image<T>& image)
{
    display(image.data(), image.width(), image.height());
    return *this;
}

template <class T> inline void
ImageView::display(const T* data, size_t width, size_t height)
{
    constexpr auto	N = iterator_value<pixel_iterator<const T*> >::npixels;
    const auto		npixels = width * height;

    _rgb.resize(npixels);
    std::copy_n(make_pixel_iterator(data), npixels/N,
		make_pixel_iterator(_rgb.data()));
    _qimage = QImage(reinterpret_cast<const uchar*>(_rgb.data()),
		     width, height, width*sizeof(RGB), QImage::Format_RGB888);
    _qimage.setColorTable(_colors);
}

template <> inline void
ImageView::display(const uint8_t* data, size_t width, size_t height)
{
    _qimage = QImage(data, width, height,
		     width*sizeof(uint8_t), QImage::Format_Indexed8);
    _qimage.setColorTable(_colors);
}

template <> inline void
ImageView::display(const RGB* data, size_t width, size_t height)
{
    _qimage = QImage(reinterpret_cast<const uchar*>(data),
		     width, height, width*sizeof(RGB), QImage::Format_RGB888);
    _qimage.setColorTable(_colors);
}

}	// namespace qt
}	// namespace TU
#endif	// !TU_QT_IMAGEVIEW_H
