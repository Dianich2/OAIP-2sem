#include <iostream>
#include<Windows.h>
#include <conio.h>
#include <vector>
#include <fstream>
#include <string>
using namespace std;

struct list // структура для односвязного списка
{
  char symbol;
  list* next;
};


list* first = NULL; // указатель на первый элемент
char symb; // переменная для хранения символа

void input(list*& first) { // функция для добавления символа в список
  cout << "Введите символ\n";
  string str;
  while (true) {
    getline(cin, str);
    if (str.length() == 1) {
      symb = str[0];
      break;
    }
    cout << "Некорректный ввод\n";
  }
  list* newp = new list;
  if (newp != NULL) {
    newp->symbol = symb;
    newp->next = first;
    first = newp;
  }
  else {
    cout << "Произошла ошибка\n";
  }
  cout << '\n';
}



void del(list*& first) { // функция для удаления первого совпадающего элемента с введенным
  if (first == NULL) {
    cout << "Список пуст\n";
  }
  else {
    cout << "Введите символ, который хотите удалить\n";
    string str;
    while (true) {
      getline(cin, str);
      if (str.length() == 1) {
        symb = str[0];
        break;
      }
      cout << "Некорректный ввод\n";
    }
    list* prev, * current, * temp;
    if (symb == first->symbol) {
      temp = first;
      first = first->next;
      delete temp;
    }
    else {
      prev = first;
      current = first->next;
      while (current != NULL and symb != current->symbol) {
        prev = current;
        current = current->next;
      }
      if (current != NULL) {
        temp = current;
        prev->next = current->next;
        delete temp;
      }
      else {
        cout << "Символ не найден\n";
      }
    }
  }
  cout << '\n';
}


void search(list*& first) { // функция для поиска элемента и вывода предыдущего(который находится перед искомым в списке)
  if (first == NULL) {
    cout << "Список пуст\n";
    return;
  }
  cout << "Введите символ, который будем искать\n";
  string str;
  while (true) {
    getline(cin, str);
    if (str.length() == 1) {
      symb = str[0];
      break;
    }
    cout << "Некорректный ввод\n";
  }
  list* current, * prev;
  if (symb == first->symbol) {
    cout << "Символ найден\n";
    cout << "Предыдущего символа нет\n";
  }
  else {
    prev = first;
    current = first->next;
    while (current != NULL and current->symbol != symb) {
      prev = current;
      current = current->next;
    }
    if (current != NULL) {
      cout << "Символ найден\n";
      cout << "Предыдущий символ = " << prev->symbol;
    }
    else {
      cout << "Символ не найден\n";
    }
  }
  cout << '\n';
}


void output(list* fir) { // функция для вывода элементов списка
  if (fir == NULL) {
    cout << "Список пуст\n";
  }
  else {
    cout << "Список:\n";
    while (fir != NULL) {
      cout << " --> " << fir->symbol;
      fir = fir->next;
    }
    cout << " --> NULL\n";
  }
  cout << '\n';
}


void tofile(list* fir) { // функция записи в файл
  list buf;
  ofstream fout("t.txt");
  if (fout.fail()) {
    cout << "Ошибка открытия файла\n";
  }
  else {
    while (fir) {
      buf = *fir;
      fout << buf.symbol << ' ';
      fir = fir->next;
    }
    fout.close();
  }
}

void fromfile(list*& first) { // функция для считывания списка из файла
  list buf;
  first = NULL;
  ifstream fin("t.txt");
  if (fin.fail()) {
    cout << "Ошибка открытия файла\n";
  }
  else {
    string str;
    fin >> str;
    if (str.length() == 1) {
      buf.symbol = str[0];
    }
    else {
        cout << "Некорректные данные\n";
        cout << "Дальнейшее чтение невозможно\n";
        return;
    } 
    while (!fin.eof()) {
      list* newp = new list;
      if (newp != NULL) {
        newp->symbol = buf.symbol;
        newp->next = first;
        first = newp;
        fin >> str;
        if (str.length() == 1) {
          buf.symbol = str[0];
        }
        else {
          cout << "Некорректные данные\n";
          cout << "Дальнейшее чтение невозможно\n";
          return;
        }
      }
    }
    fin.close();
  }
}


int main()
{
  SetConsoleCP(1251);
  SetConsoleOutputCP(1251);
  char choice; // переменная для выбора опции
  string c;
  do {
    cout << "Введите:\n";
    cout << "1 - для ввода символа с клавиатуры и добавления в начало списка\n";
    cout << "2 - для удаления первого подходящего элемента из списка\n";
    cout << "3 - для поиска первого подходящего элемента в списке\n";
    cout << "4 - для вывода элементов списка в консоль\n";
    cout << "5 - для записи списка в файл\n";
    cout << "6 - для чтения элементов списка из файла\n";
    cout << "7 - для выхода\n";
    getline(cin, c);
    while (c == "") {
      getline(cin, c);
    }
    while (c.length() != 1) {
      cout << "Некорректный ввод\n";
      getline(cin, c);
    }
    choice = c[0];
    switch (choice) {
    case '1': {
      input(first);
      break;
    }
    case '2': {
      del(first);
      break;
    }
    case '3': {
      search(first);
      break;
    }
    case '4': {
      output(first);
      break;
    }
    case '5': {
      tofile(first);
      break;
    }
    case '6': {
      fromfile(first);
      break;
    }
    case '7': {
      break;
    }
    default: {
      cout << "Некорректный ввод\n";
      break;
    }
    }
  } while (choice != '7');
}
