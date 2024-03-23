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
	int k;
	fscanf_s(f, "%d", &k); // ��������� ������ �������
	float** a = (float**)malloc(k * sizeof(float*)); // �������� ������ ��� ������ ��������
	a[0] = (float*)malloc(k * sizeof(float)); // �������� ������ ��� ����� ������
	int j = 0;
	int i = 0;
	while (fscanf_s(f, "%f ", &a[i][j]) != EOF) { // ���� �� �������� ����� ����� ��������� �����
		j++;
		if (j == k) {
			i++;
			a[i] = (float*)malloc(k * sizeof(float)); // �������� ������ ��� ����� ������
			j = 0;
		}
	}
	for (int i = 0; i < k; i++) {
		for (int j = 0; j < k; j++) {
			fprintf(g, "%.2f ", a[j][i]); // ���������� ����� � ���� g
		}
		fprintf(g, "\n"); // ��������� �� ����� ������
	}
	fclose(f); // ��������� ����
	fclose(g); // ��������� ����
}
