#include <Windows.h> // 13 вариант
#include <ctype.h>
#include <string>
#include <fstream>
#include <iostream>
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
	int skobki[] = { 0, 0, 0, 0, 0, 0, 0, 0 }; // массив для отслеживания вхождений скобок разных видов ()[]<>{}
	int i = 0;
	while (a[i] != '\0') {
		if (a[i] == '(') {
			skobki[0] = 1;
		}
		else if (a[i] == ')') {
			skobki[1] = 1;
		}
		else if (a[i] == '[') {
			skobki[2] = 1;
		}
		else if (a[i] == ']') {
			skobki[3] = 1;
		}
		else if (a[i] == '<') {
			skobki[4] = 1;
		}
		else if (a[i] == '>') {
			skobki[5] = 1;
		}
		else if (a[i] == '{') {
			skobki[6] = 1;
		}
		else if (a[i] == '}') {
			skobki[7] = 1;
		}
		i++;
	}
	int count = 0;
	for (int i = 0; i < 8; i++) {
		count += skobki[i];
	}
	if (count == 1) {
		cout << "В строке " << count << " вид скобок";
	}
	else if (count > 1 and count < 5) {
		cout << "В строке " << count << " вида скобок";
	}
	else {
		cout << "В строке " << count << " видов скобок";
	}
	fin.close();
}
