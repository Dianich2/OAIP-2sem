#include <iostream> // 7 �������
#include <Windows.h>
#include <ctype.h>
#include <string>
#include <fstream>
using namespace std;
void fromfile(ofstream& f, char a[]) { // ������� ��� ������ � ����
	f << a;
}
void infile(ifstream& f, char	a[]) { // ������� ��� ������ �� �����
	f.getline(a, 100000);
}
int main() {
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	ofstream fout("FILE1.txt"); // �������� ������� ��� ������ � ����
	if (!fout.is_open()) cout << "���� �� ����� ���� ������!\n"; // �������� ����� �� ��������
	cout << "������� ������" << '\n';
	char a[100000];
	cin.getline(a, 100000);
	fromfile(fout, a);
	fout.close();
	ifstream fin("FILE1.txt"); // �������� ������� ��� ������ �� �����
	if (!fin.is_open()) cout << "���� �� ����� ���� ������!\n"; // �������� ����� �� ��������
	infile(fin, a);
	int k;
	cout << "������� ����� ������� ������� " << '\n';
	cin >> k;
	int world_count = 0;
	bool f = false; // ���������� ��� ������������ ��������� � �����
	int i = 0;
	bool t = false; // ���������� ��� ������������ ��������� ������� ������� �������
	bool r = false; // ���������� ��� ������������ ���������� ��������� ������� ����� ������
	while (i != k and a[i] != '\0') {
		if (!f and a[i] != ' ' and (a[i] < '0' or a[i] > '9')) {
			world_count += 1;
			f = true;
		}
		else if (f and a[i] == ' ') {
			f = false;
		}
		if (i + 1 == k and a[i] == ' ') {
			t = true;
			break;
		}
		if (a[i + 1] == '\0' and k >= (i + 1)) {
			cout << "�������� ����� ������� ��������� ����� ������" << '\n';
			r = true;
		}
		i++;
	}
	if (t and !r) {
		cout << "������ � ������� " << k << " ��� ������ " << '\n';
		cout << "����� ����������� ����� " << world_count << '\n';
	}
	else if (!r) {
		cout << "������ � ������� " << k << " ����������� ����� � ������� " << world_count << '\n';
	}
	fin.close();
}
