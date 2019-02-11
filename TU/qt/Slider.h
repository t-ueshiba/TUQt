/*
 *  \file	Slider.h
 */
#ifndef TU_QT_SLIDER_H
#define TU_QT_SLIDER_H

#include <QSlider>
#include <QDoubleSpinBox>

namespace TU
{
namespace qt
{
/************************************************************************
*  class Slider							*
************************************************************************/
class Slider : public QWidget
{
    Q_OBJECT

  private:
    using sig_p	= void (QDoubleSpinBox::*)(double);

  public:
		Slider(QWidget* parent)					;

    double	value()						const	;
    void	setValue(double val)					;
    void	setRange(double min, double max, double step)		;

  Q_SIGNALS:
    void	valueChanged(double val)				;

  private:
    void	onSliderValueChanged(int sliderVal)			;
    void	onSpinBoxValueChanged(double val)			;

  private:
    double	sliderValToVal(int sliderVal)			const	;
    int		valToSliderVal(double val)			const	;

  private:
    QSlider*		const	_slider;
    QDoubleSpinBox*	const	_spinBox;
};

}	// namespace qt
}	// namespace TU
#endif	// !TU_QT_SLIDER_H
