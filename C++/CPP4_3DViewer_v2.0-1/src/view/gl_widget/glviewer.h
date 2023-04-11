#ifndef GLVIEWER_H
#define GLVIEWER_H

#define GL_SILENCE_DEPRECATION

#include <QColorDialog>
#include <QFileDialog>
#include <QtOpenGL>
#include <QtOpenGLWidgets>
#include <QtWidgets/QWidget>
#include <iostream>

#include "../../model/dao/data_model.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class GLviewer;
}
QT_END_NAMESPACE

class GLviewer : public QOpenGLWidget {
  Q_OBJECT

 public:
  GLviewer(QWidget *parent = nullptr);
  ~GLviewer();

  double scale;
  double modelScale;

  QColor colorWidget;
  QColor colorLine;
  QColor colorPoint;

  int pointSize;
  int pointForm;
  int lineWidth;
  int lineForm;
  int frustum;

  enum {
    EMPTY,
    POINT_ROUND = 1,
    POINT_QUADRO,
    LINE_SOLID = 1,
    LINE_DASHED,
    IS_CHECKED = 1
  };

  //_________OPTIMIZE_SCALE_________________
  void change_zoom(double value);
  //________________________________________

 private:
  //_______OPENGL_METHODS_AND_MEMBERS_______
  void initializeGL() override;
  void resizeGL(int w, int h) override;
  void paintGL() override;
  void mousePressEvent(QMouseEvent *) override;
  void mouseMoveEvent(QMouseEvent *) override;
  float xRot, yRot, zRot;
  QPoint mPos;
  //________________________________________

  //___________MODEL_RENDERING______________
  void drawShape();
  void pointSettingForm();
  void lineSettingForm();
  //________________________________________

  //______________PROJECTION________________
  void projectionSelect();
  //________________________________________
};
#endif  // GLVIEWER_H
