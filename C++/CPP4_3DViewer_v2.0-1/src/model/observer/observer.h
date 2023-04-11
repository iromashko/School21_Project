#ifndef INC_3DVIEWER_V2_0_SRC_MODEL_OBSERVER_OBSERVER_H_
#define INC_3DVIEWER_V2_0_SRC_MODEL_OBSERVER_OBSERVER_H_
#include <vector>

namespace s21 {
class Observer {
 public:
  virtual void update() = 0;
};
}  // namespace s21
#endif  // INC_3DVIEWER_V2_0_SRC_MODEL_OBSERVER_OBSERVER_H_
