#include <stdio.h>
#include <cstdlib>
#include <iostream>
int main() {
	setlocale(LC_CTYPE, "Russian");
	FILE* f, * g, * d, * t;
	errno_t err, err2, err3, err4;
	err = fopen_s(&f, "NameA.txt", "r"); // открываем первый файл с именем "NameA.txt" для чтения
	err2 = fopen_s(&g, "NameB.txt", "r"); // открываем второй файл с именем "NameB.txt" для чтения
	err3 = fopen_s(&d, "NameC.txt", "r"); // открываем второй файл с именем "NameC.txt" для чтения
	err4 = fopen_s(&t, "NameD.txt", "w"); // открываем второй файл с именем "NameD.txt" для записи
	if (err != 0) // делаем проверку открытия первого файла
	{
		perror("Невозможно открыть файл\n");
		return EXIT_FAILURE;
	}
	if (err2 != 0) // делаем проверку открытия второго файла
	{
		perror("Невозможно открыть файл\n");
		return EXIT_FAILURE;
	}
	if (err3 != 0) // делаем проверку открытия третьего файла
	{
		perror("Невозможно открыть файл\n");
		return EXIT_FAILURE;
	}
	if (err4 != 0) // делаем проверку открытия четвёртого файла
	{
		perror("Невозможно создать файл\n");
		return EXIT_FAILURE;
	}
	int n;
	while (fscanf_s(f, "%d", &n) != EOF) { // пока не конец файлов(мы можем делать проверку по 1, так как их размеры равны по условию)
		fprintf(t, "%d ", n); // записываем число из 1 файла
		fscanf_s(g, "%d", &n); // считываем число из 2 файла
		fprintf(t, "%d ", n);// записываем число из 2 файла
		fscanf_s(d, "%d", &n); // считываем число из 3 файла
		fprintf(t, "%d ", n);// записываем число из 3 файла
	}
	fclose(f); // закрываем файл
	fclose(g); // закрываем файл
	fclose(d); // закрываем файл
	fclose(t); // закрываем файл
}
