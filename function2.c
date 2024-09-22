#include <stdio.h>
// Функция среднего значения.
float average(int a, int b, int c);

int main() {
  int a = 0, b = 0, c = 0;
  if (scanf("%d%d%d", &a, &b, &c) != 3) {
    printf("ERROR!\n");
    return 0;
  }
  float result = average(a, b, c);          // Вызов функции
  printf("Среднее значение: %0.2f\n", result); // Вывод результата
  return 0;
}

float average(int a, int b, int c) { return (a + b + c) / 3; }