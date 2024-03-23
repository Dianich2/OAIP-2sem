#include <stdio.h> // ��������� �������
#include <cstdlib>
#include <iostream>
int main() {
	setlocale(LC_CTYPE, "Russian");
	FILE* f, * g;
	errno_t err, err2;
	err = fopen_s(&f, "f.txt", "r"); // ��������� ������ ���� � ������ "f.txt" ��� ������
	err2 = fopen_s(&g, "g.txt", "w"); // ��������� ������ ���� � ������ "g.txt" ��� ������
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
	int k;
	printf("������� �����, ������ �������� ����� ������ �������� ");
	scanf_s("%d", &k);
	while (fscanf_s(f, "%d", &n) != EOF) { // ���� �� ����� �����, ��������� �����
		if (n > k) { // ���������, ����� ��� ���� ������ ���������
			fprintf(g, "%d ", n); // ���������� ����� �� ������ ����
		}
	}
	fclose(f); // ��������� ����
	fclose(g); // ��������� ����
}
