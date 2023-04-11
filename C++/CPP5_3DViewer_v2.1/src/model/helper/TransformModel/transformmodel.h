#ifndef CPP4_3DVIEWER_V2_0_0_TRANSFORMMODEL_TRANSFORMMODEL_HPP
#define CPP4_3DVIEWER_V2_0_0_TRANSFORMMODEL_TRANSFORMMODEL_HPP

#define USE_MATH_DEFINES
#include <cmath>

#include "../VertexData/vertexdata.h"

namespace s21 {
class TransformModel {
 private:
  TransformModel() : _last_move(), _last_scale(1), _last_rotate(){};

  Vec3 _last_move;
  float _last_scale;
  Vec3 _last_rotate;

 public:
  TransformModel(const TransformModel &) = delete;
  void operator=(const TransformModel &) = delete;

  static TransformModel &GetTransform() {
    static TransformModel trans;
    return trans;
  }

  void Scale(ObjectDataModel &model, float scale);
  void Move(ObjectDataModel &model, float value, bool x = false, bool y = false,
            bool z = false);
  void Rotate(ObjectDataModel &model, float value, bool x = false,
              bool y = false, bool z = false);

 private:
  void SetLastMove(float value, bool x, bool y, bool z);
  void SetLastRotate(float angle, bool x, bool y, bool z);

  float GetCurrentMove(float new_move, bool x, bool y, bool z);
  float GetCurrentScale(float new_scale);
  float GetCurrentRotate(float new_rotate, bool x, bool y, bool z);
};

}  // namespace s21

#endif  // !CPP4_3DVIEWER_V2_0_0_TRANSFORMMODEL_TRANSFORMMODEL_HPP
