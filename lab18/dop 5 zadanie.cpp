#include <stdio.h> // четвертый вариант
#include <cstdlib>
#include <iostream>
int main() {
	setlocale(LC_CTYPE, "Russian");
	FILE* f, * g;
	errno_t err, err2;
	err = fopen_s(&f, "fileA.txt", "r"); // открываем первый файл с именем "fileA.txt" для чтения
	err2 = fopen_s(&g, "fileB.txt", "w"); // открываем второй файл с именем "fileB.txt" для записи
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
	while (fscanf_s(f, "%d", &n) != EOF) { // пока не конец файла, считываем число
		if (n > 0) { // проверяем, чтобы оно было положительным
			fprintf(g, "%d ", n); // записываем число во второй файл
		}
	}
	fclose(f); // закрываем файл
	fclose(g); // закрываем файл
}
