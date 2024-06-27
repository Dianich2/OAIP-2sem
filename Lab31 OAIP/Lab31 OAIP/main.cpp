#include <iostream>
#include <Windows.h>
#include <string>
#include <regex>
#include <chrono>
#include <vector>
using namespace std;
regex checknum("[\\-]?[1-9]+[0-9]*");
class Hashtable {
private:
	int size;
	int currentsize;
	vector<string> keys;
	vector<string> values;
public:
	Hashtable(int siz) {
		size = siz;
		currentsize = 0;
		keys.resize(siz);
		values.resize(siz);
		for (int i = 0; i < siz; i++) {
			keys[i] = "";
			values[i] = "";
		}
	}
	int hashfunc(string cur) {
		int hash = 0;
		for (char sym : cur) {
			hash += sym;
		}
		return hash % size;
	}
	void resize() {
		keys.resize(size * 2);
		values.resize(size * 2);
		size *= 2;
	}
	void insert(string cur, string key) {
		if (currentsize + 1>= size * 0.8) {
			resize();
		}
		int index = hashfunc(key);
		while (!keys[index].empty()) {
			if (keys[index] == key) {
				values[index] = cur;
				return;
			}
			index = (index + 1) % size;
		}
		keys[index] = key;
		values[index] = cur;
		currentsize++;
	}
	void search(string key) {
		int index = hashfunc(key);
		while (!keys[index].empty()) {
			if (keys[index] == key) {
				cout << keys[index] << " -> " << values[index] << '\n';
				return;
			}
			index = (index + 1) % size;
		}
		cout << "�������� �� �������\n";
	}
	void remove(string key) {
		int index = hashfunc(key);
		while (!keys[index].empty()) {
			if (keys[index] == key) {
				keys[index] = "";
				values[index] = "";
				return;
			}
			index = (index + 1) % size;
		}
		cout << "������� �� ������\n";
	}
	void output() {
		for (int i = 0; i < size; i++) {
			cout << i << " �������  ";
			if (keys[i] == "" && values[i] == "") {
				cout << "����� -> �����\n";
			}
			else {
				cout << keys[i] << " -> " << values[i] << '\n';
			}
		}
	}
};

int main() {
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	int choice;
	string b, d;
	cout << "������� ������ �������\n";
	getline(cin, b);
	while (!regex_match(b, checknum)) {
		cout << "������������ ����\n";
		getline(cin, b);
	}
	Hashtable hashtable(stoi(b));
	for (;;)
	{
		cout << "1 - ����� ���-������� �� �����\n";
		cout << "2 - �������� �������\n";
		cout << "3 - ������� �������\n";
		cout << "4 - ����� ������� �� �����\n";
		cout << "0 - �����\n";
		cout << "�������� �����\n";
		getline(cin, b);
		while (b.length() != 1) {
			cout << "������������ ����\n";
			getline(cin, b);
		}
		choice = b[0];
		switch (choice)
		{
		case '0':  exit(0);
		case '1': {
			hashtable.output();
			break;
		}
		case '2': {
			cout << "������� ����\n";
			getline(cin, b);
			cout << "������� ��������\n";
			getline(cin, d);
			hashtable.insert(d, b);
			break;
		}
		case '3': {
			cout << "������� ����\n";
			getline(cin, b);
			hashtable.remove(b);
			break;
		}
		case '4': {
			cout << "������� ����\n";
			getline(cin, b);
			auto start = chrono::high_resolution_clock::now();
			hashtable.search(b);
			auto end = chrono::high_resolution_clock::now();
			auto time = chrono::duration_cast<std::chrono::microseconds>(end - start);
			cout << "�����" << time.count() << '\n';
			break;
		}
		default:  cout << "\n������� �������� �������!\n";
		}
	} 
	return 0;
}