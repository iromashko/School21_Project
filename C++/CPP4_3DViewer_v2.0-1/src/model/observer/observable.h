#ifndef INC_3DVIEWER_V2_0_SRC_MODEL_OBSERVER_OBSERVABLE_H_
#define INC_3DVIEWER_V2_0_SRC_MODEL_OBSERVER_OBSERVABLE_H_

#include <vector>

#include "observer.h"

namespace s21 {
class Observable {
 public:
  void addObserver(Observer *observer) { observers_.push_back(observer); }

  void notifyUpdate() {
    int size = observers_.size();
    for (int i = 0; i < size; i++) {
      observers_[i]->update();
    }
  }

 private:
  std::vector<Observer *> observers_;
};
}  // namespace s21

#endif  // INC_3DVIEWER_V2_0_SRC_MODEL_OBSERVER_OBSERVABLE_H_
