#include "view.h"

#include <unistd.h>

#include <QCloseEvent>
#include <QFileDialog>
#include <QMessageBox>
#include <QSettings>

#include "ui_view.h"

View::View(QWidget *parent) : QMainWindow(parent), ui(new Ui::View) {
  ui->setupUi(this);
  ui->flat_shading->click();
  _controller.SetScene(ui->scene);

  connect(ui->flat_shading, SIGNAL(clicked()), this, SLOT(ShadingRadio()));
  connect(ui->guro_shading, SIGNAL(clicked()), this, SLOT(ShadingRadio()));
  connect(ui->phong_shading, SIGNAL(clicked()), this, SLOT(ShadingRadio()));

  LockUi();
  on_pushButtonZeroSettings_clicked();

  _geometry = QRect(0, 0, 1160, 764);
  _settings = new QSettings("Tonijerl", "3DViewer", this);
  ReadSettings();
}

View::~View() { delete ui; }

void View::SaveSettings() {
  _settings->setValue("geometry", geometry());
  _settings->setValue("line_width", ui->doubleSpinBox_lineWidth->value());
  _settings->setValue("point_size", ui->doubleSpinBox_pointSize->value());
  _settings->setValue("line_type", ui->comboBox_typesLines->currentIndex());
  _settings->setValue("point_type", ui->comboBox_typesPoints->currentIndex());
  _settings->setValue("move_step", ui->lineEdit_stepMove->text().toDouble());
  _settings->setValue("rotate_step",
                      ui->lineEdit_stepRotate->text().toDouble());
  _settings->setValue("scale_step", ui->lineEdit_stepScale->text().toDouble());
  _settings->setValue("line_color_x", _controller.GetColorLine().x);
  _settings->setValue("line_color_y", _controller.GetColorLine().y);
  _settings->setValue("line_color_z", _controller.GetColorLine().z);
  _settings->setValue("point_color_x", _controller.GetColorPoint().x);
  _settings->setValue("point_color_y", _controller.GetColorPoint().y);
  _settings->setValue("point_color_z", _controller.GetColorPoint().z);
  _settings->setValue("background_color_x", _controller.GetColorBackground().x);
  _settings->setValue("background_color_y", _controller.GetColorBackground().y);
  _settings->setValue("background_color_z", _controller.GetColorBackground().z);
}

void View::ReadSettings() {
  setGeometry(_settings->value("geometry", QRect(0, 0, 1160, 764)).toRect());

  ui->doubleSpinBox_lineWidth->setValue(
      _settings->value("line_width", 1.0).toDouble());
  _controller.SetLineWidth(ui->doubleSpinBox_lineWidth->value());
  ui->doubleSpinBox_pointSize->setValue(
      _settings->value("point_size", 2.0).toDouble());
  _controller.SetPointSize(ui->doubleSpinBox_pointSize->value());
  ui->comboBox_typesLines->setCurrentIndex(
      _settings->value("line_type", 0).toInt());
  _controller.SetLineType(ui->comboBox_typesLines->currentIndex());
  ui->comboBox_typesPoints->setCurrentIndex(
      _settings->value("point_type", 0).toInt());
  _controller.SetPointType(ui->comboBox_typesPoints->currentIndex());

  ui->lineEdit_stepMove->setText(_settings->value("move_step", 0.1).toString());
  ui->lineEdit_stepRotate->setText(
      _settings->value("rotate_step", 1).toString());
  ui->lineEdit_stepScale->setText(
      _settings->value("scale_step", 0.05).toString());

  {
    s21::Vec3 color(_settings->value("line_color_x", 1.f).toFloat(),
                    _settings->value("line_color_y", 0.f).toFloat(),
                    _settings->value("line_color_z", 0.f).toFloat());
    _controller.SetLineColor(color);
    SetColorToLabel(ui->label_colorLines, color);
  }
  {
    s21::Vec3 color(_settings->value("point_color_x", 0.f).toFloat(),
                    _settings->value("point_color_y", 1.f).toFloat(),
                    _settings->value("point_color_z", 0.f).toFloat());
    _controller.SetPointColor(color);
    SetColorToLabel(ui->label_colorPoints, color);
  }
  {
    s21::Vec3 color(_settings->value("background_color_x", .5f).toFloat(),
                    _settings->value("background_color_y", .5f).toFloat(),
                    _settings->value("background_color_z", .5f).toFloat());
    _controller.SetBackgroundColor(color);
    SetColorToLabel(ui->label_colorBackgournd, color);
  }
}

void View::SaveDefaultSettings() {
  _settings->setValue("geometry", QRect(0, 0, 1160, 764));
  _settings->setValue("line_width", 1.0);
  _settings->setValue("point_size", 2.0);
  _settings->setValue("line_type", 0);
  _settings->setValue("point_type", 0);
  _settings->setValue("move_step", 0.1);
  _settings->setValue("rotate_step", 1);
  _settings->setValue("scale_step", 0.05);
  _settings->setValue("line_color_x", 1.f);
  _settings->setValue("line_color_y", 0.f);
  _settings->setValue("line_color_z", 0.f);
  _settings->setValue("point_color_x", 0.f);
  _settings->setValue("point_color_y", 1.f);
  _settings->setValue("point_color_z", 0.f);
  _settings->setValue("background_color_x", .5f);
  _settings->setValue("background_color_y", .5f);
  _settings->setValue("background_color_z", .5f);
}

void View::ShadingRadio() {
  if (ui->flat_shading->isChecked()) {
    _controller.ChangeShadow(s21::Shading::flatShading);
  } else if (ui->guro_shading->isChecked()) {
    _controller.ChangeShadow(s21::Shading::guroShading);
  } else if (ui->phong_shading->isChecked()) {
    _controller.ChangeShadow(s21::Shading::phongShading);
  }
}

void View::on_horizontalSlider_lightPower_valueChanged(int value) {
  _controller.ChangeSceneLightPower(value);
}

void View::on_horizontalSlider_lightPosX_valueChanged(int value) {
  _controller.ChangeSceneLightPos(value, true, false, false);
}

void View::on_horizontalSlider_lightPosY_valueChanged(int value) {
  _controller.ChangeSceneLightPos(value, false, true, false);
}

void View::on_horizontalSlider_lightPosZ_valueChanged(int value) {
  _controller.ChangeSceneLightPos(value, false, false, true);
}

void View::on_pushButton_light_reset_clicked() {
  ui->horizontalSlider_lightPosX->setValue(0);
  ui->horizontalSlider_lightPosY->setValue(0);
  ui->horizontalSlider_lightPosZ->setValue(0);
  ui->horizontalSlider_lightPower->setValue(100);
}

void View::on_pushButton_load_model_clicked() {
  QString path =
      QFileDialog::getOpenFileName(0, "Select .obj file", "/Users/", "*.obj");
  if (!path.isEmpty()) {
    UnlockUi();
    ResetSpinBoxesAndSliders();
    _controller.Reset();
    _controller.LoadObjModelToScene(path.toStdString());
    SetModelDataToLabels(path);
  }
}

void View::on_pushButton_perspective_clicked() {
  _controller.ChangePerspective(true);
}

void View::on_pushButton_orthographic_clicked() {
  _controller.ChangePerspective(false);
}

void View::on_pushButton_load_texture_clicked() {
  QString path = QFileDialog::getOpenFileName(
      0, "Select .texture file", "/Users/", tr("Images(*.png *.jpg *.jpeg)"));
  if (!path.isEmpty()) {
    _texture_loaded = true;
    _controller.AddTexture(path.toStdString());
  } else {
    _texture_loaded = false;
  }
}

void View::on_pushButton_create_image_clicked() { _controller.RecordImage(); }

void View::on_pushButton_create_gif_clicked() { _controller.RecordGif(); }

void View::on_pushButton_create_gif_rotate_clicked() {
  _controller.RecordGifRotate();
}

void View::on_doubleSpinBox_xMove_valueChanged(double arg1) {
  _controller.ChangeMove(arg1, true);
}

void View::on_doubleSpinBox_yMove_valueChanged(double arg1) {
  _controller.ChangeMove(arg1, false, true);
}

void View::on_doubleSpinBox_zMove_valueChanged(double arg1) {
  _controller.ChangeMove(arg1, false, false, true);
}

void View::on_pushButton_reset_texture_clicked() {
  _controller.ResetTexture();
  if (ui->pushButton_reset_texture->text() == "Наложить текстуру") {
    _is_texture_view = true;
    ui->pushButton_reset_texture->setText("Убрать текстуру");
  } else {
    _is_texture_view = false;
    ui->pushButton_reset_texture->setText("Наложить текстуру");
  }
}

void View::on_horizontalSlider_rotate_x_valueChanged(int value) {
  _controller.ChangeRotate(value, true);
}

void View::on_horizontalSlider_rotate_y_valueChanged(int value) {
  _controller.ChangeRotate(value, false, true);
}

void View::on_horizontalSlider_rotate_z_valueChanged(int value) {
  _controller.ChangeRotate(value, false, false, true);
}

void View::on_pushButton_light_color_clicked() {
  _controller.ChangeShadowColor(QColorDialog::getColor(Qt::green, this));
}

void View::on_doubleSpinBox_Scale_valueChanged(double arg1) {
  _controller.ChangeScale(arg1);
}

void View::ResetSpinBoxesAndSliders() {
  on_pushButtonZeroScale_clicked();
  on_pushButton_zeroRotate_clicked();
  on_pushButtonZeroMovement_clicked();
}

void View::SetModelDataToLabels(QString path) {
  ui->label_filepath->setText(path);
  ui->label_facets_count->setText(
      QString::number(_controller.GetFacetsCount()));
  ui->label_vertexes_count->setText(
      QString::number(_controller.GetVertexesCount()));
}

void View::SetColorToLabel(QLabel *label, s21::Vec3 color) {
  QColor qcolor(255 * color.x, 255 * color.y, 255 * color.z);
  QPalette palette = label->palette();
  palette.setColor(label->backgroundRole(), qcolor);
  label->setPalette(palette);
}

void View::closeEvent(QCloseEvent *event) {
  auto result =
      QMessageBox::question(this, "Закрытие программы",
                            "Хотите ли вы сохранить состояние программы?");
  if (result == QMessageBox::Yes) {
    SaveSettings();
  } else {
    SaveDefaultSettings();
  }
  event->accept();
}

void View::LockUi() {
  ui->move->setDisabled(true);
  ui->scale->setDisabled(true);
  ui->rotate->setDisabled(true);
  ui->settings->setDisabled(true);
  ui->lightning->setDisabled(true);
  ui->pushButton_create_gif->setDisabled(true);
  ui->pushButton_perspective->setDisabled(true);
  ui->pushButton_load_texture->setDisabled(true);
  ui->pushButton_create_image->setDisabled(true);
  ui->pushButton_orthographic->setDisabled(true);
  ui->pushButton_reset_texture->setDisabled(true);
  ui->pushButton_create_gif_rotate->setDisabled(true);
}

void View::UnlockUi() {
  ui->move->setDisabled(false);
  ui->scale->setDisabled(false);
  ui->rotate->setDisabled(false);
  ui->settings->setDisabled(false);
  ui->lightning->setDisabled(false);
  ui->pushButton_create_gif->setDisabled(false);
  ui->pushButton_perspective->setDisabled(false);
  ui->pushButton_load_texture->setDisabled(false);
  ui->pushButton_create_image->setDisabled(false);
  ui->pushButton_orthographic->setDisabled(false);
  ui->pushButton_reset_texture->setDisabled(false);
  ui->pushButton_create_gif_rotate->setDisabled(false);
}

void View::on_lineEdit_stepScale_textChanged(const QString &arg1) {
  double step = arg1.toFloat();
  ui->doubleSpinBox_Scale->setSingleStep(step);
}

void View::on_lineEdit_stepMove_textChanged(const QString &arg1) {
  double step = arg1.toDouble();
  ui->doubleSpinBox_xMove->setSingleStep(step);
  ui->doubleSpinBox_yMove->setSingleStep(step);
  ui->doubleSpinBox_zMove->setSingleStep(step);
}

void View::on_pushButtonZeroMovement_clicked() {
  ui->doubleSpinBox_xMove->setValue(0.0);
  ui->doubleSpinBox_yMove->setValue(0.0);
  ui->doubleSpinBox_zMove->setValue(0.0);
  on_doubleSpinBox_xMove_valueChanged(0.0);
  on_doubleSpinBox_yMove_valueChanged(0.0);
  on_doubleSpinBox_zMove_valueChanged(0.0);
}

void View::on_lineEdit_stepRotate_textChanged(const QString &arg1) {
  double step = arg1.toDouble();
  ui->horizontalSlider_rotate_x->setSingleStep(step);
  ui->horizontalSlider_rotate_y->setSingleStep(step);
  ui->horizontalSlider_rotate_z->setSingleStep(step);
}

void View::on_pushButton_zeroRotate_clicked() {
  ui->horizontalSlider_rotate_x->setValue(0.0);
  ui->horizontalSlider_rotate_y->setValue(0.0);
  ui->horizontalSlider_rotate_z->setValue(0.0);
  on_horizontalSlider_rotate_x_valueChanged(0.0);
  on_horizontalSlider_rotate_y_valueChanged(0.0);
  on_horizontalSlider_rotate_z_valueChanged(0.0);
}

void View::on_pushButtonZeroScale_clicked() {
  ui->doubleSpinBox_Scale->setValue(1.0);
  on_doubleSpinBox_Scale_valueChanged(1.0);
}

void View::on_doubleSpinBox_lineWidth_valueChanged(double arg1) {
  _controller.SetLineWidth(arg1);
}

void View::on_doubleSpinBox_pointSize_valueChanged(double arg1) {
  _controller.SetPointSize(arg1);
}

void View::on_pushButton_selectColorLines_clicked() {
  auto color = QColorDialog::getColor(Qt::green, this);
  _controller.SetLineColor(
      s21::Vec3(color.redF(), color.greenF(), color.blueF()));
  QPalette palette = ui->label_colorLines->palette();
  palette.setColor(ui->label_colorLines->backgroundRole(),
                   QColor(color.red(), color.green(), color.blue()));
  ui->label_colorLines->setPalette(palette);
}

void View::on_pushButton_selectColorPoints_clicked() {
  auto color = QColorDialog::getColor(Qt::green, this);
  _controller.SetPointColor(
      s21::Vec3(color.redF(), color.greenF(), color.blueF()));
  QPalette palette = ui->label_colorPoints->palette();
  palette.setColor(ui->label_colorPoints->backgroundRole(),
                   QColor(color.red(), color.green(), color.blue()));
  ui->label_colorPoints->setPalette(palette);
}

void View::on_comboBox_typesPoints_currentIndexChanged(int index) {
  _controller.SetPointType(index);
}

void View::on_comboBox_typesLines_currentIndexChanged(int index) {
  _controller.SetLineType(index);
}

void View::on_pushButton_selectColorBackground_clicked() {
  auto color = QColorDialog::getColor(Qt::green, this);
  _controller.SetBackgroundColor(
      s21::Vec3(color.redF(), color.greenF(), color.blueF()));
  QPalette palette = ui->label_colorPoints->palette();
  palette.setColor(ui->label_colorBackgournd->backgroundRole(),
                   QColor(color.red(), color.green(), color.blue()));
  ui->label_colorBackgournd->setPalette(palette);
}

void View::on_pushButtonZeroSettings_clicked() {
  _controller.SetLineType(0);
  _controller.SetLineWidth(1);
  _controller.SetLineColor(s21::Vec3(1.f, 0.f, 0.f));
  _controller.SetPointType(0);
  _controller.SetPointSize(2);
  _controller.SetPointColor(s21::Vec3(0.f, 1.f, 0.f));
  _controller.SetBackgroundColor(s21::Vec3(0.5f, 0.5f, 0.5f));

  ui->doubleSpinBox_lineWidth->setValue(1);
  ui->doubleSpinBox_pointSize->setValue(2);
  ui->comboBox_typesLines->setCurrentIndex(0);
  ui->comboBox_typesPoints->setCurrentIndex(0);

  SetColorToLabel(ui->label_colorLines, s21::Vec3(1.f, 0.f, 0.f));
  SetColorToLabel(ui->label_colorPoints, s21::Vec3(0.f, 1.f, 0.f));
  SetColorToLabel(ui->label_colorBackgournd, s21::Vec3(.5f, .5f, .5f));
}
