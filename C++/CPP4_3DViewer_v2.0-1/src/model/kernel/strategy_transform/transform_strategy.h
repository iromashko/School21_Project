#ifndef INC_3DVIEWER_V2_0_SRC_MODEL_KERNEL_STRATEGY_TRANSFORM_TRANFORM_STRATEGY_H_
#define INC_3DVIEWER_V2_0_SRC_MODEL_KERNEL_STRATEGY_TRANSFORM_TRANFORM_STRATEGY_H_
#include <cmath>
#include <vector>

#include "../../../view/type_transform.h"
#include "../../dao/data_model.h"

namespace s21 {

class TransformStrategy {
 public:
  virtual ~TransformStrategy() {}
  virtual void transform(double offset, Axis axis) = 0;

  // нужно чтобы не было резких перепадов
  void SetDifferenceOffset(const double& offset, Axis axis);
  void SetDifferenceScale(const double& scale) {
    this->scale_ = scale / this->scale_;
  }

  // нужно обратно вернуть значения
  void SetDifferenceOffsetBack(const double& offset, Axis axis);
  void SetDifferenceScaleBack(const double& scale) { this->scale_ = scale; }

 protected:
  double offset_x_ = 1;
  double offset_y_ = 1;
  double offset_z_ = 1;
  double scale_ = 1;
};

}  // namespace s21

#endif  // INC_3DVIEWER_V2_0_SRC_MODEL_KERNEL_STRATEGY_TRANSFORM_TRANFORM_STRATEGY_H_
