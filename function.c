#include <stdio.h>

int sum(int a, int b);

int main() {
  int x = 0, y = 0;
  scanf("%d%d", &x, &y);
  int result = sum(x, y);        // Вызов функции
  printf("Сумма: %d\n", result); // Вывод результата
  return 0;
}

int sum(int a, int b) { return a + b; }