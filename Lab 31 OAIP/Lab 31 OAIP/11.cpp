#include <iostream>
#include <Windows.h>
#include <vector>
#include <string>
#include <regex>
using namespace std;

regex checknum("[1-9]+[0-9]*");
regex checkcity("(([A-ZА-Я]{1}[a-zа-я]+)||([A-ZА-Я]{1}[a-zа-я]+([\\-]{1})[A-ZА-Я]{1}[a-zа-я]+))");

struct city { 
	string name;
	string chisl;
};

int currentsize = 0; 

bool operator == (city cit1, city cit2) { 
	return (cit1.name == cit2.name && cit1.chisl == cit2.chisl);
}

class Hashtable { // класс хэш-функции
private:
	vector<vector<city>> table; // хэш-таблица

public:
	Hashtable(){ // конструктор хэш-таблицы
		table.resize(currentsize);
	}

	int hashfunc(string num) { // функция для подсчета хэша
		int hash = 0;
		for (int i = 0; i < num.length(); i++) {
			hash = hash ^ num[i];
		}
		return hash % currentsize;
	}

	void add(city cit) { // функция для добавления информации
		int index = hashfunc(cit.chisl);
		table[index].push_back(cit);
	}

	void del(city cit) { // функция для удаления информации
		int index = hashfunc(cit.chisl);
		if (table[index].empty()) {
			cout << "Такого города нет в списке\n";
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
				cout << "Такого города нет в списке\n";
			}
		}
	}

	void search(city cit) { // функция для поиска информации
		int index = hashfunc(cit.chisl);
		if (table[index].empty()) {
			cout << "Такого города нет в списке\n";
		}
		else {
			bool t = false;
			for (int i = 0; i < table[index].size(); i++) {
				if (cit == table[index][i]) {
					cout << "Информация найдена\n" << "Она находится в ячейке с индексом " << index << " в " << i + 1 << " месте этой ячейки\n";
					t = true;
					break;
				}
			}
			if (!t) {
				cout << "Такого города нет в списке\n";
			}
		}
	}

	void output() { // функция для вывода элементов хэш-таблицы
		for (int i = 0; i < table.size(); i++) {
			cout << "Ячейка с индексом " << i << '\n';
			if (table[i].empty()) {
				cout << "Пусто\n";
				cout << '\n';
			}
			else {
				for (int j = 0; j < table[i].size(); j++) {
					cout << "Название: " << table[i][j].name << '\n';
					cout << "Численность населения: " << table[i][j].chisl << '\n';
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
	cout << "Введите размер таблицы\n";
	getline(cin, b);
	while (!regex_match(b, checknum)) {
		cout << "Некорректный ввод\n";
		getline(cin, b);
	}
	currentsize = stoi(b);
	Hashtable table;
	for (;;)
	{
		cout << "1 - вывод хеш-таблицы на экран\n";
		cout << "2 - добавить элемент\n";
		cout << "3 - удалить элемент\n";
		cout << "4 - найти элемент\n";
		cout << "0 - выход\n";
		cout << "сделайте выбор\n";
		getline(cin, b);
		while (b.length() != 1) {
			cout << "Некорректный ввод\n";
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
			cout << "введите Название города\n";
			getline(cin, b);
			while (!regex_match(b, checkcity)) {
				cout << "Некорректный ввод\n";
				getline(cin, b);
			}
			cout << "введите численность населения\n";
			getline(cin, d);
			while (!regex_match(d, checknum)) {
				cout << "Некорректный ввод\n";
				getline(cin, d);
			}
			city buf;
			buf.name = b;
			buf.chisl = d;
			table.add(buf);
			break;
		}
		case '3': {
			cout << "введите Название города\n";
			getline(cin, b);
			while (!regex_match(b, checkcity)) {
				cout << "Некорректный ввод\n";
				getline(cin, b);
			}
			cout << "введите численность населения\n";
			getline(cin, d);
			while (!regex_match(d, checknum)) {
				cout << "Некорректный ввод\n";
				getline(cin, d);
			}
			city buf;
			buf.name = b;
			buf.chisl = d;
			table.del(buf);
			break;
		}
		case '4': {
			cout << "введите Название города\n";
			getline(cin, b);
			while (!regex_match(b, checkcity)) {
				cout << "Некорректный ввод\n";
				getline(cin, b);
			}
			cout << "введите численность населения\n";
			getline(cin, d);
			while (!regex_match(d, checknum)) {
				cout << "Некорректный ввод\n";
				getline(cin, d);
			}
			city buf;
			buf.name = b;
			buf.chisl = d;
			table.search(buf);
			break;
		}
		default:  cout << "\nВведена неверная команда!\n";
		}
	}
	return 0;
}