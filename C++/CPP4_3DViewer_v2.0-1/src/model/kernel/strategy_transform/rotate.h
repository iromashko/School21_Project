#ifndef INC_3DVIEWER_V2_0_SRC_MODEL_KERNEL_STRATEGY_TRANSFORM_ROTATE_H_
#define INC_3DVIEWER_V2_0_SRC_MODEL_KERNEL_STRATEGY_TRANSFORM_ROTATE_H_

#include "transform_strategy.h"

namespace s21 {

class Rotate : public TransformStrategy {
  void transform(double offset, Axis axis) override;
  double CalculateRadians(double& offset) { return offset * M_PI / 180; }

  std::pair<int, int> GetIndexSpinningAxes(Axis axis);

  double RotateFirstAxis(double& offset, const double& first_axis,
                         const double& second_axis);

  double RotateSecondAxis(double& offset, const double& first_axis,
                          const double& second_axis);
};
}  // namespace s21
#endif  // INC_3DVIEWER_V2_0_SRC_MODEL_KERNEL_STRATEGY_TRANSFORM_ROTATE_H_
