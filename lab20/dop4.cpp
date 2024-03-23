#include <iostream> // 7 вариант
#include <Windows.h>
#include <ctype.h>
#include <string>
#include <fstream>
using namespace std;
void fromfile(ofstream& f, char a[]) { // функция для записи в файл
	f << a;
}
void infile(ifstream& f, char	a[]) { // функция для чтения из файла
	f.getline(a, 100000);
}
int main() {
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	ofstream fout("FILE1.txt"); // создание объекта для записи в файл
	if (!fout.is_open()) cout << "Файл не может быть открыт!\n"; // проверка файла на открытие
	cout << "Введите строку" << '\n';
	char a[100000];
	cin.getline(a, 100000);
	fromfile(fout, a);
	fout.close();
	ifstream fin("FILE1.txt"); // создание объекта для чтения из файла
	if (!fin.is_open()) cout << "Файл не может быть открыт!\n"; // проверка файла на открытие
	infile(fin, a);
	int k;
	cout << "Введите номер позиции символа " << '\n';
	cin >> k;
	int world_count = 0;
	bool f = false; // переменная для отслеживания положения в слове
	int i = 0;
	bool t = false; // переменная для отслеживания равенства данного символа пробелу
	bool r = false; // переменная для отслеживания превышения введённого символа длине строки
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
			cout << "Введённый номер позиции превышает длину строки" << '\n';
			r = true;
		}
		i++;
	}
	if (t and !r) {
		cout << "Символ с номером " << k << " это пробел " << '\n';
		cout << "Номер предыдущего слова " << world_count << '\n';
	}
	else if (!r) {
		cout << "Символ с номером " << k << " принадлежит слову с номером " << world_count << '\n';
	}
	fin.close();
}
