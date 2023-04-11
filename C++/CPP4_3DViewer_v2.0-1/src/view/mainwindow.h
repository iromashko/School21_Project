#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include <QMovie>

#include "../controller/controller.h"
#include "gl_widget/glviewer.h"
#include "media_creator/media.h"
#include "settings/save_settings.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow, public s21::Observer {
  Q_OBJECT

 public:
  MainWindow(QWidget *parent = nullptr);
  ~MainWindow();

 private slots:

  void on_openFile_clicked();

  //_______________OBSERVER_________________
  void update() override;
  //________________________________________

  //_________AFFINE_TRANSFORMATIONS_________
  void on_dx_textChanged();
  void on_dy_textChanged();
  void on_dz_textChanged();
  void on_rdx_textChanged();
  void on_rdy_textChanged();
  void on_rdz_textChanged();
  void on_modelScale_textChanged();
  //________________________________________

  //_________OPTIMIZE_SCALE_________________
  void on_optimization_clicked();
  void on_doubleSpinBox_Scale_valueChanged(double valueScale);
  //________________________________________

  //_________PAINT__________________________
  void on_color_clicked();
  void on_comboBox_point_form_currentIndexChanged(int index);
  void on_spinBox_point_size_valueChanged(int value);
  void on_spinBox_line_width_valueChanged(int value);
  void on_comboBox_line_form_currentIndexChanged(int index);
  //________________________________________

  //______________PROJECTION________________
  void on_radioButton_frustum_clicked(bool checked);
  void on_radioButton_ortho_clicked();
  //________________________________________

  //_________SAVE_AND_LOAD_SETTINGS_________
  void on_save_settings_clicked();
  void on_load_setting_clicked();
  //________________________________________

  //_________GIF_PHOTO_SAVE_________________
  void on_Pthoto_clicked();
  void on_stop_and_save_GIF_clicked();
  //________________________________________

 private:
  Ui::MainWindow *ui;
  s21::Controller controller_;

  //_________OPTIMIZE_SCALE_________________
  void wheelEvent(QWheelEvent *event) override;
  //________________________________________

  //_________SAVE_AND_LOAD_SETTINGS_________
  SaveSettings save_settings_;
  void save_settings();
  void load_settings();
  void SaveSettingsSignal(Ui::MainWindow *ui) {
    save_settings_.SaveSettingsUI(ui);
  };
  void LoadSettingsSignal(Ui::MainWindow *ui) {
    save_settings_.LoadSettingsUI(ui);
  };
  //________________________________________

  //_________GIF_PHOTO_SAVE_________________
  Media *picture_;
  //________________________________________
};
#endif  // MAINWINDOW_H
