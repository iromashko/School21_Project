#ifndef INC_3DVIEWER_V2_0_SRC_MODEL_KERNEL_transform_strategy_TRANSFORMER_H_
#define INC_3DVIEWER_V2_0_SRC_MODEL_KERNEL_transform_strategy_TRANSFORMER_H_

#include "transform_strategy.h"

namespace s21 {
class Transformer {
 public:
  Transformer(TransformStrategy* strategy_transform)
      : transform_strategy_(strategy_transform) {}
  ~Transformer() { delete transform_strategy_; }

  void TransformObject(double offset, Axis axis) {
    transform_strategy_->transform(offset, axis);
  }

 private:
  TransformStrategy* transform_strategy_{};
};
}  // namespace s21

#endif  // INC_3DVIEWER_V2_0_SRC_MODEL_KERNEL_transform_strategy_TRANSFORMER_H_
