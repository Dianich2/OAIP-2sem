#include <stdio.h> // ��������� �������
#include <cstdlib>
#include <iostream>
int main() {
	setlocale(LC_CTYPE, "Russian");
	FILE* f, * g;
	errno_t err, err2;
	err = fopen_s(&f, "fileA.txt", "r"); // ��������� ������ ���� � ������ "fileA.txt" ��� ������
	err2 = fopen_s(&g, "fileB.txt", "w"); // ��������� ������ ���� � ������ "fileB.txt" ��� ������
	if (err != 0) // ������ �������� �������� ������� �����
	{
		perror("���������� ������� ����\n");
		return EXIT_FAILURE;
	}
	if (err2 != 0) // ������ �������� �������� ������� �����
	{
		perror("���������� ������� ����\n");
		return EXIT_FAILURE;
	}
	int n;
	while (fscanf_s(f, "%d", &n) != EOF) { // ���� �� ����� �����, ��������� �����
		if (n > 0) { // ���������, ����� ��� ���� �������������
			fprintf(g, "%d ", n); // ���������� ����� �� ������ ����
		}
	}
	fclose(f); // ��������� ����
	fclose(g); // ��������� ����
}
