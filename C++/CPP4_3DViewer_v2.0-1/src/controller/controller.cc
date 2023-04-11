#include "controller.h"

namespace s21 {

void Controller::addObserver(Observer* observer) {
  facade_.addObserver(observer);
}

void Controller::OpenFile(std::string& input_file) {
  facade_.OpenFile(input_file);
}

void Controller::TransformObject(TypeTransform type_transform, double offset,
                                 Axis axis) {
  facade_.TransformObject(type_transform, offset, axis);
}

double Controller::GetOptimizeScale() { return facade_.GetOptimizeScale(); }

}  // namespace s21
