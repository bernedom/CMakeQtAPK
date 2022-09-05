#include "slideshow.h"
#include <QObject>

SlideShow::SlideShow(QObject *parent) : QObject() {
  imageSources_.push_back("/sunset0.jpg");
  imageSources_.push_back("/sunset1.jpg");
  imageSources_.push_back("/sunset2.jpg");
  timer_.setInterval(1000);
  timer_.setSingleShot(false);
  timer_.start();

  connect(&timer_, &QTimer::timeout, this, &SlideShow::nextImage);
}

void SlideShow::nextImage() {
  currentIdx_++;
  emit imageChanged(imageSources_[currentIdx_ % imageSources_.size()]);
  
}