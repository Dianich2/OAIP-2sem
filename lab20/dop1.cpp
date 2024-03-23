#include <iostream> // 4 вариант
#include <Windows.h>
#include <ctype.h>
#include <cstring>
#include <iomanip>
#include <fstream>
using namespace std;
int main() {
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	ifstream fin("FILE1.txt"); 
	if (!fin.is_open()) { 
		cout << "Файл не открыт" << '\n';
		exit(1);
	}
	ofstream fout("FILE2.txt");
	if (!fout.is_open()) { 
		cout << "Файл не открыт" << '\n';
		exit(1);
	}
	char a[10000];
	int i = 0;
	bool t = false;
	int count_A = 0;
	while (!fin.eof()) { 
		fin.getline(a, 10000);
		while (a[i] != '\0') { 
			if (a[i] >= '0' and a[i] <= '9') {
				t = true;
				break;
			}
			i++;
		}
		if (!t) { 
			fout << a;
			fout << '\n';
		}
		t = false;
		i = 0;
	}
	fin.close();
	fout.close();
	ifstream finf("FILE2.txt");
	if (!finf.is_open()) {
		cout << "Файл не открыт" << '\n';
		exit(1);
	}
	while (!finf.eof()) {
		finf.getline(a, 10000);
		if (a[0] == 'A') {
			count_A++;
		}
	}
	cout << "Количество строк, которые начинаются на А = " << count_A << '\n';
	finf.close();
}
