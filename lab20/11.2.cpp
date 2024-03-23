#include <iostream> //11
#include <Windows.h>
#include <ctype.h>
#include <string>
#include <fstream>
using namespace std;
void fromfile(ofstream& f, char a[]) { // функция для записи в файл
	f << a;
	f << ' ';
	f << '\n';
}
void infile(ifstream& f, char	a[]) { // функция для чтения из файла
	f.getline(a, 100000);
}
int main() {
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	ofstream fout("FILE1.txt"); 
	if (!fout.is_open()) {
		cout << "Файл не может быть открыт!\n"; exit(1);
	}
	cout << "Введите две строки" << '\n';
	char a[100000];
	for (int i = 0; i < 2; i++) {
		cin.getline(a, 100000);
		fromfile(fout, a);
	}
	fout.close();
	ifstream fin("FILE1.txt"); 
	if (!fin.is_open()) {
		cout << "Файл не может быть открыт!\n"; exit(1);
	} 
	infile(fin, a);
	int i = 0;
	bool t = false;
	int length = 100000;
	int current_length = 0;
	string stroka = "";
	string current_stroka = "";
	while (a[i] != '\0') {
		if (a[i] != ' ' and !t) {
			current_length += 1;
			current_stroka += a[i];
			t = true;
		}
		else if (a[i] != ' ' and t) {
			current_length += 1;
			current_stroka += a[i];
		}
		else if (a[i] == ' ' and t) {
			t = false;
			if (current_length < length) {
				stroka = current_stroka;
				length = current_length;
			}
			current_length = 0;
			current_stroka = "";
		}
		i++;
	}
	cout << "В первой строке первое самое короткое слово " << stroka << '\n';
	cout << "Его длина " << length << '\n';
	stroka = "";
	length = 0;
	i = 0;
	infile(fin, a);
	while (a[i] != '\0') {
		if (a[i] != ' ' and !t) {
			current_length += 1;
			current_stroka += a[i];
			t = true;
		}
		else if (a[i] != ' ' and t) {
			current_length += 1;
			current_stroka += a[i];
		}
		else if (a[i] == ' ' and t) {
			t = false;
			if (current_length > length) {
				stroka = current_stroka;
				length = current_length;
			}
			current_length = 0;
			current_stroka = "";
		}
		i++;
	}
	cout << "Во второй строке первое самое длинное слово " << stroka << '\n';
	cout << "Его длина " << length << '\n';
	fin.close();
}
