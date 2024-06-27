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
	cout << "Введите целое число, для которого будем искать делители\n";
	getline(cin, a);
	while (!regex_match(a, checknum)) {
		cout << "Некорректный ввод\n";
		getline(cin, a);
	}
	n = stoi(a);
	n = abs(n);
	cout << "Введите натуральное число, до которого мы будем искать делители\n";
	getline(cin, a);
	while (!regex_match(a, checknum)) {
		cout << "Некорректный ввод\n";
		getline(cin, a);
	}
	x = stoi(a);
	x = abs(x);
	cout << "Количество делителей = " << dnx(n, x);
}
