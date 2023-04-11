#pragma once

#include <cmath>
#include <vector>

namespace s21 {
struct Vec2 {
  float x = 0.f;
  float y = 0.f;

  Vec2() = default;
  Vec2(float x, float y) : x(x), y(y) {}
};

struct Vec3 {
  float x = 0.f;
  float y = 0.f;
  float z = 0.f;

  Vec3() = default;
  Vec3(float x, float y, float z) : x(x), y(y), z(z) {}
  Vec3 &operator*=(float value) {
    x *= value;
    y *= value;
    z *= value;
    return *this;
  }
  Vec3 &operator+=(Vec3 value) {
    x += value.x;
    y += value.y;
    z += value.z;
    return *this;
  }

  Vec3 operator-(const Vec3 &other) const {
    return {x - other.x, y - other.y, z - other.z};
  }
  Vec3 operator+(const Vec3 &other) const {
    return {x + other.x, y + other.y, z + other.z};
  }
  Vec3 operator*(float value) const {
    return {x * value, y * value, z * value};
  }

  [[nodiscard]] float Dot(const Vec3 &other) const {
    return x * other.x + y * other.y + z * other.z;
  }
  [[nodiscard]] float Absolute() const { return sqrtf(x * x + y * y + z * z); }
  [[nodiscard]] float Angle(const Vec3 &other) const {
    return acosf(Dot(other) / (Absolute() * other.Absolute()));
  }
  [[nodiscard]] Vec3 Cross(const Vec3 &other) const {
    Vec3 i(1, 0, 0);
    Vec3 j(0, 1, 0);
    Vec3 k(0, 0, 1);
    return i * (y * other.z - z * other.y) - j * (x * other.z - z * other.x) +
           k * (x * other.y - y * other.x);
  }

  void Normalize(float normalize_to) {
    float max = std::fabs(x) > std::fabs(y) ? x : y;
    max = std::fabs(z) > std::fabs(max) ? z : max;
    float aspect = max / normalize_to;
    x /= aspect;
    y /= aspect;
    z /= aspect;
  }
};

struct VertexData {
  Vec3 position;
  Vec2 tex_coord;
  Vec3 normal;

  VertexData() = default;
  VertexData(Vec3 p, Vec2 t, Vec3 n) : position(p), tex_coord(t), normal(n) {}
  VertexData operator*(float value) {
    position *= value;
    return *this;
  }
  VertexData operator+(Vec3 value) {
    position += value;
    return *this;
  }
};

class ObjectDataModel {
 private:
  std::vector<VertexData> _vertexes;
  std::vector<unsigned int> _indexes;

  int _facets_count = 0;
  int _vertexes_count = 0;
  int _type = 0;

 public:
  ObjectDataModel() = default;
  ~ObjectDataModel() = default;

  const std::vector<VertexData> &GetVertexes() { return _vertexes; }
  VertexData GetVertex(std::size_t pos) { return _vertexes[pos]; }
  const std::vector<unsigned int> &GetIndexes() { return _indexes; }

  void SetVertexes(std::vector<VertexData> &&vertexes) {
    _vertexes = std::move(vertexes);
  }
  void SetVertex(std::size_t pos, VertexData &&vertex) {
    _vertexes[pos] = std::move(vertex);
  }
  void SetVertex(const VertexData &v) { _vertexes.push_back(v); }
  void SetIndex(unsigned int index) { _indexes.push_back(index); }

  void ResizeVertexes(std::size_t size) { _vertexes.resize(size); }
  std::size_t SizeVertexes() const { return _vertexes.size(); }
  std::size_t SizeIndexes() const { return _indexes.size(); }

  int GetFacetsCount() { return _facets_count; }
  int GetVertexesCount() { return _vertexes_count; }
  void SetFacetsCount(int facets) { _facets_count = facets; }
  void SetVertexesCount(int vertexes) { _vertexes_count = vertexes; }

  void Reset() {
    _vertexes.clear();
    _indexes.clear();
    _facets_count = 0;
    _vertexes_count = 0;
  }

  void SetNormals() {
    if (_type == 4) {
      for (std::size_t i = 0; i < _vertexes.size(); i += 3) {
        VertexData v0 = _vertexes[i];
        VertexData v1 = _vertexes[i + 1];
        VertexData v2 = _vertexes[i + 2];

        Vec3 a = v1.position - v0.position;
        Vec3 b = v2.position - v0.position;
        Vec3 normal(a.Cross(b));
        normal.Normalize(1.f);

        _vertexes[i].normal = normal;
        _vertexes[i + 1].normal = normal;
        _vertexes[i + 2].normal = normal;
      }
    }
  }

  void SetType(int type) { _type = type; }
};
}  // namespace s21
