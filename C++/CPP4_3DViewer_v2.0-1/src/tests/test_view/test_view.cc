#include "test_view.h"

namespace s21 {
void TestView::update() {
  //____ОТРИСОВКА____
}

void TestView::OpenFile(std::string &input_file) {
  controller_.OpenFile(input_file);
}

void TestView::TransformObject(TypeTransform type_transform, double offset,
                               Axis axis) {
  controller_.TransformObject(type_transform, offset, axis);
}
}  // namespace s21
