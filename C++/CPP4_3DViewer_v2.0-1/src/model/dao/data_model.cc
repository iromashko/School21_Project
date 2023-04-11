#include "data_model.h"

namespace s21 {
DataModel* DataModel::GetInstance() {
  if (!instance_) {
    instance_ = new DataModel();
  }
  return instance_;
}

}  // namespace s21
