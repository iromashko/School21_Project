#include "s21_utils.h"

void s21::exitError(std::string str) {
  perror(str.c_str());
  exit(1);
}