#ifndef INC_3DVIEWER_V2_0_SRC_MODEL_DAO_DATA_MODEL_H_
#define INC_3DVIEWER_V2_0_SRC_MODEL_DAO_DATA_MODEL_H_
#include <string>
#include <vector>

namespace s21 {
class DataModel {
 public:
  [[nodiscard]] const std::vector<double> &GetVertex() const { return vertex_; }
  [[nodiscard]] const std::vector<unsigned int> &GetFacets() const {
    return facets_;
  }

  [[nodiscard]] size_t GetVertexSize() const { return vertex_.size(); }

  [[nodiscard]] size_t GetFacetsSize() const { return facets_.size(); }

  [[nodiscard]] const std::string &GetFileName() const { return file_name_; }

  static DataModel *GetInstance();

  ~DataModel() { delete instance_; }

 private:
  DataModel() = default;
  static inline DataModel *instance_;
  std::vector<double> vertex_{};
  std::vector<unsigned int> facets_{};
  std::string file_name_{};

  friend class Parser;
  friend class OptimalScaleCalculator;
  friend class Move;
  friend class Rotate;
  friend class Scale;

  std::vector<double> &AccessVertex() { return vertex_; }
  std::vector<unsigned int> &AccessFacets() { return facets_; }
  std::string &AccessFileName() { return file_name_; }
};

}  // namespace s21

#endif  // INC_3DVIEWER_V2_0_SRC_MODEL_DAO_DATA_MODEL_H_
