#include <iostream>
#include<Windows.h>
#include <conio.h>
#include <vector>
#include <fstream>
#include <string>
using namespace std;

struct list // ��������� ��� ������������ ������
{
  char symbol;
  list* next;
};


list* first = NULL; // ��������� �� ������ �������
char symb; // ���������� ��� �������� �������

void input(list*& first) { // ������� ��� ���������� ������� � ������
  cout << "������� ������\n";
  string str;
  while (true) {
    getline(cin, str);
    if (str.length() == 1) {
      symb = str[0];
      break;
    }
    cout << "������������ ����\n";
  }
  list* newp = new list;
  if (newp != NULL) {
    newp->symbol = symb;
    newp->next = first;
    first = newp;
  }
  else {
    cout << "��������� ������\n";
  }
  cout << '\n';
}



void del(list*& first) { // ������� ��� �������� ������� ������������ �������� � ���������
  if (first == NULL) {
    cout << "������ ����\n";
  }
  else {
    cout << "������� ������, ������� ������ �������\n";
    string str;
    while (true) {
      getline(cin, str);
      if (str.length() == 1) {
        symb = str[0];
        break;
      }
      cout << "������������ ����\n";
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
        cout << "������ �� ������\n";
      }
    }
  }
  cout << '\n';
}


void search(list*& first) { // ������� ��� ������ �������� � ������ �����������(������� ��������� ����� ������� � ������)
  if (first == NULL) {
    cout << "������ ����\n";
    return;
  }
  cout << "������� ������, ������� ����� ������\n";
  string str;
  while (true) {
    getline(cin, str);
    if (str.length() == 1) {
      symb = str[0];
      break;
    }
    cout << "������������ ����\n";
  }
  list* current, * prev;
  if (symb == first->symbol) {
    cout << "������ ������\n";
    cout << "����������� ������� ���\n";
  }
  else {
    prev = first;
    current = first->next;
    while (current != NULL and current->symbol != symb) {
      prev = current;
      current = current->next;
    }
    if (current != NULL) {
      cout << "������ ������\n";
      cout << "���������� ������ = " << prev->symbol;
    }
    else {
      cout << "������ �� ������\n";
    }
  }
  cout << '\n';
}


void output(list* fir) { // ������� ��� ������ ��������� ������
  if (fir == NULL) {
    cout << "������ ����\n";
  }
  else {
    cout << "������:\n";
    while (fir != NULL) {
      cout << " --> " << fir->symbol;
      fir = fir->next;
    }
    cout << " --> NULL\n";
  }
  cout << '\n';
}


void tofile(list* fir) { // ������� ������ � ����
  list buf;
  ofstream fout("t.txt");
  if (fout.fail()) {
    cout << "������ �������� �����\n";
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

void fromfile(list*& first) { // ������� ��� ���������� ������ �� �����
  list buf;
  first = NULL;
  ifstream fin("t.txt");
  if (fin.fail()) {
    cout << "������ �������� �����\n";
  }
  else {
    string str;
    fin >> str;
    if (str.length() == 1) {
      buf.symbol = str[0];
    }
    else {
        cout << "������������ ������\n";
        cout << "���������� ������ ����������\n";
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
          cout << "������������ ������\n";
          cout << "���������� ������ ����������\n";
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
  char choice; // ���������� ��� ������ �����
  string c;
  do {
    cout << "�������:\n";
    cout << "1 - ��� ����� ������� � ���������� � ���������� � ������ ������\n";
    cout << "2 - ��� �������� ������� ����������� �������� �� ������\n";
    cout << "3 - ��� ������ ������� ����������� �������� � ������\n";
    cout << "4 - ��� ������ ��������� ������ � �������\n";
    cout << "5 - ��� ������ ������ � ����\n";
    cout << "6 - ��� ������ ��������� ������ �� �����\n";
    cout << "7 - ��� ������\n";
    getline(cin, c);
    while (c == "") {
      getline(cin, c);
    }
    while (c.length() != 1) {
      cout << "������������ ����\n";
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
      cout << "������������ ����\n";
      break;
    }
    }
  } while (choice != '7');
}
