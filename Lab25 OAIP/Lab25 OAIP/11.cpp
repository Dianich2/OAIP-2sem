#include <iostream>
#include<Windows.h>
#include <conio.h>
#include <string>
#include <fstream>
using namespace std;

int Maxsize = 0;

struct Node { 
  char sym;
  Node* next = nullptr;
};

struct queue {
  int size = 0;
  Node* first = nullptr;
  Node* last = nullptr;
};

void push(queue*& q, char n) { // функция для ввода
  if (q->size >= Maxsize) {
    cout << "Очередь переполнена\n";
  }
  else {
    if (q->first == NULL) {
      q->first = q->last = new Node;
      q->first->sym = q->last->sym = n;
    }
    else {
      q->last = q->last->next = new Node;
      q->last->sym = n;
    }
    q->size++;
  }
}

void pop(queue*& q) { // функция для удаления
  if (q->first == NULL) {
    cout << "Очередь пуста\n";
  }
  else {
    Node* temp = q->first;
    q->first = q->first->next;
    if (q->first == NULL) {
      q->last = NULL;
    }
    q->size--;
    delete temp;
  }
  cout << '\n';
}

char top(queue*& q) { // функция для возвращения значения 1 элемента
  if (q->first == NULL) {
    return 0;
  }
  return q->first->sym;
}

void output(queue*& q) { // функция для вывода
  queue* p = new queue;
  if (q->first == NULL) {
    cout << "Очередь пуста\n";
  }
  else {
    cout << "NULL <-- ";
    while (q->first) {
      cout << q->first->sym << " <-- ";
      push(p, q->first->sym);
      q->first = q->first->next;
    }
    cout << "NULL\n";
    q = p;
  }
  cout << '\n';
}

void clear(queue* q) {
  q->first = NULL;
  q->last = NULL;
  q->size = 0;
  return;
}

void tofile(queue *&q, string f) {
  queue* p = new queue;
  ofstream fout(f);
  if (fout.fail()) {
    cout << "Ошибка открытия файла\n";
    return;
  }
  if (q->first == NULL) {
    cout << "Очередь пуста\n";
  }
  else {
    while (q->first) {
      fout << q->first->sym << ' ';
      push(p, q->first->sym);
      q->first = q->first->next;
    }
    q = p;
    fout.close();
  }
}

void fromfile(queue* &q, string f) {
  ifstream fin(f);
  bool t = true;
  if (f == "little.txt") {
    t = false;
  }
  if (fin.fail()) {
    cout << "Ошибка открытия файла\n";
    return;
  }
  q->first = NULL;
  q->last = NULL;
  q->size = 0;
  string a;
  while (!fin.eof()) {
    fin >> a;
    if (fin.eof()) {
      return;
    }
    if (a.length() > 1 || a.length() == 0 || (t && (a[0] < 'A' || a[0] > 'Z')) || (!t && (a[0] < 'a' || a[0] > 'z'))) {
      cout << "В файле некорректные данные\n";
      cout << "Дальнейшее чтение невозможно\n";
      return;
    }
    if (q->size >= Maxsize) {
      cout << "Оставшаяся информация не помещается в очередь\n";
      cout << "Дальнейшее чтение невозможно\n";
      return;
    }
    push(q, a[0]);
  }
  fin.close();
}

int main()
{
  SetConsoleCP(1251);
  SetConsoleOutputCP(1251);
  queue* little = new queue;
  queue* large = new queue;
  char choice;
  cout << "Введите максимальный размер для очереди\n";
  string a;
  bool t = true;
  getline(cin, a);
  while (true) {
    if (a[0] == '0' || a == "") {
      t = false;
    }
    else {
      for (int i = 0; i < a.length(); i++) {
        if (a[i] < '0' || a[i] > '9') {
          t = false;
        }
      }
    }
    if (t) {
      break;
    }
    cout << "Некорректный ввод\n";
    getline(cin, a);
    t = true;
  }
  Maxsize = stoi(a);
  cout << "Данная программа считывает символ.\nЕсли он является строчной буквой латинского алфавита, то она преобразует его в прописную и помещает во 2 очередь, если прописной буквой латинского алфавита - преобразует в строчную и помещает в первую очередь.\nОстальные символы будут игнорироваться\n";
  do {
    cout << "Введите:\n";
    cout << "1 - для добавления элемента в очередь\n";
    cout << "2 - для удаления первого элемента из очереди\n";
    cout << "3 - для вывода всех элементов очереди\n";
    cout << "4 - для вывода первого элемента из очереди\n";
    cout << "5 - для очистки очереди\n";
    cout << "6 - для записи в файл\n";
    cout << "7 - для чтения из файла\n";
    cout << "8 - для освобождения памяти и выхода \n";
    getline(cin, a);
    while (a.length() != 1) {
      cout << "Некорректный ввод\n";
      getline(cin, a);
    }
    choice = a[0];
    switch (choice) {
    case '1': {
      char n;
      cout << "Введите символ для добавления в очередь\n";
      getline(cin, a);
      while(a.length() != 1) {
        cout << "Некорректный ввод\n";
        getline(cin, a);
      }
      n = a[0];
      if (n >= 'A' and n <= 'Z') {
        n = n - 'A' + 'a';
        push(little, n);
      }
      else if (n >= 'a' and n <= 'z') {
        n = n - 'a' + 'A';
        push(large, n);
      }
      else {
        cout << "Символ не является буквой латинского алфавита\n";
        cout << '\n';
      }
      break;
    }

    case '2': {
      char c;
      cout << "Введите:\n";
      cout << "1 - для удаления элемента из очереди с прописными буквами\n";
      cout << "2 - для удаления элемента из очереди со строчными буквами\n";
      getline(cin, a);
      while (a.length() != 1) {
        cout << "Некорректный ввод\n";
        getline(cin, a);
      }
      c = a[0];
      switch (c) {

      case '1': {
        pop(large);
        break;
      }

      case '2': {
        pop(little);
        break;
      }

      default: {
        cout << "Некорректный ввод\n";
        break;
      }
      }
      break;
    }

    case '3': {
      char c;
      cout << "Введите:\n";
      cout << "1 - для вывода элементов очереди с прописными буквами\n";
      cout << "2 - для вывода элементов очереди со строчными буквами\n";
      getline(cin, a);
      while (a.length() != 1) {
        cout << "Некорректный ввод\n";
        getline(cin, a);
      }
      c = a[0];
      switch (c) {

      case '1': {
        output(large);
        break;
      }

      case '2': {
        output(little);
        break;
      }

      default: {
        cout << "Некорректный ввод\n";
        break;
      }
      }
      break;
    }

    case '4': {
      char c;
      cout << "Введите:\n";
      cout << "1 - для получения элемента из очереди с прописными буквами\n";
      cout << "2 - для получения элемента из очереди со строчными буквами\n";
      getline(cin, a);
      while (a.length() != 1) {
        cout << "Некорректный ввод\n";
        getline(cin, a);
      }
      c = a[0];
      switch (c) {

      case '1': {
        int a = top(large);
        if (a) {
          cout << "Первый элемент очереди = " << top(large) << '\n';
        }
        else {
          cout << "Очередь пуста\n";
        }
        break;
      }

      case '2': {
        int a = top(little);
        if (a) {
          cout << "Первый элемент очереди = " << top(little) << '\n';
        }
        else {
          cout << "Очередь пуста\n";
        }
        break;
      }

      default: {
        cout << "Некорректный ввод\n";
        break;
      }
      }
      break;
    }
    
    case '5': {
      char c;
      cout << "Введите:\n";
      cout << "1 - для очистки очереди с прописными буквами\n";
      cout << "2 - для очистки очереди со строчными буквами\n";
      getline(cin, a);
      while (a.length() != 1) {
        cout << "Некорректный ввод\n";
        getline(cin, a);
      }
      c = a[0];
      switch (c) {

      case '1': {
        clear(large);
        break;
      }

      case '2': {
        clear(little);
        break;
      }

      default: {
        cout << "Некорректный ввод\n";
        break;
      }
      }
      break;
    }

    case '6': {
      char c;
      cout << "Введите:\n";
      cout << "1 - для записи очереди с прописными буквами\n";
      cout << "2 - для записи очереди со строчными буквами\n";
      getline(cin, a);
      while (a.length() != 1) {
        cout << "Некорректный ввод\n";
        getline(cin, a);
      }
      c = a[0];
      switch (c) {

      case '1': {
        tofile(large, "large.txt");
        break;
      }

      case '2': {
        tofile(little, "little.txt");
        break;
      }

      default: {
        cout << "Некорректный ввод\n";
        break;
      }
      }
      break;
    }

    case '7': {
      char c;
      cout << "Введите:\n";
      cout << "1 - для чтения очереди с прописными буквами\n";
      cout << "2 - для чтения очереди со строчными буквами\n";
      getline(cin, a);
      while (a.length() != 1) {
        cout << "Некорректный ввод\n";
        getline(cin, a);
      }
      c = a[0];
      switch (c) {

      case '1': {
        fromfile(large, "large.txt");
        break;
      }

      case '2': {
        fromfile(little, "little.txt");
        break;
      }

      default: {
        cout << "Некорректный ввод\n";
        break;
      }
      }
      break;
    }

    case '8': {
      delete little;
      delete large;
      break;
    }

    default: {
      cout << "Некорректный ввод\n";
      break;
    }

    }
  } while (choice != '8');
}
