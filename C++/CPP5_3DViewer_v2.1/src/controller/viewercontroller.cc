#include "viewercontroller.h"

namespace s21 {
void ViewerController::LoadObjModelToScene(const std::string &path) {
  if (_scene) {
    Reset();
    ViewerModel::GetViewerModel().LoadObjModelToScene(path, _scene);
  }
}

void ViewerController::ChangeSceneLightPower(float value) {
  if (_scene) {
    ViewerModel::GetViewerModel().ChangeSceneLightPower(value, _scene);
  }
}

void ViewerController::ChangeSceneLightPos(float value, bool x, bool y,
                                           bool z) {
  if (_scene) {
    ViewerModel::GetViewerModel().ChangeSceneLightPos(value, _scene, x, y, z);
  }
}

void ViewerController::ChangeRotate(float angle, bool x, bool y, bool z) {
  if (_scene) {
    ViewerModel::GetViewerModel().ChangeSceneRotate(_scene, angle, x, y, z);
  }
}

void ViewerController::ChangeMove(float move, bool x, bool y, bool z) {
  if (_scene) {
    ViewerModel::GetViewerModel().ChangeSceneMove(_scene, move, x, y, z);
  }
}

Vec3 ViewerController::GetColorBackground() {
  Vec3 color;
  if (_scene) {
    color = ViewerModel::GetViewerModel().GetColorBackground(_scene);
  }
  return color;
}

Vec3 ViewerController::GetColorLine() {
  Vec3 color;
  if (_scene) {
    color = ViewerModel::GetViewerModel().GetColorLine(_scene);
  }
  return color;
}

Vec3 ViewerController::GetColorPoint() {
  Vec3 color;
  if (_scene) {
    color = ViewerModel::GetViewerModel().GetColorPoint(_scene);
  }
  return color;
}

}  // namespace s21
