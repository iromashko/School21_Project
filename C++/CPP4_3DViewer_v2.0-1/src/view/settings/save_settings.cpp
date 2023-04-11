#include "save_settings.h"

#include "ui_mainwindow.h"

SaveSettings::SaveSettings(QObject *parent) : QObject{parent} {
  this->settings_file = QApplication::applicationDirPath() + "/settings.ini";
}

void SaveSettings::SaveSettingsUI(Ui::MainWindow *ui) {
  QSettings settings(this->settings_file, QSettings::NativeFormat);
  settings.setValue("comboBox_point_form",
                    ui->comboBox_point_form->currentIndex());
  settings.setValue("spinBox_point_size", ui->spinBox_point_size->value());
  settings.setValue("comboBox_line_form",
                    ui->comboBox_line_form->currentIndex());
  settings.setValue("spinBox_line_width", ui->spinBox_line_width->value());

  settings.setValue("colorBackground", ui->colorBackground->isChecked());
  settings.setValue("colorLine", ui->colorLine->isChecked());
  settings.setValue("colorPoint", ui->colorPoint->isChecked());

  settings.setValue("colorLine_c", ui->widget->colorLine);
  settings.setValue("colorPoint_c", ui->widget->colorPoint);
  settings.setValue("colorWidget_c", ui->widget->colorWidget);
}

void SaveSettings::LoadSettingsUI(Ui::MainWindow *ui) {
  QSettings settings(this->settings_file, QSettings::NativeFormat);
  QFile file(this->settings_file);
  if (file.exists()) {
    ui->comboBox_point_form->setCurrentIndex(
        settings.value("comboBox_point_form").toInt());
    ui->comboBox_line_form->setCurrentIndex(
        settings.value("comboBox_line_form").toInt());

    ui->spinBox_point_size->setValue(
        settings.value("spinBox_point_size").toInt());
    ui->spinBox_line_width->setValue(
        settings.value("spinBox_line_width").toInt());

    ui->colorBackground->setChecked(settings.value("colorBackground").toBool());
    ui->colorLine->setChecked(settings.value("colorLine").toBool());
    ui->colorPoint->setChecked(settings.value("colorPoint").toBool());

    ui->widget->colorLine = settings.value("colorLine_c").value<QColor>();
    ui->widget->colorPoint = settings.value("colorPoint_c").value<QColor>();
    ui->widget->colorWidget = settings.value("colorWidget_c").value<QColor>();
  }
}
