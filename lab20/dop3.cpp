#include <iostream> // 7 вариант
#include <Windows.h>
#include <ctype.h>
#include <cstring>
#include <iomanip>
#include <fstream>
using namespace std;
int main() {
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	ifstream fin("FILE1.txt"); // создаём объект для чтения
	if (!fin.is_open()) { // проверяем на открытие
		cout << "Файл не открыт" << '\n';
	}
	ofstream fout("FILE2.txt"); // создаём объект для записи
	if (!fout.is_open()) { // проверяем на открытие
		cout << "Файл не открыт" << '\n';
	}
	char a[10000];
	int i = 0;
	int length = 0;
	bool t = false;
	bool k = false;
	while (!fin.eof()) { // пока мы не достигли конца файла
		fin.getline(a, 10000); // читаем строку	
		while (a[i] != '\0') { // пока не конец строки, ищем цифры
			if (a[i] != ' ' and !t) {
				t = true;
			}
			else if (a[i] == ' ' and t) {
				k = true;
			}
			else if (t and k and a[i] != ' ') {
				t = false;
				break;
			}
			i++;
		}
		if (t) {
			fout << a;
			fout << '\n';
		}
		i = 0;
		t = false;
		k = false;
	}
	fin.close();
	fout.close();
	ifstream fint("FILE2.txt"); // создаём объект для чтения
	if (!fint.is_open()) { // проверяем на открытие
		cout << "Файл не открыт" << '\n';
	}
	while (!fint.eof()) {
		i = 0;
		fint.getline(a, 10000);
		while (a[i] != '\0') {
			i++;
		}
		if (i == 5) {
			printf("Строка, в которой 5 символов %s\n", a);
		}
	}
	fint.close();
	fout.close();
}
