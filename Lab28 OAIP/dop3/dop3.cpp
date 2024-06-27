#include <iostream>
#include<Windows.h>
#include <conio.h>
#include <regex>
#include <string>
using namespace std;
regex checknum("([1-9]+)([0-9]*)");
void permutation(int a[], int start, int end) {
	if (start == end) {
		for (int i = 0; i < 5; i++) {
			cout << a[i] << ' ';
		}
		cout << '\n';
		return;
	}
	for (int i = start; i <= end; i++) {
		swap(a[i], a[start]);
		permutation(a, start + 1, end);
		swap(a[i], a[start]);
	}
}

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	int b[5];
	for (int i = 0; i < 5; i++) {
		cout << "Введите число\n";
		string a;
		getline(cin, a);
		while (!regex_match(a, checknum)) {
			cout << "Некорректный ввод\n";
			getline(cin, a);
		}
		b[i] = stoi(a);
	}
	permutation(b, 0, 4);
}

