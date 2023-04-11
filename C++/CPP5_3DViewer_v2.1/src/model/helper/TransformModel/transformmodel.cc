#include "transformmodel.h"

namespace s21 {
void TransformModel::Scale(ObjectDataModel &model, float scale) {
  if (scale >= 1e-6) {
    float current_scale = GetCurrentScale(scale);
    for (std::size_t i = 0; i != model.SizeVertexes(); ++i) {
      model.SetVertex(i, model.GetVertex(i) * current_scale);
    }
    _last_scale = scale;
  }
}

void TransformModel::Move(ObjectDataModel &model, float move, bool x, bool y,
                          bool z) {
  float current_move = GetCurrentMove(move, x, y, z);
  for (std::size_t i = 0; i != model.SizeVertexes(); ++i) {
    if (x) {
      model.SetVertex(i, model.GetVertex(i) + Vec3(current_move, 0, 0));
    } else if (y) {
      model.SetVertex(i, model.GetVertex(i) + Vec3(0, current_move, 0));
    } else if (z) {
      model.SetVertex(i, model.GetVertex(i) + Vec3(0, 0, current_move));
    }
  }
  SetLastMove(move, x, y, z);
}

void TransformModel::Rotate(ObjectDataModel &model, float angle, bool x, bool y,
                            bool z) {
  float current_angle = GetCurrentRotate(angle, x, y, z);
  for (std::size_t i = 0; i < model.SizeVertexes(); i++) {
    auto vertexData = model.GetVertex(i);
    if (x) {
      vertexData.position =
          Vec3(vertexData.position.x,
               std::cos(current_angle) * vertexData.position.y -
                   std::sin(current_angle) * vertexData.position.z,
               std::sin(current_angle) * vertexData.position.y +
                   std::cos(current_angle) * vertexData.position.z);

    } else if (y) {
      vertexData.position =
          Vec3(std::cos(current_angle) * vertexData.position.x +
                   std::sin(current_angle) * vertexData.position.z,
               vertexData.position.y,
               -std::sin(current_angle) * vertexData.position.x +
                   std::cos(current_angle) * vertexData.position.z);
    } else if (z) {
      vertexData.position =
          Vec3(std::cos(current_angle) * vertexData.position.x -
                   std::sin(current_angle) * vertexData.position.y,
               std::sin(current_angle) * vertexData.position.x +
                   std::cos(current_angle) * vertexData.position.y,
               vertexData.position.z);
    }
    model.SetVertex(i, std::move(vertexData));
  }
  SetLastRotate(angle, x, y, z);
}

/**
 * @param value saving last movement by axis param
 */
void TransformModel::SetLastMove(float value, bool x, bool y, bool z) {
  if (x) {
    _last_move.x = value;
  } else if (y) {
    _last_move.y = value;
  } else {
    _last_move.z = value;
  }
  (void)z;
}

/**
 * @param angle saving last rotation angle param, must be in radians
 */
void TransformModel::SetLastRotate(float angle, bool x, bool y, bool z) {
  angle *= (M_PI / 180.0);
  if (x) {
    _last_rotate.x = angle;
  } else if (y) {
    _last_rotate.y = angle;
  } else {
    _last_rotate.z = angle;
  }
  (void)z;
}

/**
 * @param new_move
 * @return current move by axis
 */
float TransformModel::GetCurrentMove(float new_move, bool x, bool y, bool z) {
  float current_move = 0.f;
  if (x) {
    current_move = new_move - _last_move.x;
  } else if (y) {
    current_move = new_move - _last_move.y;
  } else {
    current_move = new_move - _last_move.z;
  }
  (void)z;
  return current_move;
}

/**
 * @param new_scale
 * @return current scale
 */
float TransformModel::GetCurrentScale(float new_scale) {
  return new_scale / _last_scale;
}

/**
 * @param new_rotate new rotation angle must be in radians
 * @return current rotation angle in degrees
 */
float TransformModel::GetCurrentRotate(float new_rotate, bool x, bool y,
                                       bool z) {
  float current_rotation_degrees = 0.f;
  float new_rotation_degrees = new_rotate * (M_PI / 180.0);

  if (x) {
    current_rotation_degrees = new_rotation_degrees - _last_rotate.x;
  } else if (y) {
    current_rotation_degrees = new_rotation_degrees - _last_rotate.y;
  } else {
    current_rotation_degrees = new_rotation_degrees - _last_rotate.z;
  }
  (void)z;
  return current_rotation_degrees;
}

}  // namespace s21
