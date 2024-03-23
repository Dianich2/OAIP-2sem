#include <iostream>
#include <math.h>
#include<Windows.h>
#include <stdio.h>
#include <string>
#include <string.h>
#define _CRT_SECURE_NO_WARNINGS
#define SIZE 30
using namespace std;

struct book { // структура для записей
	char lastname[100]; // фамилия
	char firstname[100]; // имя
	char patronimic[100]; // отчество
	char date[100]; // дата рождения
	char address[100]; // адрес
	char tel[100]; // телефон
	char workplace[100]; // место работы или учебы
	char position[100]; // должность
};

int days_in_month[12] = { 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
struct book book1[SIZE]; // наша структура
int currentsize = 0; // текущий размер структуры
char a; // переменная выбора
FILE* f; // файл для записей

bool visokosny(int y) { // функция для определения високосности года
	if (y % 4 != 0) {
		return 0;
	}
	if (y % 100 != 0) {
		return 1;
	}
	if (y % 400 == 0) {
		return 1;
	}
	return 0;
}

bool check_telephone(string tel) { // проверка телефона
	if (tel.length() != 13) {
		return false;
	}
	if (tel[0] != '+') {
		return false;
	}
	if (tel[1] != '3') {
		return false;
	}
	if (tel[2] != '7') {
		return false;
	}
	if (tel[3] != '5') {
		return false;
	}
	for (int i = 4; i < 13; i++) {
		if (tel[i] < '0' || tel[i] > '9') {
			return false;
		}
	}
	return true;
}

bool checkfio(string f) {
	bool t = false;
	if (f == "" || f == "\n") {
		return 0;
	}
	for (int i = 0; i < f.length(); i++) {
		if (i == 0) {
			if ((f[0] >= 'A' && f[0] <= 'Z') || (f[0] >= 'А' && f[0] <= 'Я')) {
				t = true;
				continue;
			}
			else {
				return 0;
			}
		}
		else if ((f[i] >= 'A' && f[i] <= 'Z') || (f[i] >= 'А' && f[i] <= 'Я') && t) {
			if (f[i - 1] == '-') {
				continue;
			}
			else {
				return 0;
			}
		}
		else if((f[i] >= 'a' && f[i] <= 'z') || (f[i] >= 'а' && f[i] <= 'я')){
			if (f[i - 1] == '-') {
				return 0;
			}
			continue;
		}
		else if(f[i] == '-') {
			continue;
		}
		else {
			return 0;
		}
	}
	return 1;
}

bool check_date(string d) {
	for (int i = 0; i < d.length(); i++) {
		if (d[i] < '0' || d[i] > '9') {
			return 0;
		}
	}
	int a = stoi(d);
	int b = a % 10000; a /= 10000;
	int c = a % 100; a /= 100;
	bool t = visokosny(b);
	if (b > 2018) {
		return 0;
	}
	else if (c <= 0 || c > 12) {
		return 0;
	}
	else if (c != 2 && a > days_in_month[c - 1] || a <= 0) {
		return 0;
	}
	else if (c == 2) {
		if (t) {
			if (a > days_in_month[c - 1]) {
				return 0;
			}
		}
		else {
			if (a > days_in_month[c - 1] - 1) {
				return 0;
			}
		}
	}
}

bool nopatronimic(string a) {
	if (a.length() == 1 && a[0] == '-') {
		return 1;
	}
	return 0;
}

void input() { // функция для ввода с клавиатуры(1)
	if (currentsize < SIZE) {
		cout << "Введите фамилию\n";
		gets_s(book1[currentsize].lastname);
		while (!checkfio(book1[currentsize].lastname)) {
			cout << "Некорректный ввод\n";
			gets_s(book1[currentsize].lastname);
		}
		cout << "Введите имя\n";
		gets_s(book1[currentsize].firstname);
		while (!checkfio(book1[currentsize].firstname)) {
			cout << "Некорректный ввод\n";
			gets_s(book1[currentsize].firstname);
		}
		cout << "Введите отчество\n";
		gets_s(book1[currentsize].patronimic);
		if (!nopatronimic(book1[currentsize].patronimic)) {
			while (!checkfio(book1[currentsize].patronimic)) {
				cout << "Некорректный ввод\n";
				gets_s(book1[currentsize].patronimic);
			}
		}
		cout << "Введите дату рождения в формате(ДДММГГГГ)\n";
		string d;
		getline(cin, d);
		while (!check_date(d)) {
			cout << "Некорректный ввод\n";
			getline(cin, d);
		}
		strcpy_s(book1[currentsize].date, d.c_str());
		cout << "Введите адрес\n";
		gets_s(book1[currentsize].address);
		cout << "Введите телефон\n";
		gets_s(book1[currentsize].tel);
		while (!check_telephone(book1[currentsize].tel)) {
			cout << "Некорректный ввод\n";
			gets_s(book1[currentsize].tel);
		}
		cout << "Введите место работы или учебы\n";
		gets_s(book1[currentsize].workplace);
		cout << "Введите должность\n";
		gets_s(book1[currentsize].position);
		currentsize++;
	}
	else {
		cout << "Введено максимальное количество\n";
	}
	cout << '\n';
}


void out() { // функция для вывода записей
	string ch; // переменная выбора количества выводимых записей
	while (true) { // проверка корректности ввода
		cout << "Выберите:\n";
		cout << "1-для вывода 1 записи\n";
		cout << "2-для вывода всех записей\n";
		getline(cin, ch);
		if(ch.length() != 1) {
			cout << "Некорректный ввод\n";
		}
		if (ch[0] != '2' and ch[0] != '1') {
			cout << "Некорректный ввод\n";
		}
		else {
			break;
		}
	}
	if (ch[0] == '1') { // если выбрана опция вывода 1 записи
		int n; // переменная для номера строки
		cout << "Введите номер записи\n";
		cin >> n;
		if (n - 1 >= currentsize or n - 1 < 0) {
			cout << "Такой записи нет.\n";
		}
		else {
			cout << "Фамилия: " << book1[n - 1].lastname << '\n';
			cout << "Имя: " << book1[n - 1].firstname << '\n';
			cout << "Отчество: " << book1[n - 1].patronimic << '\n';
			cout << "Дата рождения в формате(ДДММГГГГ): " << book1[n - 1].date << '\n';
			cout << "Адрес: " << book1[n - 1].address << '\n';
			cout << "Телефон: " << book1[n - 1].tel << '\n';
			cout << "Место работы или учебы: " << book1[n - 1].workplace << '\n';
			cout << "Должность: " << book1[n - 1].position << '\n';
		}
	}
	else if (ch[0] == '2') { // если выбрана опция вывода всех записей
		if (currentsize == 0) {
			cout << "Записей нет\n";
			return;
		}
		for (int i = 0; i < currentsize; i++) {
			cout << i + 1 << '\n';
			cout << "Фамилия: " << book1[i].lastname << '\n';
			cout << "Имя: " << book1[i].firstname << '\n';
			cout << "Отчество: " << book1[i].patronimic << '\n';
			cout << "Дата рождения в формате(ДДММГГГГ): " << book1[i].date << '\n';
			cout << "Адрес: " << book1[i].address << '\n';
			cout << "Телефон: " << book1[i].tel << '\n';
			cout << "Место работы или учебы: " << book1[i].workplace << '\n';
			cout << "Должность: " << book1[i].position << '\n';
			cout << '\n';
		}
	}
	cout << '\n';
}


void del() { // функция для удаления записи
	int n;
	cout << "Введите номер записи, которую нужно удалить\n";
	cin >> n;
	n--;
	if (n >= currentsize or n < 0) {
		cout << "Такой записи нет\n";
	}
	else {
		for (int i = n; i < currentsize - 1; i++) {
			book1[i] = book1[i + 1];
		}
		currentsize--; // уменьшаем размер массива
	}
	cout << '\n';
}


void search() { // функция для поиска информации по фамилии
	string current_lastname; // переменная для искомой фамилии
	cout << "Введите фамилию\n";
	cin >> current_lastname;
	bool t = false; // переменная-флажок для проверки наличия записи по фамилии
	for (int i = 0; i < currentsize; i++) {
		if (book1[i].lastname == current_lastname) {
			cout << "Запись найдена\n";
			cout << i + 1 << '\n';
			cout << "Фамилия: " << book1[i].lastname << '\n';
			cout << "Имя: " << book1[i].firstname << '\n';
			cout << "Отчество: " << book1[i].patronimic << '\n';
			cout << "Дата рождения в формате(ДДММГГГГ): " << book1[i].date << '\n';
			cout << "Адрес: " << book1[i].address << '\n';
			cout << "Телефон: " << book1[i].tel << '\n';
			cout << "Место работы или учебы: " << book1[i].workplace << '\n';
			cout << "Должность: " << book1[i].position << '\n';
			cout << '\n';
			t = true;
		}
	}
	if (!t) { // если запись не найдена
		cout << "Такой записи нет\n";
	}
	cout << '\n';
}


void input_in_file() {
	if (!fopen_s(&f, "t.txt", "w")) {
		for (int i = 0; i < currentsize; i++) {
			fputs(book1[i].lastname, f);
			fputs("\n", f);
			fputs(book1[i].firstname, f);
			fputs("\n", f);
			fputs(book1[i].patronimic, f);
			fputs("\n", f);
			fputs(book1[i].date, f);
			fputs("\n", f);
			fputs(book1[i].address, f);
			fputs("\n", f);
			fputs(book1[i].tel, f);
			fputs("\n", f);
			fputs(book1[i].workplace, f);
			fputs("\n", f);
			fputs(book1[i].position, f);
			fputs("\n", f);
		}
		fclose(f);
	}
	else {
		cout << "Ошибка открытия файла\n";
	}
	cout << '\n';
}


void output_file() { //функция для считывания из файла и записи в консольное окно
	bool t = false;
	book book2;
	if (!fopen_s(&f, "t.txt", "r")) { // если файл успешно открыт
		currentsize = 0;
		while (!feof(f)) { // пока не конец файла
			fgets(book2.lastname, 100, f);
			if (feof(f)) {
				if (!t) cout << "Файл пуст\n";
				break;
			}
			t = true;
			string d = book2.lastname;
			d.erase(d.length() - 1);
			if (!checkfio(d)) {
				cout << "Файл содержит некорректную информацию\n";
				cout << "Дальнейшее чтение невозможно\n";
				cout << "Исправьте пожалуйста данные\n";
				break;
			}
			strcpy_s(book2.lastname, d.c_str());
			fgets(book2.firstname, 100, f);
			d = book2.firstname;
			d.erase(d.length() - 1);
			if (!checkfio(d)) {
				cout << "Файл содержит некорректную информацию\n";
				cout << "Дальнейшее чтение невозможно\n";
				cout << "Исправьте пожалуйста данные\n";
				break;
			}
			strcpy_s(book2.firstname, d.c_str());
			fgets(book2.patronimic, 100, f);
			d = book2.patronimic;
			d.erase(d.length() - 1);
			if (!nopatronimic(d)) {
				if (!checkfio(d)) {
					cout << "Файл содержит некорректную информацию\n";
					cout << "Дальнейшее чтение невозможно\n";
					cout << "Исправьте пожалуйста данные\n";
					break;
				}
			}
			strcpy_s(book2.patronimic, d.c_str());
			char buf[100];
			fgets(buf, 100, f);
			d = buf;
			d.erase(d.length() - 1);
				if (!check_date(d)) {
					cout << "Файл содержит некорректную информацию\n";
					cout << "Дальнейшее чтение невозможно\n";
					cout << "Исправьте пожалуйста данные\n";
					break;
				}
			strcpy_s(book2.date, d.c_str());
			fgets(book2.address, 100, f);
			d = book2.address;
			d.erase(d.length() - 1);
			strcpy_s(book2.address, d.c_str());
			fgets(book2.tel, 100, f);
			d = book2.tel;
			d.erase(d.length() - 1);
			if(!check_telephone(d)) {
				cout << "Файл содержит некорректную информацию\n";
				cout << "Дальнейшее чтение невозможно\n";
				cout << "Исправьте пожалуйста данные\n";
				break;
			}
			strcpy_s(book2.tel, d.c_str());
			fgets(book2.workplace, 100, f);
			d = book2.workplace;
			d.erase(d.length() - 1);
			strcpy_s(book2.workplace, d.c_str());
			fgets(book2.position, 100, f);
			d = book2.position;
			d.erase(d.length() - 1);
			strcpy_s(book2.position, d.c_str());
			cout << '\n';
			strcpy_s(book1[currentsize].lastname, book2.lastname);
			strcpy_s(book1[currentsize].firstname, book2.firstname);
			strcpy_s(book1[currentsize].patronimic, book2.patronimic);
			strcpy_s(book1[currentsize].date, book2.date);
			strcpy_s(book1[currentsize].address, book2.address);
			strcpy_s(book1[currentsize].tel, book2.tel);
			strcpy_s(book1[currentsize].workplace, book2.workplace);
			strcpy_s(book1[currentsize].position, book2.position);
			currentsize++;
		}
		fclose(f);
	}
	else {
		cout << "Ошибка открытия файла\n";
	}
}

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	string c;
	do {
		cout << "Введите:\n";
		cout << "1-для ввода элементов с клавиатуры\n";
		cout << "2-для вывода элементов в консольное окно\n";
		cout << "3-для удаления переменной\n";
		cout << "4-для поиска информации по фамилии\n";
		cout << "5-для записи информации в файл\n";
		cout << "6-для чтения данных из файла\n";
		cout << "7-для выхода\n";
		getline(cin, c); 
		while (c == "") {
			getline(cin, c);
		}
		while (c.length() != 1) {
			cout << "Некорректный ввод\n";
			getline(cin, c);
		}
		a = c[0];
		switch (a) {
		case '1': { //
			input();
			break;
		}
		case '2': {
			out();
			break;
		}
		case '3': {
			del();
			break;
		}
		case '4': {
			search();
			break;
		}
		case '5': {
			input_in_file();
			break;
		}
		case '6': {
			output_file();
			break;
		}
		case '7': {
			break;
		}
		default: { // если введен символ не из списка
			cout << "Некорректный ввод\n";
			break;
		}
		}
	} while (a != '7'); // если символ = 7, то завершение программы
}
