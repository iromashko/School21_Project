#pragma once

#include <cmath>

#include "../VertexData/vertexdata.h"

namespace s21 {
class Normalizer {
 private:
  Normalizer(){};

 public:
  Normalizer(const Normalizer &) = delete;
  Normalizer &operator=(const Normalizer &) = delete;

  static Normalizer &GetNormalizer() {
    static Normalizer normalizer;
    return normalizer;
  }

  void Normalize(ObjectDataModel &data, float normalize_to) {
    auto vertexes = data.GetVertexes();

    float max = vertexes[0].position.x;

    for (std::size_t i = 0; i != vertexes.size(); ++i) {
      if (fabs(vertexes[i].position.x) > max)
        max = fabs(vertexes[i].position.x);
      if (fabs(vertexes[i].position.y) > max)
        max = fabs(vertexes[i].position.y);
      if (fabs(vertexes[i].position.z) > max)
        max = fabs(vertexes[i].position.z);
    }

    float aspect = max / normalize_to;
    for (std::size_t i = 0; i != vertexes.size(); ++i) {
      vertexes[i].position.x /= aspect;
      vertexes[i].position.y /= aspect;
      vertexes[i].position.z /= aspect;
    }

    data.SetVertexes(std::move(vertexes));
  }
};

}  // namespace s21
