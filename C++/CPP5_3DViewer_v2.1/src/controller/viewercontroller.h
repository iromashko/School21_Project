#pragma once

#include <string>

#include "../model/facade/viewermodel.h"

namespace s21 {
class Scene;

class ViewerController {
 private:
  Scene *_scene = nullptr;

 public:
  ViewerController() = default;

  void SetScene(Scene *scene) { _scene = scene; }

  void LoadObjModelToScene(const std::string &path);
  void ChangeSceneLightPower(float value);
  void ChangeSceneLightPos(float value, bool x = false, bool y = false,
                           bool z = false);
  void ChangePerspective(bool value) {
    ViewerModel::GetViewerModel().ChangeScenePerspective(_scene, value);
  }

  void ChangeRotate(float angle, bool x = false, bool y = false,
                    bool z = false);
  void ChangeMove(float move, bool x = false, bool y = false, bool z = false);
  void ChangeScale(float value) {
    ViewerModel::GetViewerModel().ChangeSceneScale(_scene, value);
  }
  void ChangeShadowColor(QColor color) {
    ViewerModel::GetViewerModel().ChangeLightColor(_scene, color);
  }
  void ChangeShadow(Shading type) {
    ViewerModel::GetViewerModel().ChangeShading(_scene, type);
  }

  void AddTexture(const std::string &path) {
    ViewerModel::GetViewerModel().ChangeTexture(path, _scene);
  }
  void ResetTexture() { ViewerModel::GetViewerModel().ResetTexture(_scene); }

  void RecordImage() { ViewerModel::GetViewerModel().MakeImage(_scene); }
  void RecordGif() { ViewerModel::GetViewerModel().MakeGif(_scene); }
  void RecordGifRotate() {
    ViewerModel::GetViewerModel().MakeGifRotate(_scene);
  }

  void SetLineWidth(float width) {
    ViewerModel::GetViewerModel().SetLineWidth(_scene, width);
  }
  void SetPointSize(float size) {
    ViewerModel::GetViewerModel().SetPointSize(_scene, size);
  }
  void SetBackgroundColor(Vec3 color) {
    ViewerModel::GetViewerModel().SetBackgroundColor(_scene, color);
  }
  void SetLineColor(Vec3 color) {
    ViewerModel::GetViewerModel().SetLineColor(_scene, color);
  }
  void SetPointColor(Vec3 color) {
    ViewerModel::GetViewerModel().SetPointColor(_scene, color);
  }
  void SetLineType(int type) {
    ViewerModel::GetViewerModel().SetLineType(_scene, type);
  }
  void SetPointType(int type) {
    ViewerModel::GetViewerModel().SetPointType(_scene, type);
  }

  int GetVertexesCount() {
    return ViewerModel::GetViewerModel().GetVertexesCount();
  }
  int GetFacetsCount() {
    return ViewerModel::GetViewerModel().GetFacetsCount();
  }

  Vec3 GetColorBackground();
  Vec3 GetColorLine();
  Vec3 GetColorPoint();

  void Reset() { ViewerModel::GetViewerModel().Reset(); }
};
}  // namespace s21
