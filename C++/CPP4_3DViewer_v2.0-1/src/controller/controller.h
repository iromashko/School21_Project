#ifndef INC_3DVIEWER_V2_0_SRC_CONTROLLER_CONTROLLER_H_
#define INC_3DVIEWER_V2_0_SRC_CONTROLLER_CONTROLLER_H_

#include "../model/facade.h"
#include "../view/type_transform.h"

namespace s21 {

class Controller {
 public:
  void addObserver(Observer* observer);

  void OpenFile(std::string& input_file);
  void TransformObject(TypeTransform type_transform, double offset, Axis axis);
  double GetOptimizeScale();

 private:
  Facade facade_{};
};

}  // namespace s21

#endif  // INC_3DVIEWER_V2_0_SRC_CONTROLLER_CONTROLLER_H_
