#include "media.h"

#include "ui_mainwindow.h"

Media::Media(Ui::MainWindow *ui, QWidget *parent)
    : QMainWindow{parent}, ui(ui) {
  timer_for_gif = new QTimer();  // parent must be null
  connect(timer_for_gif, &QTimer::timeout, this, &Media::CreateScreen);
}

Media::~Media() { delete timer_for_gif; }

void Media::SavePicture() {
  QFileDialog dialog_photo(this);
  QString name_photo = dialog_photo.getSaveFileName(
      this, "Save as...", "photo", "BMP (*.bmp);; JPEG (*.jpeg)");
  ui->widget->grabFramebuffer().save(name_photo);
}

void Media::SaveGif() { timer_for_gif->start(100); }

void Media::CreateGif() {
  QString fileName = QFileDialog::getSaveFileName(
      this, tr("Save screenshot"), "",
      tr("GIF screenshot (*.gif);;GIF screenshot (*.gif)"));
  QGifImage gif(QSize(640, 480));

  gif.setDefaultTransparentColor(Qt::black);
  gif.setDefaultDelay(100);

  for (QVector<QImage>::Iterator img = mas_image.begin();
       img != mas_image.end(); ++img) {
    gif.addFrame(*img);
  }
  gif.save(fileName);
  mas_image.clear();
  ui->label_Timer_GIF->clear();
  time = 0.0;
}

void Media::CreateScreen() {
  if (time <= 4.9) {
    mas_image.push_back(ui->widget->grabFramebuffer());
    time += 0.1;
    ui->label_Timer_GIF->setText(QString::number(time));
  } else {
    CreateGif();
    timer_for_gif->stop();
  }
}
