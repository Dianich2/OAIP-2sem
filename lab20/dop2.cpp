#include <iostream> // 4 вариант
#include <Windows.h>
#include <ctype.h>
#include <string>
#include <fstream>
using namespace std;
void fromfile(ofstream& f, char a[]) {
	f << a;
	f << ' ';
}
void infile(ifstream& f, char	a[]) { 
	f.getline(a, 100000);
}
int main() {
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	ofstream fout("FILE1.txt"); 
	if (!fout.is_open()) {
		cout << "‘айл не может быть открыт!\n";
		exit(1);
	}
	cout << "¬ведите строку" << '\n';
	char a[100000];
	cin.getline(a, 100000);
	fromfile(fout, a);
	fout.close();
	ifstream fin("FILE1.txt"); 
	if (!fin.is_open()) {
		cout << "‘айл не может быть открыт!\n";
		exit(1);
	}
	infile(fin, a);
	string long_world = "";
	string current_long_world = "";
	int length = 0;
	int current_length = 0;
	int i = 0;
	bool t = false;
	while (a[i] != '\0') {
		if (a[i] != ' ' and t == false and (a[i] < '0' or a[i] > '9')) {
			t = true;
			current_length += 1;
			current_long_world += a[i];
		}
		else if (a[i] != ' ' and t == true and (a[i] < '0' or a[i] > '9')) {
			current_length += 1;
			current_long_world += a[i];
		}
		else if (a[i] == ' ') {
			t = false;
			if (current_length > length) {
				length = current_length;
				long_world = current_long_world;
			}
			current_length = 0;
			current_long_world = "";
		}
		i++;
	}
	cout << "—амое длинное слово в строке " << long_world << '\n';
	cout << "≈го длина = " << length << '\n';
	fin.close();
}
