#include <stdlib.h>
int priority(char a) {
  int prior = 0;
  const char operators[10] = {'s', 'q', 'c', 'n', 't', 'l'};
  switch (a) {
    case '^':
      prior = 4;
      break;
    case '*':
    case '/':
      prior = 3;
      break;
    case '-':
    case '+':
      prior = 2;
      break;
    case ')':
    case '(':
      prior = 1;
      break;
  }
  for (int i = 0; operators[i] != '\0'; i++) {
    if (operators[i] == a)
      prior = 5;
  }

  return prior;
}

int left_assoc(char ch) {
  int ok = 0;
  const char operators[10] = {'s', 'q', 'c', 'n', 't', 'l'};
  for (int i = 0; operators[i] != '\0'; i++) {
    if (operators[i] == ch) {
      ok = 1;
      break;
    }
  }
  return ok;
}

str_dig *transformation(str_dig* data, int count) {
  str_dig *stack = (str_dig *) malloc(count * sizeof(str_dig));
  str_dig *final_expression = (str_dig *) malloc(count * sizeof(str_dig));
  int max_sign = 0, final_size = -1, stack_size = -1;

  for (int i = 0; i < count; i++) {
    if (data[i].flag == 1 || (data[i].flag == 0 && (data[i].alpha == 'x' || data[i].alpha == '!'))) {
      final_size++;
      final_expression[final_size] = data[i];

    } else if (data[i].alpha == '(' || priority(data[i].alpha) > max_sign || data[i].alpha == '^'
               || left_assoc(data[i].alpha)) {
      stack_size++;
      stack[stack_size] = data[i];
      max_sign = priority(data[i].alpha);

    } else if (data[i].alpha == ')') {
      while (stack[stack_size].alpha != '(' && stack_size > -1) {
        final_size++;
        final_expression[final_size] = stack[stack_size];
        stack_size--;
      }

      stack_size--;

      if (stack_size > -1)
        max_sign = priority(stack[stack_size].alpha);
      else
        max_sign = 0;

    } else {
      while (max_sign >= priority(data[i].alpha) && stack_size > -1) {
        final_size++;
        final_expression[final_size] = stack[stack_size];
        stack_size--;
        if (stack_size > -1)
          max_sign = priority(stack[stack_size].alpha);
        else
          max_sign = 0;
      }
      stack_size++;
      stack[stack_size] = data[i];
      max_sign = priority(data[i].alpha);
    }
  }
  while (stack_size > -1) {
    final_size++;
    final_expression[final_size] = stack[stack_size];
    stack_size--;
  }
  free(stack);
  free(data);
  return final_expression;
}

double calculating(str_dig *data, double x, int count) {
  str_dig *stack = (str_dig *) malloc(count * sizeof(str_dig));

  int size = -1;
  for (int i = 0; i < count; i++) {
    if (data[i].flag == 1) {
      size++;
      stack[size] = data[i];
    } else if (data[i].flag == 0 && data[i].alpha == 'x') {
      size++;
      data[i].flag = 1;
      data[i].digit = x;
      stack[size] = data[i];
    } else {
      switch (data[i].alpha) {
        case '+': stack[size - 1].digit += stack[size--].digit; break;
        case '-': stack[size - 1].digit -= stack[size--].digit; break;
        case '*': stack[size - 1].digit *= stack[size--].digit; break;
        case '/':
          if (stack[size].digit != 0)
            stack[size - 1].digit /= stack[size--].digit;
          else
            return 0;
          break;
        case 's': stack[size].digit = sin(stack[size].digit); break;
        case 'q': stack[size].digit = sqrt(stack[size].digit); break;
        case 'c': stack[size].digit = cos(stack[size].digit); break;
        case 'n': stack[size].digit = atan(stack[size].digit); break;
        case 't': stack[size].digit = tan(stack[size].digit); break;
        case 'l': stack[size].digit = log(stack[size].digit); break;
      }
    }
  }
  double answer = stack[0].digit;


  free(stack);

  return answer;
}
