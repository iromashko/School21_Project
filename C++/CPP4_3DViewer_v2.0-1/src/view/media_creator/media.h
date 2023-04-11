#ifndef MEDIA_H
#define MEDIA_H

#include <QMainWindow>

#include "../QtGifImage-master/src/gifimage/qgifimage.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class Media : public QMainWindow {
  Q_OBJECT
 public:
  explicit Media(Ui::MainWindow *ui, QWidget *parent = nullptr);
  ~Media();

  void SavePicture();
  void SaveGif();
  QVector<QImage> mas_image;

 private slots:

  void CreateScreen();
  void CreateGif();

 private:
  Ui::MainWindow *ui;
  QTimer *timer_for_gif{};
  double time{};
};

#endif  // MEDIA_H
