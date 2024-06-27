#include <iostream>
#include<Windows.h>
#include <conio.h>
#include <regex>
using namespace std;

regex checknum("([1-9]+)([0-9]*)");
regex checknum2("([0-9]+)|([0-9]+)([\\.]?)([0-9]+)");
double S(int n, double x) {
	if (n == 0) {
		return 0;
	}
	if (n == 1) {
		return 2 * x;
	}
	return ((2 * n) / (n - 1)) * S(n - 1, x) + ((n - 1) / (2 * n)) * S(n - 2, x);
}

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	string a;
	double x;
	int n;
	cout << "������� ����� n\n";
	getline(cin, a);
	while (!regex_match(a, checknum)) {
		cout << "������������ ����\n";
		getline(cin, a);
	}	
	n = stoi(a);
	cout << "������� ����� x\n";
	getline(cin, a);
	while (!regex_match(a, checknum2)) {
		cout << "������������ ����\n";
		getline(cin, a);
	}
	x = stof(a);
	cout << "��������� ������ " << S(n, x);
}
