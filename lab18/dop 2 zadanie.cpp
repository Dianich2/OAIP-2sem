#include <stdio.h> // первый вариант
#include <cstdlib>
#include <iostream>
int main() {
	setlocale(LC_CTYPE, "Russian");
	FILE* f, * g;
	errno_t err, err2;
	err = fopen_s(&f, "f.txt", "r"); // открываем первый файл с именем "f.txt" для чтения
	err2 = fopen_s(&g, "g.txt", "w"); // открываем второй файл с именем "g.txt" для записи
	if (err != 0) // делаем проверку открытия первого файла
	{
		perror("Невозможно открыть файл\n");
		return EXIT_FAILURE;
	}
	if (err2 != 0) // делаем проверку открытия второго файла
	{
		perror("Невозможно создать файл\n");
		return EXIT_FAILURE;
	}
	printf("Введите число, для которого будем искать кратные числа ");
	int k;
	scanf_s("%d", &k); // считываем число, которому будем искать кратные
	int a;
	while (fscanf_s(f, "%d", &a) != EOF) { // пока не достигли конца файла считываем числа
		if (a % k == 0) { // если кратно, то
			fprintf(g, "%d ", a); // записываем в файл
		}
	}
	fclose(f); // закрываем файл
	fclose(g); // закрываем файл
}
