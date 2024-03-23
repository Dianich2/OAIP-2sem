#include <stdio.h>
#include <cstdlib>
#include <iostream>
int main() {
	setlocale(LC_CTYPE, "Russian");
	FILE* f, * g, * d, * t;
	errno_t err, err2, err3, err4;
	err = fopen_s(&f, "NameA.txt", "r"); // ��������� ������ ���� � ������ "NameA.txt" ��� ������
	err2 = fopen_s(&g, "NameB.txt", "r"); // ��������� ������ ���� � ������ "NameB.txt" ��� ������
	err3 = fopen_s(&d, "NameC.txt", "r"); // ��������� ������ ���� � ������ "NameC.txt" ��� ������
	err4 = fopen_s(&t, "NameD.txt", "w"); // ��������� ������ ���� � ������ "NameD.txt" ��� ������
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
	if (err3 != 0) // ������ �������� �������� �������� �����
	{
		perror("���������� ������� ����\n");
		return EXIT_FAILURE;
	}
	if (err4 != 0) // ������ �������� �������� ��������� �����
	{
		perror("���������� ������� ����\n");
		return EXIT_FAILURE;
	}
	int n;
	while (fscanf_s(f, "%d", &n) != EOF) { // ���� �� ����� ������(�� ����� ������ �������� �� 1, ��� ��� �� ������� ����� �� �������)
		fprintf(t, "%d ", n); // ���������� ����� �� 1 �����
		fscanf_s(g, "%d", &n); // ��������� ����� �� 2 �����
		fprintf(t, "%d ", n);// ���������� ����� �� 2 �����
		fscanf_s(d, "%d", &n); // ��������� ����� �� 3 �����
		fprintf(t, "%d ", n);// ���������� ����� �� 3 �����
	}
	fclose(f); // ��������� ����
	fclose(g); // ��������� ����
	fclose(d); // ��������� ����
	fclose(t); // ��������� ����
}
