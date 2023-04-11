#ifndef SCENE_H
#define SCENE_H

#include <QMatrix4x4>
#include <QOpenGLBuffer>
#include <QOpenGLShaderProgram>
#include <QOpenGLTexture>
#include <QOpenGLWidget>

#include "../model/helper/VertexData/vertexdata.h"

namespace s21 {

enum Shading { flatShading = 1, guroShading, phongShading };
class Object3D;

class Scene : public QOpenGLWidget {
  Q_OBJECT
 public:
  explicit Scene(QWidget *parent = nullptr);
  ~Scene();

  void SetLightPower(float ligth_power);
  void SetLightPosition(float value, bool x = 0, bool y = 0, bool z = 0);
  void SetPerspective(bool value) { _projection_is_perspective = value; }

  void SetTextureFlag() {
    if (!_path.isEmpty()) {
      _texture_is_inited = !_texture_is_inited;
      update();
    }
  }

  void SetLightColor(QColor ribs) {
    _light_color = QVector3D(ribs.redF(), ribs.greenF(), ribs.blueF());
  }
  void SetShading(Shading type) { typeShading = type; }

  void LoadObjectModel(const std::vector<VertexData> &vertexes,
                       const std::vector<unsigned int> &indexes);
  void LoadTexture(const QString &path);

  bool getPerspective() { return _projection_is_perspective; }
  void SetLineWidth(float width) { _line_width = width; }
  float GetLineWidth() const { return _line_width; }

  void SetPointSize(float size) { _point_size = size; }
  float GetPointSize() const { return _point_size; }

  void SetLineColor(Vec3 color) { _line_color = color; }
  Vec3 GetLineColor() const { return _line_color; }

  void SetPointColor(Vec3 color) { _point_color = color; }
  Vec3 GetPointColor() const { return _point_color; }

  void SetBackgroundColor(Vec3 color) { _background_color = color; }
  Vec3 GetBackgroundColor() const { return _background_color; }

  void SetLineType(int type) { _line_type = type; }
  int GetLineType() const { return _line_type; }

  void SetPointType(int type) { _point_type = type; }
  int GetPointType() const { return _point_type; }

 protected:
  void initializeGL() override;
  void resizeGL(int w, int h) override;
  void paintGL() override;

  void mousePressEvent(QMouseEvent *event) override;
  void mouseMoveEvent(QMouseEvent *event) override;

  void InitShaders();
  void LoadObj();

 private:
  QVector2D _mouse_position;
  QQuaternion _rotation;

  QOpenGLShaderProgram _shader_program;
  QMatrix4x4 _projection_matrix;

  QOpenGLBuffer _vertex_buffer;
  QOpenGLBuffer _index_buffer;
  QOpenGLTexture *_texture;

  QVector4D _light_position = QVector4D(0.0, 0.0, 0.0, 1.0);
  QVector3D _light_color = QVector3D(0.0, 0.0, 1.0);

  bool _model_is_inited = false;
  bool _projection_is_perspective = false;
  bool _texture_is_inited = false;
  bool _shaders_is_linked = false;

  QVector<float> _vertexes;
  QVector<GLuint> _indexes;
  Shading typeShading = Shading::flatShading;
  QString _file_name = nullptr;
  float _light_power = 5.0f;
  QString _path;

  /* Model settings */
  float _line_width{1.0f};
  float _point_size{2.0f};
  Vec3 _line_color;
  Vec3 _point_color;
  Vec3 _background_color;
  int _line_type{0};
  int _point_type{0};
};
}  // namespace s21

#endif  // SCENE_
