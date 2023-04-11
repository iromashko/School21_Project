#include "mainwindow.h"

#include <QDebug>

#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);
  picture_ = new Media(ui);
  controller_.addObserver(this);
  LoadSettingsSignal(ui);
}

MainWindow::~MainWindow() {
  if (ui->checkBox->isChecked()) {
    SaveSettingsSignal(ui);
  }
  delete ui;
  delete picture_;
}

void MainWindow::on_openFile_clicked() {
  QString file =
      QFileDialog::getOpenFileName(this, "Выберите файл", ".", tr(" (*.obj)"));
  if (file != "") {
    ui->statusBar->showMessage(file);
    std::string input_file = file.toStdString();
    try {
      controller_.OpenFile(input_file);
    } catch (std::exception &e) {
      QMessageBox::critical(this, "Исключение", e.what());
    }
    ui->coun_vertexes->setText(QString::number(
        (s21::DataModel::GetInstance()->GetVertex().size() - 3) / 3));
    ui->count_facets->setText(
        QString::number(s21::DataModel::GetInstance()->GetFacetsSize() / 2));
    ui->filename->setText(file.right(file.size() - file.lastIndexOf("/") - 1));
  }
}

//_______________OBSERVER_________________
void MainWindow::update() { ui->widget->update(); }
//________________________________________

//_________AFFINE_TRANSFORMATIONS_________
void MainWindow::on_dx_textChanged() {
  controller_.TransformObject(MOVE, ui->dx->value(), X);
}

void MainWindow::on_dy_textChanged() {
  controller_.TransformObject(MOVE, ui->dy->value(), Y);
}

void MainWindow::on_dz_textChanged() {
  controller_.TransformObject(MOVE, ui->dz->value(), Z);
}

void MainWindow::on_rdx_textChanged() {
  controller_.TransformObject(ROTATE, ui->rdx->value(), X);
}

void MainWindow::on_rdy_textChanged() {
  controller_.TransformObject(ROTATE, ui->rdy->value(), Y);
}

void MainWindow::on_rdz_textChanged() {
  controller_.TransformObject(ROTATE, ui->rdz->value(), Z);
}

void MainWindow::on_modelScale_textChanged() {
  controller_.TransformObject(SCALE, ui->modelScale->value(), {});
}
//________________________________________

//_________OPTIMIZE_SCALE_________________
void MainWindow::on_optimization_clicked() {
  ui->doubleSpinBox_Scale->setValue(controller_.GetOptimizeScale());
}

void MainWindow::on_doubleSpinBox_Scale_valueChanged(double valueScale) {
  ui->widget->scale = valueScale;
}

void MainWindow::wheelEvent(QWheelEvent *event) {
  if (event->angleDelta().y() > 0) {
    ui->widget->change_zoom(0.9);
    ui->doubleSpinBox_Scale->setValue(ui->widget->scale);
  } else {
    ui->widget->change_zoom(1.1);
    ui->doubleSpinBox_Scale->setValue(ui->widget->scale);
  }
}
//________________________________________

//_________PAINT__________________________
void MainWindow::on_color_clicked() {
  if (ui->colorPoint->isChecked()) {
    ui->widget->colorPoint = QColorDialog::getColor(Qt::gray);
  } else if (ui->colorLine->isChecked()) {
    ui->widget->colorLine = QColorDialog::getColor(Qt::gray);
  } else if (ui->colorBackground->isChecked()) {
    ui->widget->colorWidget = QColorDialog::getColor(Qt::gray);
  }
}

void MainWindow::on_comboBox_point_form_currentIndexChanged(int index) {
  ui->widget->pointForm = index;
  ui->widget->update();
}

void MainWindow::on_spinBox_point_size_valueChanged(int value) {
  ui->widget->pointSize = value;
  update();
}

void MainWindow::on_spinBox_line_width_valueChanged(int value) {
  ui->widget->lineWidth = value;
  update();
}

void MainWindow::on_comboBox_line_form_currentIndexChanged(int index) {
  ui->widget->lineForm = index;
  ui->widget->update();
}
//________________________________________

//______________PROJECTION________________
void MainWindow::on_radioButton_frustum_clicked(bool checked) {
  ui->widget->frustum = checked;
  update();
}

void MainWindow::on_radioButton_ortho_clicked() {
  ui->widget->frustum = ui->widget->EMPTY;
  update();
}
//________________________________________

//_________SAVE_AND_LOAD_SETTINGS_________
void MainWindow::on_save_settings_clicked() {
  save_settings();
  QMessageBox::information(this, "Сохранение настроек",
                           "Сохранение настроек выполнено успешно");
}

void MainWindow::save_settings() { SaveSettingsSignal(ui); }

void MainWindow::on_load_setting_clicked() {
  load_settings();
  update();
}

void MainWindow::load_settings() { LoadSettingsSignal(ui); }
//________________________________________

//_________GIF_PHOTO_SAVE________
void MainWindow::on_Pthoto_clicked() { picture_->SavePicture(); }

void MainWindow::on_stop_and_save_GIF_clicked() { picture_->SaveGif(); }
//_______________________________
