#ifndef INC_3DVIEWER_V2_0_SRC_MODEL_KERNEL_STRATEGY_TRANSFORM_MOVE_H_
#define INC_3DVIEWER_V2_0_SRC_MODEL_KERNEL_STRATEGY_TRANSFORM_MOVE_H_

#include "transform_strategy.h"

namespace s21 {
class Move : public TransformStrategy {
  void transform(double offset, Axis axis) override;
};
}  // namespace s21

#endif  // INC_3DVIEWER_V2_0_SRC_MODEL_KERNEL_STRATEGY_TRANSFORM_MOVE_H_
