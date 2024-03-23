#include <stdio.h> // третий вариант
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
	int k;
	fscanf_s(f, "%d", &k); // считываем размер матрицы
	float** a = (float**)malloc(k * sizeof(float*)); // выделяем память под массив массивов
	a[0] = (float*)malloc(k * sizeof(float)); // выделяем память под новый массив
	int j = 0;
	int i = 0;
	while (fscanf_s(f, "%f ", &a[i][j]) != EOF) { // пока не достигли конца файла считываем числа
		j++;
		if (j == k) {
			i++;
			a[i] = (float*)malloc(k * sizeof(float)); // выделяем память под новый массив
			j = 0;
		}
	}
	for (int i = 0; i < k; i++) {
		for (int j = 0; j < k; j++) {
			fprintf(g, "%.2f ", a[j][i]); // записываем числа в файл g
		}
		fprintf(g, "\n"); // переходим на новую строку
	}
	fclose(f); // закрываем файл
	fclose(g); // закрываем файл
}
