#include <stdio.h> // ������ �������
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
	printf("������� �����, ��� �������� ����� ������ ������� ����� ");
	int k;
	scanf_s("%d", &k); // ��������� �����, �������� ����� ������ �������
	int a;
	while (fscanf_s(f, "%d", &a) != EOF) { // ���� �� �������� ����� ����� ��������� �����
		if (a % k == 0) { // ���� ������, ��
			fprintf(g, "%d ", a); // ���������� � ����
		}
	}
	fclose(f); // ��������� ����
	fclose(g); // ��������� ����
}
