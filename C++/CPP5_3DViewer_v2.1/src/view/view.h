#ifndef VIEW_H
#define VIEW_H

#include <QColorDialog>
#include <QMainWindow>

#include "../controller/viewercontroller.h"

class QLabel;
class QSettings;

namespace Ui {
class View;
}

class View : public QMainWindow {
  Q_OBJECT

 public:
  explicit View(QWidget *parent = nullptr);
  ~View();

  void SaveSettings();
  void ReadSettings();
  void SaveDefaultSettings();

 private slots:
  void ShadingRadio();
  void on_horizontalSlider_lightPower_valueChanged(int value);
  void on_horizontalSlider_lightPosX_valueChanged(int value);
  void on_horizontalSlider_lightPosY_valueChanged(int value);
  void on_horizontalSlider_lightPosZ_valueChanged(int value);
  void on_pushButton_light_reset_clicked();
  void on_pushButton_load_model_clicked();
  void on_pushButton_perspective_clicked();
  void on_pushButton_orthographic_clicked();
  void on_horizontalSlider_rotate_x_valueChanged(int value);
  void on_horizontalSlider_rotate_y_valueChanged(int value);
  void on_horizontalSlider_rotate_z_valueChanged(int value);
  void on_doubleSpinBox_xMove_valueChanged(double arg1);
  void on_doubleSpinBox_yMove_valueChanged(double arg1);
  void on_doubleSpinBox_zMove_valueChanged(double arg1);
  void on_pushButton_load_texture_clicked();
  void on_pushButton_create_image_clicked();
  void on_pushButton_create_gif_clicked();
  void on_pushButton_reset_texture_clicked();
  void on_pushButton_light_color_clicked();
  void on_pushButton_create_gif_rotate_clicked();
  void on_doubleSpinBox_Scale_valueChanged(double arg1);
  void on_lineEdit_stepScale_textChanged(const QString &arg1);
  void on_lineEdit_stepMove_textChanged(const QString &arg1);
  void on_pushButtonZeroMovement_clicked();
  void on_lineEdit_stepRotate_textChanged(const QString &arg1);
  void on_pushButton_zeroRotate_clicked();
  void on_pushButtonZeroScale_clicked();
  void on_doubleSpinBox_lineWidth_valueChanged(double arg1);
  void on_doubleSpinBox_pointSize_valueChanged(double arg1);
  void on_pushButton_selectColorLines_clicked();
  void on_pushButton_selectColorPoints_clicked();
  void on_comboBox_typesPoints_currentIndexChanged(int index);
  void on_comboBox_typesLines_currentIndexChanged(int index);
  void on_pushButton_selectColorBackground_clicked();
  void on_pushButtonZeroSettings_clicked();

 private:
  Ui::View *ui;

  s21::ViewerController _controller;

  QRect _geometry;
  QSettings *_settings;

  void LockUi();
  void UnlockUi();
  void ResetSpinBoxesAndSliders();
  void SetModelDataToLabels(QString path);
  void SetColorToLabel(QLabel *label, s21::Vec3 color);

  bool _texture_loaded{false};
  bool _is_texture_view{false};

 protected:
  void closeEvent(QCloseEvent *event) override;
};

#endif  // VIEW_H
