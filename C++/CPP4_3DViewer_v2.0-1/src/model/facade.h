#ifndef INC_3DVIEWER_V2_0_SRC_MODEL_FACADE_H_
#define INC_3DVIEWER_V2_0_SRC_MODEL_FACADE_H_

#include "./kernel/optimal_scale_calculator.h"
#include "./kernel/parser.h"
#include "./kernel/strategy_transform/move.h"
#include "./kernel/strategy_transform/rotate.h"
#include "./kernel/strategy_transform/scale.h"
#include "./kernel/strategy_transform/transform_strategy.h"
#include "./observer/observable.h"
#include "kernel/strategy_transform/transformer.h"

namespace s21 {

class Facade : public Observable {
 public:
  Facade();
  ~Facade();

  void OpenFile(std::string& input_file);
  void TransformObject(TypeTransform type_transform, double offset, Axis axis);
  double GetOptimizeScale();

 private:
  Parser parser_{};
  Transformer* transformer_move_;
  Transformer* transformer_rotate_;
  Transformer* transformer_scale_;
  OptimalScaleCalculator optimal_scale_calculator_;
};

}  // namespace s21

#endif  // INC_3DVIEWER_V2_0_SRC_MODEL_FACADE_H_
