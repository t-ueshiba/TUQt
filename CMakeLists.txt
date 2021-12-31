cmake_minimum_required(VERSION 2.4)
project(TUQt)

enable_language(CXX)
set(CMAKE_CXX_STANDARD		14)
set(CMAKE_CXX_STANDARD_REQUIRED	ON)
set(CMAKE_CXX_EXTENSIONS	OFF)
set(CMAKE_CXX_FLAGS_RELEASE	"-Wall -O3")
set(CMAKE_CXX_FLAGS_DEBUG	"-g")
set(CMAKE_BUILD_TYPE		Release)

if(APPLE)
  set(MACOSX_RPATH TRUE)
endif()

find_package(Qt5Widgets REQUIRED)
find_package(Boost REQUIRED)

include_directories(
    ${PROJECT_SOURCE_SIR}
    ${CMAKE_INSTALL_PREFIX}/include
    ${Boost_INCLUDE_DIRS}
    ${Qt5Widgets_INCLUDE_DIRS}
)

link_directories(${CMAKE_INSTALL_PREFIX}/lib)

file(GLOB sources *.cc)

set(moc_headers TU/qt/Slider.h)
set(moc_sources "")
QT5_WRAP_CPP(moc_sources ${moc_headers})

add_library(${PROJECT_NAME} SHARED ${sources} ${moc_sources})
target_link_libraries(${PROJECT_NAME} TUTools ${Qt5Widgets_LIBRARIES})

install(TARGETS ${PROJECT_NAME} LIBRARY DESTINATION lib)

add_subdirectory(TU)
