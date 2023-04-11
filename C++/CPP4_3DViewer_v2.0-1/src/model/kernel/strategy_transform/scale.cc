#include "scale.h"

namespace s21 {
void Scale::transform(double scale, [[maybe_unused]] Axis axis) {
  std::vector<double> &vertex = DataModel::GetInstance()->AccessVertex();
  if (scale <= 0) {
    scale = 0.1;
  }
  SetDifferenceScale(scale);

  for (unsigned int i = 3; i < vertex.size(); i += 3) {
    vertex[i] *= this->scale_;
    vertex[i + 1] *= this->scale_;
    vertex[i + 2] *= this->scale_;
  }
  SetDifferenceScaleBack(scale);
}
}  // namespace s21
