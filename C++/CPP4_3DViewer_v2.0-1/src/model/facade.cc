#include "facade.h"

namespace s21 {
Facade::Facade() {
  transformer_move_ = new Transformer(new Move());
  transformer_rotate_ = new Transformer(new Rotate());
  transformer_scale_ = new Transformer(new Scale());
}

Facade::~Facade() {
  delete transformer_move_;
  delete transformer_rotate_;
  delete transformer_scale_;
}

void Facade::OpenFile(std::string& input_file) {
  parser_.OpenFile(input_file);
  this->notifyUpdate();
}

void Facade::TransformObject(TypeTransform type_transform, double offset,
                             Axis axis) {
  switch (type_transform) {
    case MOVE:
      transformer_move_->TransformObject(offset, axis);
      break;
    case ROTATE:
      transformer_rotate_->TransformObject(offset, axis);
      break;
    case SCALE:
      transformer_scale_->TransformObject(offset, axis);
      break;
  }
  this->notifyUpdate();
}

double Facade::GetOptimizeScale() {
  double optimize_scale = optimal_scale_calculator_.GetOptimizeScale();
  this->notifyUpdate();
  return optimize_scale;
}

}  // namespace s21
