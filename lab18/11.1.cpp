#include <stdio.h>
#include <cstdlib>
#include <Windows.h>
#include <vector>
#include <iostream>
using namespace std;
int main() {
	SetConsoleOutputCP(1251);
	SetConsoleCP(1251);
	FILE* f, * g;
	int a[1000];
	vector<int> b;
	bool t = false;
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
	int i = 0;
	while (!feof(f)) // пока не конец файла
	{
		fscanf_s(f, "%d", &a[i]); // считываем числа и записываем в массив чисел
		b.push_back(a[i]);
		i++;
	}
	for (int j = 0; j < i; j++) {
		for (int h = j + 1; h < i; h++) {
			if (a[j] == a[h]) {
				t = true;
				for (int k = h; k < i; k++) {
					a[k] = a[k + 1];
				}
				b.erase(b.begin() + h);
				i--;
				h--;
			}
		}
		if (t) {
			for (int k = j; k < i; k++) {
				a[k] = a[k + 1];
			}
			b.erase(b.begin() + j);
			i--;
			j--;
		}
		t = false;
	}
	for (int j = 0; j < b.size(); j++) {
		fprintf(g, "%d ", b[j]); // записываем неповторяющиеся числа во второй файла
	}
	fclose(f); // закрываем первый файл
	fclose(g); // закрываем второй файл
}
