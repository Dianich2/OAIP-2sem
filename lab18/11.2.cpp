#include <stdio.h>
#include <conio.h>
#include <cstdlib>
#include <iostream>
int main() {
	setlocale(LC_CTYPE, "Russian");
	FILE* f, * g;
	char a[500];
	int n;
	errno_t err, err2;
	err2 = fopen_s(&g, "F2.txt", "w"); 
	if (err2 != 0) 
	{
		perror("Невозможно создать файл\n");
		return EXIT_FAILURE;
	}
	err = fopen_s(&f, "F1.txt", "r");
	if (err != 0) 
	{
		perror("Невозможно открыть файл\n");
		return EXIT_FAILURE;
	}
	while (fgets(a, 500, f)) 
	{
		if (a[strlen(a) - 1] == '\n') {
			if (a[strlen(a) - 2] == 'a') {
				fprintf(g, "%s", a);
			}
		}
		else if (a[strlen(a) - 1] == 'a') {
			fprintf(g, "%s", a);
		}
	}
	fclose(f); 
	fclose(g);
	return 0;
}
