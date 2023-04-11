#include "move.h"

namespace s21 {
void Move::transform(double offset, Axis axis) {
  std::vector<double> &vertex = DataModel::GetInstance()->AccessVertex();
  SetDifferenceOffset(offset, axis);
  for (unsigned int i = 3; i < vertex.size(); i += 3) {
    switch (axis) {
      case X:
        vertex[i] += this->offset_x_;
        break;
      case Y:
        vertex[i + 1] += this->offset_y_;
        break;
      case Z:
        vertex[i + 2] += this->offset_z_;
        break;
    }
  }
  SetDifferenceOffsetBack(offset, axis);
}
}  // namespace s21
