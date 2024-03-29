#ifndef SRC_S21_SMARTCALC_H_
#define SRC_S21_SMARTCALC_H_

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
// #include <ctype.h>
#include <limits.h>
#include <string.h>

typedef enum {
    NUMBER = 1,
    X = 2,
    PLUS = 3,
    MINUS = 4,
    MULT = 5,
    DIV = 6,
    POW = 7,
    MOD = 9,
    SIN = 10,
    COS = 11,
    TAN = 12,
    ASIN = 13,
    ACOS = 14,
    ATAN = 15,
    SQRT = 16,
    LN = 17,
    LOG = 18,
    ROUNDBRACKET_L = 19,
    ROUNDBRACKET_R = 20
} type_t;

typedef enum {
    SHORT = 1,
    MIDDLE = 2,
    HIGH = 3,
    ROUNDBRACKET = -1
} top_priority;

typedef struct N {
    double value;
    top_priority priority;
    struct N* next;
    type_t type;
} N;

double s21_parser(char* str, double val);
N* s21_delimiter(N* end);
double s21_calc(N* end);
double s21_arithmetic(double a, double b, int sym);
double s21_trigonometry(double a, int sym);
N* s21_RPN(N* end);
void s21_PushBack(N** end, double value, int priority, int type);
N* s21_PopBack(N** end);
int s21_bracket(char* str, int str_len);
void s21_line_break(N** calc, char* str, int* d);
void s21_free_str(char* str);

#endif  // SRC_S21_SMARTCALC_H_
