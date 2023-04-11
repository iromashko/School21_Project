#include "./objectrecorder.h"

#include "../TransformModel/transformmodel.h"

void s21::RecorderContext::SetRecorder(Recorder* recoder) {
  delete this->_recoder;
  _recoder = recoder;
}

void s21::RecorderContext::RecordObject(s21::Scene* scene,
                                        TypeRecorder type) const {
  this->_recoder->RecordObject(scene, type);
}

void s21::RecorderImage::RecordObject(Scene* scene, TypeRecorder type) {
  if (!scene->size().isEmpty()) {
    _type = type;
    QString path_to_save =
        QFileDialog::getSaveFileName(scene, "Загрузить файл", "/Users/",
                                     "All files (*.*);; JPEG Image (*.jpeg);;"
                                     "BMP Image (*.bmp)");
    scene->grab().save(path_to_save);
  }
}

void s21::RecorderGif::RecordObject(Scene* scene, TypeRecorder type) {
  if (!scene->size().isEmpty()) {
    _type = type;
    _timer->start(100);
    _object = scene;
    connect(_timer, SIGNAL(timeout()), this, SLOT(GifFile()));
  }
}

void s21::RecorderGif::GifFile() {
  _counter++;
  if (_type == GifRotation) {
    TransformModel::GetTransform().Rotate(_model, _current_angle, true, false,
                                          false);
    _object->LoadObjectModel(_model.GetVertexes(), _model.GetIndexes());
    _object->update();
    _current_angle += _angle;
  }
  QImage image = _object->grabFramebuffer();
  _gif->setDefaultDelay(10);
  _gif->addFrame(image);
  if (_counter == 50) {
    _timer->stop();
    QString path_to_save =
        QFileDialog::getSaveFileName(_object, "Загрузить файл", "/Users/",
                                     "All Files (*.*);; Gif Image (*.gif);;");
    _gif->save(path_to_save);
    _counter = 0;
    image.bits();
    if (_type == GifRotation) {
      _current_angle = 0;
      TransformModel::GetTransform().Rotate(_model, 0, true, false, false);
      _object->LoadObjectModel(_model.GetVertexes(), _model.GetIndexes());
      _object->update();
    }
  }
}
