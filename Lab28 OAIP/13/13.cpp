#include <iostream>
#include<Windows.h>
#include <conio.h>
#include <string>
#include <regex>
using namespace std;

regex checknum("([\\-]?[1-9]+)([0-9]*)");
int check(int n, int x) {
	if (n % x == 0 && x > 1) {
		return 1;
	}
	return 0;
}

int dnx(int n, int x) {
	if (x == 1) {
		return 1;
	}
	return dnx(n, x - 1) + check(n, x);
}


int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	int x, n;
	string a;
	cout << "������� ����� �����, ��� �������� ����� ������ ��������\n";
	getline(cin, a);
	while (!regex_match(a, checknum)) {
		cout << "������������ ����\n";
		getline(cin, a);
	}
	n = stoi(a);
	n = abs(n);
	cout << "������� ����������� �����, �� �������� �� ����� ������ ��������\n";
	getline(cin, a);
	while (!regex_match(a, checknum)) {
		cout << "������������ ����\n";
		getline(cin, a);
	}
	x = stoi(a);
	x = abs(x);
	cout << "���������� ��������� = " << dnx(n, x);
}
