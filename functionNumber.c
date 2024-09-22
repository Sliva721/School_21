#include <stdio.h>
// Функция проверки на ввод ТОЛЬКО ЧИСЕЛ

int main() {
  int a = 0, b = 0, c = 0;
  if (scanf("%d%d%d", &a, &b, &c) != 3) {
    printf("ERROR!\n");
  }
  return 0;
}