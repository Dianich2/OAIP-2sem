#include <iostream>
#include <Windows.h>
#include <vector>
#include <string>
#include <regex>
using namespace std;

regex checknum("[1-9]+[0-9]*");
regex checkcity("(([A-Z�-�]{1}[a-z�-�]+)||([A-Z�-�]{1}[a-z�-�]+([\\-]{1})[A-Z�-�]{1}[a-z�-�]+))");

struct city { 
	string name;
	string chisl;
};

int currentsize = 0; 

bool operator == (city cit1, city cit2) { 
	return (cit1.name == cit2.name && cit1.chisl == cit2.chisl);
}

class Hashtable { // ����� ���-�������
private:
	vector<vector<city>> table; // ���-�������

public:
	Hashtable(){ // ����������� ���-�������
		table.resize(currentsize);
	}

	int hashfunc(string num) { // ������� ��� �������� ����
		int hash = 0;
		for (int i = 0; i < num.length(); i++) {
			hash = hash ^ num[i];
		}
		return hash % currentsize;
	}

	void add(city cit) { // ������� ��� ���������� ����������
		int index = hashfunc(cit.chisl);
		table[index].push_back(cit);
	}

	void del(city cit) { // ������� ��� �������� ����������
		int index = hashfunc(cit.chisl);
		if (table[index].empty()) {
			cout << "������ ������ ��� � ������\n";
		}
		else {
			bool t = false;
			for (int i = 0; i < table[index].size(); i++) {
				if (cit == table[index][i]) {
					table[index].erase(table[index].begin() + i);
					t = true;
					break;
				}
			}
			if (!t) {
				cout << "������ ������ ��� � ������\n";
			}
		}
	}

	void search(city cit) { // ������� ��� ������ ����������
		int index = hashfunc(cit.chisl);
		if (table[index].empty()) {
			cout << "������ ������ ��� � ������\n";
		}
		else {
			bool t = false;
			for (int i = 0; i < table[index].size(); i++) {
				if (cit == table[index][i]) {
					cout << "���������� �������\n" << "��� ��������� � ������ � �������� " << index << " � " << i + 1 << " ����� ���� ������\n";
					t = true;
					break;
				}
			}
			if (!t) {
				cout << "������ ������ ��� � ������\n";
			}
		}
	}

	void output() { // ������� ��� ������ ��������� ���-�������
		for (int i = 0; i < table.size(); i++) {
			cout << "������ � �������� " << i << '\n';
			if (table[i].empty()) {
				cout << "�����\n";
				cout << '\n';
			}
			else {
				for (int j = 0; j < table[i].size(); j++) {
					cout << "��������: " << table[i][j].name << '\n';
					cout << "����������� ���������: " << table[i][j].chisl << '\n';
					cout << '\n';
				}
			}
		}
	}
};

int main() {
	SetConsoleOutputCP(1251);
	SetConsoleCP(1251);
	int choice;
	string b, d;
	cout << "������� ������ �������\n";
	getline(cin, b);
	while (!regex_match(b, checknum)) {
		cout << "������������ ����\n";
		getline(cin, b);
	}
	currentsize = stoi(b);
	Hashtable table;
	for (;;)
	{
		cout << "1 - ����� ���-������� �� �����\n";
		cout << "2 - �������� �������\n";
		cout << "3 - ������� �������\n";
		cout << "4 - ����� �������\n";
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
			table.output();
			break;
		}
		case '2': {
			cout << "������� �������� ������\n";
			getline(cin, b);
			while (!regex_match(b, checkcity)) {
				cout << "������������ ����\n";
				getline(cin, b);
			}
			cout << "������� ����������� ���������\n";
			getline(cin, d);
			while (!regex_match(d, checknum)) {
				cout << "������������ ����\n";
				getline(cin, d);
			}
			city buf;
			buf.name = b;
			buf.chisl = d;
			table.add(buf);
			break;
		}
		case '3': {
			cout << "������� �������� ������\n";
			getline(cin, b);
			while (!regex_match(b, checkcity)) {
				cout << "������������ ����\n";
				getline(cin, b);
			}
			cout << "������� ����������� ���������\n";
			getline(cin, d);
			while (!regex_match(d, checknum)) {
				cout << "������������ ����\n";
				getline(cin, d);
			}
			city buf;
			buf.name = b;
			buf.chisl = d;
			table.del(buf);
			break;
		}
		case '4': {
			cout << "������� �������� ������\n";
			getline(cin, b);
			while (!regex_match(b, checkcity)) {
				cout << "������������ ����\n";
				getline(cin, b);
			}
			cout << "������� ����������� ���������\n";
			getline(cin, d);
			while (!regex_match(d, checknum)) {
				cout << "������������ ����\n";
				getline(cin, d);
			}
			city buf;
			buf.name = b;
			buf.chisl = d;
			table.search(buf);
			break;
		}
		default:  cout << "\n������� �������� �������!\n";
		}
	}
	return 0;
}