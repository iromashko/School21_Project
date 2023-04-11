#include "s21_SmartCalc.h"

double s21_parser(char* str, double val) {
    N* calc = NULL;
    double res = 0;
    int str_len = strlen(str);
    char tmp_str[256] = {'\0'};
    int d = 0;
    for (int i = 0; i <= str_len; i++) {
        if (str[i] >= '0' && str[i] <= '9') {
            tmp_str[d] = str[i];
            d++;
        } else if (str[i] == '.') {
            tmp_str[d] = str[i];
            d++;
        } else if (str[i] == '+') {
            if (tmp_str[0] == '\0' && str[i - 1] != ')') tmp_str[0] = '+';
            if (str[i - 1] == '(') {
                tmp_str[d] = str[i];
                d++;
            } else {
                s21_line_break(&calc, tmp_str, &d);
                s21_PushBack(&calc, 0, SHORT, PLUS);
                s21_free_str(tmp_str);
            }
        } else if (str[i] == '-') {
            if (tmp_str[0] == '\0' && str[i - 1] != ')') tmp_str[0] = '-';
            if (str[i - 1] == '(') {
                tmp_str[d] = str[i];
                d++;
            } else {
                s21_line_break(&calc, tmp_str, &d);
                s21_PushBack(&calc, 0, SHORT, MINUS);
            }
        } else if (str[i] == '*') {
            s21_line_break(&calc, tmp_str, &d);
            s21_PushBack(&calc, 0, MIDDLE, MULT);
        } else if (str[i] == '/') {
            s21_line_break(&calc, tmp_str, &d);
            s21_PushBack(&calc, 0, MIDDLE, DIV);
        } else if (str[i] == '^') {
            s21_line_break(&calc, tmp_str, &d);
            s21_PushBack(&calc, 0, HIGH, POW);
        } else if (str[i] == 'm' && str[i + 1] == 'o' && str[i + 2] == 'd') {
            i += 2;
            s21_line_break(&calc, tmp_str, &d);
            s21_PushBack(&calc, 0, MIDDLE, MOD);
        } else if (str[i] == 's' && str[i + 1] == 'i' && str[i + 2] == 'n') {
            i += 2;
            s21_line_break(&calc, tmp_str, &d);
            s21_PushBack(&calc, 0, HIGH, SIN);
        } else if (str[i] == 'c' && str[i + 1] == 'o' && str[i + 2] == 's') {
            i += 2;
            s21_line_break(&calc, tmp_str, &d);
            s21_PushBack(&calc, 0, HIGH, COS);
        } else if (str[i] == 't' && str[i + 1] == 'a' && str[i + 2] == 'n') {
            i += 2;
            s21_line_break(&calc, tmp_str, &d);
            s21_PushBack(&calc, 0, HIGH, TAN);
        } else if (str[i] == 'a' && str[i + 1] == 's' && str[i + 2] == 'i' && str[i + 3] == 'n') {
            i += 3;
            s21_line_break(&calc, tmp_str, &d);
            s21_PushBack(&calc, 0, HIGH, ASIN);
        } else if (str[i] == 'a' && str[i + 1] == 'c' && str[i + 2] == 'o' && str[i + 3] == 's') {
            i += 3;
            s21_line_break(&calc, tmp_str, &d);
            s21_PushBack(&calc, 0, HIGH, ACOS);
        } else if (str[i] == 'a' && str[i + 1] == 't' && str[i + 2] == 'a' && str[i + 3] == 'n') {
            i += 3;
            s21_line_break(&calc, tmp_str, &d);
            s21_PushBack(&calc, 0, HIGH, ATAN);
        } else if (str[i] == 'l' && str[i + 1] == 'n') {
            i += 1;
            s21_line_break(&calc, tmp_str, &d);
            s21_PushBack(&calc, 0, HIGH, LN);
        } else if (str[i] == 'l' && str[i + 1] == 'o' && str[i + 2] == 'g') {
            i += 2;
            s21_line_break(&calc, tmp_str, &d);
            s21_PushBack(&calc, 0, HIGH, LOG);
        } else if (str[i] == 's' && str[i + 1] == 'q' && str[i + 2] == 'r' && str[i + 3] == 't') {
            i += 3;
            s21_line_break(&calc, tmp_str, &d);
            s21_PushBack(&calc, 0, HIGH, SQRT);
        } else if (str[i] == '(') {
            s21_line_break(&calc, tmp_str, &d);
            s21_PushBack(&calc, 0, ROUNDBRACKET, ROUNDBRACKET_L);
        } else if (str[i] == ')') {
            s21_line_break(&calc, tmp_str, &d);
            s21_PushBack(&calc, 0, ROUNDBRACKET, ROUNDBRACKET_R);
        } else if (str[i] == 'x') {
            s21_PushBack(&calc, val, 0, 0);
        } else {
            s21_line_break(&calc, tmp_str, &d);
        }
    }
    s21_free_str(tmp_str);
    if (!s21_bracket(str, str_len)) {
        if (calc != NULL) {
            calc = s21_RPN(calc);
        }
        if (calc != NULL) {
            calc = s21_delimiter(calc);
        }
        if (calc != NULL) {
            calc = s21_RPN(calc);
        }
        if (calc != NULL) {
            res = s21_calc(calc);
        }
    } else {
        while (calc) {
            N* free_1 = calc;
            calc = calc->next;
            free(free_1);
        }
    }
    return res;
}

N* s21_delimiter(N* end) {
    N* res = NULL;
    N* str = NULL;
    while (end) {
        if (end->priority == 0) {
            s21_PushBack(&res, end->value, 0, 0);
        } else {
            if (str != NULL) {
                if ((end->priority > str->priority) || (end->type == ROUNDBRACKET_L)) {
                    s21_PushBack(&str, 0, end->priority, end->type);
                } else {
                    if (end->type == ROUNDBRACKET_R) {
                        while (str && (str->type != ROUNDBRACKET_L)) {
                            s21_PushBack(&res, 0, str->priority, str->type);
                            N* str_1 = str;
                            str = str->next;
                            free(str_1);
                        }
                    } else {
                        s21_PushBack(&res, 0, str->priority, str->type);
                        N* free_1 = s21_PopBack(&str);
                        free(free_1);
                    }
                    s21_PushBack(&str, 0, end->priority, end->type);
                    if (res->type < SIN) {
                        if (str->type == ROUNDBRACKET_R) {
                            N* free_2 = s21_PopBack(&str);
                            free(free_2);
                        }
                        if (str->type == ROUNDBRACKET_L) {
                            N* free_3 = s21_PopBack(&str);
                            free(free_3);
                        }
                    }
                }
            } else {
                s21_PushBack(&str, 0, end->priority, end->type);
            }
        }
        N* free_4 = end;
        end = end->next;
        free(free_4);
    }
    while (str) {
        if (str->type != ROUNDBRACKET_L && str->type != ROUNDBRACKET_R) {
            s21_PushBack(&res, 0, str->priority, str->type);
        }
        N* str_2 = str;
        str = str->next;
        free(str_2);
    }
    return res;
}

double s21_calc(N* end) {
    N* str = NULL;
    double res = 0, a = 0, b = 0;
    int cnt = 2;
    while (end) {
        if (end->priority == 0) {
            s21_PushBack(&str, end->value, 0 , 0);
        } else if ((end->priority > 0) && (end->type < SIN && end->type > 0)) {
            while (str) {
                if (cnt == 2) {
                    b = str->value;
                } else if (cnt == 1) {
                    a = str->value;
                } else if (cnt == 0) {
                    break;
                }
                cnt--;
                N* str_1 = str;
                str = str->next;
                free(str_1);
            }
            if (cnt == 0) {
                s21_PushBack(&str, s21_arithmetic(a, b, end->type), 0, 0);
            }
            cnt = 2;
        } else if ((end->priority > 0) && (end->type > MOD && end->type < ROUNDBRACKET_L)) {
            while (str) {
                if (cnt == 2) {
                    b = str->value;
                } else if (cnt == 1) {
                    break;
                }
                cnt--;
                N* str_2 = str;
                str = str->next;
                free(str_2);
            }
            if (cnt == 1) {
                s21_PushBack(&str, s21_trigonometry(b, end->type), 0, 0);
            }
            cnt = 2;
        }
        N* str_3 = end;
        end = end->next;
        free(str_3);
    }
    if (str != NULL) {
        res = str->value;
        free(str);
    }
    return res;
}

double s21_arithmetic(double a, double b, int sym) {
    double res = 0;
    if (sym == PLUS) {
        res = a + b;
    }
    if (sym == MINUS) {
        res = a - b;
    }
    if (sym == DIV) {
        res = a / b;
    }
    if (sym == MULT) {
        res = a * b;
    }
    if (sym == POW) {
        res = pow(a, b);
    }
    if (sym == MOD) {
        res = fmod(a, b);
    }
    return res;
}

double s21_trigonometry(double a, int sym) {
    double res = 0;
    if (sym == SIN) {
        res = sin(a);
    }
    if (sym == COS) {
        res = cos(a);
    }
    if (sym == TAN) {
        res = tan(a);
    }
    if (sym == ASIN) {
        res = asin(a);
    }
    if (sym == ACOS) {
        res = acos(a);
    }
    if (sym == ATAN) {
        res = atan(a);
    }
    if (sym == SQRT) {
        res = sqrt(a);
    }
    if (sym == LN) {
        res = log(a);
    }
    if (sym == LOG) {
        res = log10(a);
    }
    return res;
}

N* s21_RPN(N* end) {
    N* str = NULL;
    N* str_1 = NULL;
    while (end != NULL) {
        str_1 = end;
        s21_PushBack(&str, end->value, end->priority, end->type);
        end = end->next;
        free(str_1);
    }
    return str;
}

void s21_PushBack(N** end, double value, int priority, int type) {
    N* new_N = calloc(1, sizeof(N));
    new_N->value = value;
    new_N->priority = priority;
    new_N->type = type;
    new_N->next = *end;
    *end = new_N;
}

N* s21_PopBack(N** end) {
    N* pointer = NULL;
    N* new_N = calloc(1, sizeof(N));
    pointer = *end;
    new_N->value = pointer->value;
    new_N->priority = pointer->priority;
    new_N->type = pointer->type;
    *end = (*end)->next;
    free(pointer);
    return new_N;
}

int s21_bracket(char* str, int str_len) {
    int res = 0;
    for (int i = 0; i < str_len; i++) {
        if (str[i] == '(') {
            res = (str[i + 1] == ')' ? 1 : 0);
        }
        if (str[i] == ')') {
            res = (str[i + 1] == '(' ? 1 : res);
        }
    }
    return res;
}

void s21_line_break(N** calc, char* str, int* d) {
    if (str[0] != '\0') {
        s21_PushBack(calc, atof(str), 0, 0);
        *d = 0;
        s21_free_str(str);
    }
}

void s21_free_str(char* str) {
    for (int i = 0; str[i] != '\0'; i++) {
        str[i] = '\0';
    }
}
