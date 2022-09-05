#pragma once

#include <QtCore/QObject>
#include <QtCore/QTimer>
#include <cstddef>
#include <qobject.h>
#include <qobjectdefs.h>

class SlideShow : public QObject {

Q_OBJECT

public:
  SlideShow(QObject *parent = nullptr);
  ~SlideShow() override = default;

signals:

  void imageChanged(QString imgSrc);

private slots:
  void nextImage();

private:
  QTimer timer_;
  QList<QString> imageSources_;
  int currentIdx_{0};
};
