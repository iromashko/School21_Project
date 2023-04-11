#ifndef INC_3DVIEWER_V2_0_SRC_VIEW_TEST_VIEW_H_
#define INC_3DVIEWER_V2_0_SRC_VIEW_TEST_VIEW_H_

#include <string>

#include "../../controller/controller.h"
#include "../../model/observer/observer.h"
#include "../../view/type_transform.h"

namespace s21 {
class TestView : public Observer {
 public:
  TestView() { SubscribeToChangeDataModel(); }
  void update() override;

  void SubscribeToChangeDataModel() { controller_.addObserver(this); }
  void OpenFile(std::string &input_file);
  void TransformObject(TypeTransform type_transform, double offset,
                       Axis axis = X);
  double GetOptimizeScale() { return controller_.GetOptimizeScale(); }

 private:
  Controller controller_{};
};
}  // namespace s21

#endif  // INC_3DVIEWER_V2_0_SRC_VIEW_TEST_VIEW_H_
