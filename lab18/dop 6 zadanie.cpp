#include <stdio.h> // четвертый вариант
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
	int n;
	int k;
	printf("Введите число, больше которого будем искать элементы ");
	scanf_s("%d", &k);
	while (fscanf_s(f, "%d", &n) != EOF) { // пока не конец файла, считываем число
		if (n > k) { // проверяем, чтобы оно было больше введённого
			fprintf(g, "%d ", n); // записываем число во второй файл
		}
	}
	fclose(f); // закрываем файл
	fclose(g); // закрываем файл
}
