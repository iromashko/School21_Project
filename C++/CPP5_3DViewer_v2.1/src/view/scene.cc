#define GL_SILENCE_DEPRECATION
#include "scene.h"

#include <QDebug>
#include <QMouseEvent>
#include <QOpenGLContext>

namespace s21 {

Scene::Scene(QWidget *parent)
    : QOpenGLWidget{parent},
      _index_buffer(QOpenGLBuffer::IndexBuffer),
      _texture(nullptr),
      _line_color(1.0, 0.0, 0.0),
      _point_color(0.0, 1.0, 0.0),
      _background_color(0.5, 0.5, 0.5) {}

Scene::~Scene() {}

void Scene::SetLightPower(float light_power) {
  _light_power = light_power;
  update();
}

void Scene::SetLightPosition(float value, bool x, bool y, bool z) {
  if (x) {
    _light_position.setX(value);
  } else if (y) {
    _light_position.setY(value);
  } else if (z) {
    _light_position.setZ(value);
  }
  update();
}

void Scene::LoadObjectModel(const std::vector<VertexData> &vertexes,
                            const std::vector<unsigned int> &indexes) {
  if (_vertex_buffer.isCreated()) _vertex_buffer.destroy();
  if (_index_buffer.isCreated()) _index_buffer.destroy();
  if (!_vertexes.isEmpty()) _vertexes.clear();
  if (!_indexes.isEmpty()) _indexes.clear();

  QVector<VertexData> vertexes_to_buffer;
  for (auto vertex : vertexes) {
    vertexes_to_buffer.append(vertex);
    _vertexes.append(vertex.position.x);
    _vertexes.append(vertex.position.y);
    _vertexes.append(vertex.position.z);
  }

  QVector<GLuint> indexes_to_buffer;
  for (auto index : indexes) {
    indexes_to_buffer.append(index);
  }

  _indexes = indexes_to_buffer;

  _vertex_buffer.create();
  _vertex_buffer.bind();
  _vertex_buffer.allocate(vertexes_to_buffer.constData(),
                          vertexes_to_buffer.size() * sizeof(VertexData));
  _vertex_buffer.release();

  _index_buffer.create();
  _index_buffer.bind();
  _index_buffer.allocate(indexes_to_buffer.constData(),
                         indexes_to_buffer.size() * sizeof(unsigned int));
  _index_buffer.release();

  _model_is_inited = true;
  update();
}

void Scene::LoadTexture(const QString &path) {
  _path = path;
  _texture = new QOpenGLTexture(QImage(_path).mirrored());
  _texture->setMinificationFilter(QOpenGLTexture::Nearest);
  _texture->setMagnificationFilter(QOpenGLTexture::Linear);
  _texture->setWrapMode(QOpenGLTexture::Repeat);
  _texture_is_inited = true;
}

void Scene::initializeGL() {
  glClearColor(_background_color.x, _background_color.y, _background_color.z,
               1.0);
  glEnable(GL_PROGRAM_POINT_SIZE);
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_CULL_FACE);
}

void Scene::resizeGL(int w, int h) {
  float aspect = w / static_cast<float>(h);

  _projection_matrix.setToIdentity();
  _projection_matrix.perspective(45.f, aspect, 0.1, 100.0f);
}

void Scene::paintGL() {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glClearColor(_background_color.x, _background_color.y, _background_color.z,
               1.0);

  if (_model_is_inited) {
    QMatrix4x4 view_matrix;
    view_matrix.setToIdentity();
    view_matrix.rotate(_rotation);
    view_matrix.translate(0.0, 0.0, -5.0);

    if (getPerspective()) {
      view_matrix.frustum(-0.1, 0.1, -0.1, 0.1, 0.1, 1.0);
      view_matrix.translate(0, 0, -0.1 * 3.0);
    }

    QMatrix4x4 model_matrix;
    model_matrix.setToIdentity();

    if (_texture_is_inited) {
      if (!_shaders_is_linked) {
        InitShaders();
      }
      _shader_program.bind();
      _shader_program.setUniformValue("u_projection_matrix",
                                      _projection_matrix);
      _shader_program.setUniformValue("u_view_matrix", view_matrix);
      _shader_program.setUniformValue("u_model_matrix", model_matrix);
      _shader_program.setUniformValue("u_light_position", _light_position);
      _shader_program.setUniformValue("u_light_power", _light_power);
      _shader_program.setUniformValue("u_light_color", _light_color);
      _shader_program.setUniformValue("typeShading", typeShading);

      _texture->bind(0);
      _shader_program.setUniformValue("u_texture", 0);

      _vertex_buffer.bind();

      int offset = 0;

      int vertex_location = _shader_program.attributeLocation("a_position");
      _shader_program.enableAttributeArray(vertex_location);
      _shader_program.setAttributeBuffer(vertex_location, GL_FLOAT, offset, 3,
                                         sizeof(VertexData));

      offset += sizeof(QVector3D);

      int texture_location = _shader_program.attributeLocation("a_texcoord");
      _shader_program.enableAttributeArray(texture_location);
      _shader_program.setAttributeBuffer(texture_location, GL_FLOAT, offset, 2,
                                         sizeof(VertexData));

      offset += sizeof(QVector2D);

      int normal_location = _shader_program.attributeLocation("a_normal");
      _shader_program.enableAttributeArray(normal_location);
      _shader_program.setAttributeBuffer(normal_location, GL_FLOAT, offset, 3,
                                         sizeof(VertexData));

      _index_buffer.bind();
      glDrawElements(GL_TRIANGLES, _index_buffer.size(), GL_UNSIGNED_INT,
                     nullptr);

      _shader_program.release();
      _vertex_buffer.release();
      _index_buffer.release();
      _texture->release();

    } else {
      glVertexPointer(3, GL_FLOAT, 0, _vertexes.constData());
      glEnableClientState(GL_VERTEX_ARRAY);
      if (_point_type == 1) {
        glEnable(GL_POINT_SMOOTH);
      }

      if (_point_type != 2) {
        glPointSize(_point_size);
        glColor3f(_point_color.x, _point_color.y, _point_color.z);
        glDrawElements(GL_POINTS, _indexes.size(), GL_UNSIGNED_INT,
                       _indexes.constData());
      }
      glEnable(GL_LINE_STIPPLE);
      glLineWidth(_line_width);
      if (_line_type == 1) {
        glLineStipple(2, 0X11FF);
      } else if (_line_type == 2) {
        glLineStipple(2, 0X00FF);
      } else {
        glDisable(GL_LINE_STIPPLE);
      }
      glColor3f(_line_color.x, _line_color.y, _line_color.z);
      glDrawElements(GL_TRIANGLES, _indexes.size(), GL_UNSIGNED_INT,
                     _indexes.constData());
      glDisableClientState(GL_VERTEX_ARRAY);
    }
  }
}

void Scene::mousePressEvent(QMouseEvent *event) {
  if (event->buttons() == Qt::LeftButton) {
    _mouse_position = QVector2D(event->position());
  }
  event->accept();
}

void Scene::mouseMoveEvent(QMouseEvent *event) {
  if (event->buttons() == Qt::LeftButton) {
    QVector2D difference = QVector2D(event->position()) - _mouse_position;
    _mouse_position = QVector2D(event->position());

    float angle = difference.length();
    QVector3D axis = QVector3D(difference.y(), difference.x(), 0.0);
    _rotation = QQuaternion::fromAxisAndAngle(axis, angle) * _rotation;
    update();
  }
}

void Scene::InitShaders() {
  if (!_shader_program.addShaderFromSourceFile(QOpenGLShader::Vertex,
                                               ":/vshader.vsh"))
    close();
  if (!_shader_program.addShaderFromSourceFile(QOpenGLShader::Fragment,
                                               ":/fshader.fsh"))
    close();
  if (!_shader_program.link()) close();
  _shaders_is_linked = true;
}

}  // namespace s21
