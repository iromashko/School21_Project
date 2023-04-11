#ifndef SAVESETTINGS_H
#define SAVESETTINGS_H

#include <QObject>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class SaveSettings : public QObject {
  Q_OBJECT
 public:
  explicit SaveSettings(QObject *parent = nullptr);

  void SaveSettingsUI(Ui::MainWindow *ui);
  void LoadSettingsUI(Ui::MainWindow *ui);

 private:
  QString settings_file{};
};

#endif  // SAVESETTINGS_H
