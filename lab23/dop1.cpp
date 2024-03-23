#include <iostream>
#include<Windows.h>
#include <conio.h>
#include <vector>
#include <fstream>
#include <string>
#include <regex>
using namespace std;

struct list // ��������� ��� ������������ ������
{
  int num;
  list* next;
};

regex check("[\\-0-9]+");
list* first = NULL; // ��������� �� ������ �������
int number; // ���������� ��� �������� �����

void input(list*& first) { // ������� ��� ���������� ����� � ������
  string a;
  cout << "������� ����� �����\n";
  getline(cin, a);
  getline(cin, a);
  while (!regex_match(a, check)) {
    cout << "������������ ����\n";
    getline(cin, a);
  }
  number = stoi(a);
  list* newp = new list;
  if (newp != NULL) {
    newp->num = number;
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
    cout << "������� �����, ������� ������ �������\n";
    string a;
    getline(cin, a);
    getline(cin, a);
    if (a != "") {
      if (a[a.length() - 1] == '\n') {
        a.erase(a.length() - 1);
      }
    }
    while (!regex_match(a, check)) {
      cout << "������������ ����\n";
      getline(cin, a);
    }
    number = stoi(a);
    list* prev, * current, * temp;
    if (number == first->num) {
      temp = first;
      first = first->next;
      delete temp;
    }
    else {
      prev = first;
      current = first->next;
      while (current != NULL and number != current->num) {
        prev = current;
        current = current->next;
      }
      if (current != NULL) {
        temp = current;
        prev->next = current->next;
        delete temp;
      }
      else {
        cout << "����� �� �������\n";
      }
    }
  }
  cout << '\n';
}


void search(list* fir) { // ������� ��� ������ ����� ������������� ��������� 
  int sum = 0;
  while (fir != NULL) {
    if (fir->num > 0) {
      sum += fir->num;
    }
    fir = fir->next;
  }
  if (sum == 0) {
    cout << "� ������� ��� ������������� �����\n";
  }
  else {
    cout << "����� = " << sum << '\n';
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
      cout << " --> " << fir->num;
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
      fout << buf.num << '\n';
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
    string a;
    getline(fin, a);
    if (a == "") {
      cout << "���� ����\n";
      return;
    }
    if (a != "") {
      if (a[a.length() - 1] == '\n') {
        a.erase(a.length() - 1);
      }
    }
    while (!regex_match(a, check)) {
      cout << "������������ ����������\n";
      cout << "���������� ������ ����������\n";
      return;
    }
    buf.num = stoi(a);
    while (!fin.eof()) {
      list* newp = new list;
      if (newp != NULL) {
        newp->num = buf.num;
        newp->next = first;
        first = newp;
        getline(fin, a);
        if (a != "") {
          if (a[a.length() - 1] == '\n') {
            a.erase(a.length() - 1);
          }
        }
        else {
          return;
        }
        while (!regex_match(a, check)) {
          cout << "������������ ����������\n";
          cout << "���������� ������ ����������\n";
          return;
        }
        buf.num = stoi(a);
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
  do {
    cout << "�������:\n";
    cout << "1 - ��� ����� ������ ����� � ���������� � ���������� � ������ ������\n";
    cout << "2 - ��� �������� �������� �� ������\n";
    cout << "3 - ��� ������ ����� ������������� ���������\n";
    cout << "4 - ��� ������ ��������� ������ � �������\n";
    cout << "5 - ��� ������ ������ � ����\n";
    cout << "6 - ��� ������ ��������� ������ �� �����\n";
    cout << "7 - ��� ������\n";
    cin >> choice;
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
