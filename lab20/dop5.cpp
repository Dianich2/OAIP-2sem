#include <iostream> // 13 вариант
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
	bool t = false;
	int world_count = 0;
	while (!fin.eof()) { // пока мы не достигли конца файла
		fin.getline(a, 10000); // читаем строку	
		while (a[i] != '\0') { // пока не конец строки, считаем слова
			if (a[i] != ' ' and !t) {
				t = true;
				world_count += 1;
			}
			else if (a[i] == ' ' and t) {
				t = false;
			}
			i++;
		}
		if (world_count > 2) {
			fout << a;
			fout << ' ';
			fout << '\n';
		}
		i = 0;
		t = false;
		world_count = 0;
	}
	fin.close();
	fout.close();
	ifstream fint("FILE2.txt"); // создаём объект для чтения
	if (!fint.is_open()) { // проверяем на открытие
		cout << "Файл не открыт" << '\n';
	}
	int current_letter_count = 0;
	int letter_count = 0;
	int world = 0;
	while (!fint.eof()) { // пока не конец файла
		i = 0;
		fint.getline(a, 10000);
		while (a[i] != '\0') { // пока не конец строки, ищем слово, в котором больше всего гласных(если есть несколько слов, с одинаковым количеством гласных, то ищем первое)
			if (a[i] != ' ' and !t) {
				t = true;
				world_count += 1;
				if (a[i] == 'A' or a[i] == 'a' or a[i] == 'E' or a[i] == 'e' or a[i] == 'I' or a[i] == 'i' or a[i] == 'O' or a[i] == 'o' or a[i] == 'U' or a[i] == 'u' or a[i] == 'Y' or a[i] == 'y') {
					current_letter_count += 1;
				}
			}
			else if (a[i] != ' ' and t) {
				if (a[i] == 'A' or a[i] == 'a' or a[i] == 'E' or a[i] == 'e' or a[i] == 'I' or a[i] == 'i' or a[i] == 'O' or a[i] == 'o' or a[i] == 'U' or a[i] == 'u' or a[i] == 'Y' or a[i] == 'y') {
					current_letter_count += 1;
				}
			}
			else if (a[i] == ' ') {
				t = false;
				if (current_letter_count > letter_count) {
					letter_count = current_letter_count;
					world = world_count;
				}
				current_letter_count = 0;
			}
			i++;
		}
	}
	cout << "Номер слова, в котором больше всего гласных букв " << world << '\n';
	fint.close();
	fout.close();
}
