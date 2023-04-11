#pragma once

#include <unistd.h>

#include <string>
#include <vector>

#include "../helper/ObjectRecorder/objectrecorder.h"
#include "../helper/VertexData/vertexdata.h"

namespace s21 {
class Scene;

class ViewerModel {
 private:
  ObjectDataModel object_data;
  std::vector<std::pair<std::string, ObjectDataModel>> object_data_history;

  ViewerModel() {}

 public:
  static ViewerModel &GetViewerModel() {
    static ViewerModel model;
    return model;
  }

  void LoadObjModelToScene(const std::string &path, Scene *scene);
  void ChangeSceneLightPower(float value, Scene *scene);
  void ChangeSceneLightPos(float value, Scene *scene, bool x = false,
                           bool y = false, bool z = false);
  void ChangeScenePerspective(Scene *scene, bool value);

  void ChangeSceneRotate(Scene *scene, float angle, bool x, bool y, bool z);
  void ChangeSceneScale(Scene *scene, float scale);
  void ChangeSceneMove(Scene *scene, float move, bool x, bool y, bool z);

  void ChangeLightColor(Scene *scene, QColor ribs);
  void ChangeShading(Scene *scene, Shading type);

  void ChangeTexture(const std::string &path, Scene *scene);
  void ResetTexture(Scene *scene);

  void MakeImage(Scene *scene);
  void MakeGif(Scene *scene);
  void MakeGifRotate(Scene *scene);

  int GetVertexesCount() { return object_data.GetVertexesCount(); }
  int GetFacetsCount() { return object_data.GetFacetsCount(); }

  void SetLineWidth(Scene *scene, float width);
  void SetPointSize(Scene *scene, float size);
  void SetBackgroundColor(Scene *scene, Vec3 color);
  void SetLineColor(Scene *scene, Vec3 color);
  void SetPointColor(Scene *scene, Vec3 color);
  void SetLineType(Scene *scene, int type);
  void SetPointType(Scene *scene, int type);

  Vec3 GetColorBackground(Scene *scene);
  Vec3 GetColorLine(Scene *scene);
  Vec3 GetColorPoint(Scene *scene);

  void Reset() { object_data.Reset(); }

 private:
  void AddModelToHistory(std::string path);
  int GetModelIndexFromHistory(std::string path);
};
}  // namespace s21
