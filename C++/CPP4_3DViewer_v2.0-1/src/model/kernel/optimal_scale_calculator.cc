#include "optimal_scale_calculator.h"

double s21::OptimalScaleCalculator::GetOptimizeScale() {
  double x_max = 0;
  double x_min = 0;
  double y_max = 0;
  double y_min = 0;
  double z_max = 0;
  double z_min = 0;
  double max_size = 0;
  double scale = 100;
  std::vector<double> &vertex = DataModel::GetInstance()->AccessVertex();

  for (size_t var = 3; var < vertex.size(); var += 3) {
    if (vertex[var] > x_max) x_max = vertex[var];
    if (vertex[var] < x_min) x_min = vertex[var];
    if (vertex[var + 1] > y_max) y_max = vertex[var];
    if (vertex[var + 1] < y_min) y_min = vertex[var];
    if (vertex[var + 2] > z_max) z_max = vertex[var];
    if (vertex[var + 2] < z_min) z_min = vertex[var];
  }
  max_size = x_max - x_min;
  if (max_size < y_max - y_min) max_size = y_max - y_min;
  if (max_size < z_max - z_min) max_size = z_max - z_min;

  while (max_size * scale > 1 && scale > 0.0001) {
    scale *= 0.9;
  }
  return scale;
}
