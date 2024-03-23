#include <iostream> // 11 вариант
#include <Windows.h>
#include <ctype.h>
#include <cstring>
#include <fstream>
using namespace std;

int main() {
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	ifstream fin("FILE1.txt");
	if (!fin.is_open()) {
		cout << "Файл не может быть открыт!\n"; exit(1);
	}
	ofstream fout("FILE2.txt"); 
	if (!fout.is_open()) {
		cout << "Файл не может быть открыт!\n"; exit(1);
	}
	int kolvo_sim = 0;
	while (!fin.eof()) { 
		char stroka[254];
		fin.getline(stroka, 254);
		bool t = true, k = false;
		int i = 0;
		int length = 0;
		while (stroka[i] != '\0') {
			length++;
			i++;
		}
		for (int i = 0; i < length; i++) {
			if (stroka[i] != ' ' and t == true) {
				t = false;
			}
			else if (t == false and stroka[i] == ' ') {
				k = true;
			}
			else if (t == false and k == true and stroka[i] != ' ') {
				t = true;
				break;
			}
		}

		if (!t) {
			kolvo_sim += length;
			fout << stroka << '\n';
		}
	}
	fin.close();
	fout.close();
	cout << "Количество символов в FILE2 = " << kolvo_sim << '\n';
}
