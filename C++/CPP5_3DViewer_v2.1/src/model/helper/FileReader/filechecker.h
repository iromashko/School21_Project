#ifndef FILECHECKER_H
#define FILECHECKER_H

#include <string>

namespace s21 {
enum ObjectFileType {
  with_texture,
  with_normal,
  with_all,
  with_error,
  without_texture_normal
};

class FileChecker {
 private:
  std::string _path;
  FileChecker() = default;

 public:
  FileChecker(const FileChecker &) = delete;
  FileChecker &operator=(const FileChecker &) = delete;
  ~FileChecker() = default;

  static FileChecker &GetChecker(const std::string &path) {
    static FileChecker checker;
    checker.SetCheckingPath(path);
    return checker;
  }

  ObjectFileType Check();

  static void PrintType(ObjectFileType type);

 private:
  void SetCheckingPath(const std::string &path) { _path = path; }
};
}  // namespace s21
#endif  // FILECHECKER_H
