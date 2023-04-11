#ifndef INC_3DVIEWER_V2_0_SRC_MODEL_KERNEL_STRATEGY_TRANSFORM_SCALE_H_
#define INC_3DVIEWER_V2_0_SRC_MODEL_KERNEL_STRATEGY_TRANSFORM_SCALE_H_

#include <iostream>

#include "transform_strategy.h"

namespace s21 {
class Scale : public TransformStrategy {
  void transform(double scale, [[maybe_unused]] Axis axis = X) override;
};
}  // namespace s21

#endif  // INC_3DVIEWER_V2_0_SRC_MODEL_KERNEL_STRATEGY_TRANSFORM_SCALE_H_
