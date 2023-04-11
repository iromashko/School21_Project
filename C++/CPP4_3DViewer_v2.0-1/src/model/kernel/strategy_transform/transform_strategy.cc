#include "transform_strategy.h"

namespace s21 {
void TransformStrategy::SetDifferenceOffset(const double &offset, Axis axis) {
  switch (axis) {
    case X:
      this->offset_x_ = this->offset_x_ - offset;
      break;
    case Y:
      this->offset_y_ = this->offset_y_ - offset;
      break;
    case Z:
      this->offset_z_ = this->offset_z_ - offset;
      break;
  }
}

void TransformStrategy::SetDifferenceOffsetBack(const double &offset,
                                                Axis axis) {
  switch (axis) {
    case X:
      this->offset_x_ = offset;
      break;
    case Y:
      this->offset_y_ = offset;
      break;
    case Z:
      this->offset_z_ = offset;
      break;
  }
}
}  // namespace s21
