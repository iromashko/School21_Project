#pragma once

#include <QFileDialog>
#include <QTimer>
#include <iostream>

#include "../../../extern/gifimage/qgifimage.h"
#include "../../../view/scene.h"
#include "..//VertexData/vertexdata.h"

#define GL_SILENCE_DEPRECATION

namespace s21 {
enum TypeRecorder { Image = 1, Gif, GifRotation };

class Recorder : protected QWidget {
  Q_OBJECT
 public:
  virtual ~Recorder() {}
  virtual void RecordObject(Scene *scene, TypeRecorder type) = 0;

 protected:
  TypeRecorder _type;
};

class RecorderImage : public Recorder {
 public:
  void RecordObject(Scene *scene, TypeRecorder type) override;
};

class RecorderGif : public Recorder {
  Q_OBJECT
 public:
  RecorderGif(ObjectDataModel model) { _model = model; }
  void RecordObject(Scene *scene, TypeRecorder type) override;

 private:
  uint _counter = 0;
  const float _angle = 23 / M_PI;
  float _current_angle = 0.0f;
  Scene *_object;
  QTimer *_timer = new QTimer();
  QGifImage *_gif = new QGifImage;
  ObjectDataModel _model;
 public slots:
  void GifFile();
};

class RecorderContext {
 private:
  Recorder *_recoder;

 public:
  RecorderContext(Recorder *recoder = nullptr) : _recoder(recoder) {}
  ~RecorderContext() { delete this->_recoder; }

  void SetRecorder(Recorder *recoder);

  void RecordObject(s21::Scene *scene, TypeRecorder type) const;
  void SetMoveForImg() const;
};

}  // end namespace s21
