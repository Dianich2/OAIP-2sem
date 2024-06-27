#include <iostream>
#include<Windows.h>
#include <conio.h>
#include <string>
#include <fstream>
#include <regex>
using namespace std;

ofstream fout("t.txt");
regex checknum("([0-9]{1})");

void nums(int a, int currentnum) {
	string temp = to_string(currentnum);
	if (temp.length() == a) {
		fout << currentnum << ' ';
		return;
	}
	if (currentnum > 0) {
		for (int i = 0; i <= a; i++) {
			int num = currentnum * 10 + i;
			nums(a, num);
		}
	}
	else {
		for (int i = 1; i <= a; i++) {
			int num = currentnum * 10 + i;
			nums(a, num);
		}
	}
}

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	int x;
	cout << "Введите цифру (от 0 до 9)\n";
	string a;
	getline(cin, a);
	while (!regex_match(a, checknum)) {
		cout << "Некорректный ввод\n";
		getline(cin, a);
	}
	x = stoi(a);
	nums(x, 0);
	fout.close();
}
