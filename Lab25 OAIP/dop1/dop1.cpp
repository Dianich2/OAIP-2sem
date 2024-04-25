#include <iostream>
#include<Windows.h>
#include <conio.h>
#include <string>
#include <regex>
using namespace std;

regex doublenum("([\\-]?)([0-9]+)|([\\-]?)([0-9]+)([\\.]{1})([0-9]+)");
int Maxsize = 0;

struct Node { 
  double num;
  Node* next = NULL;
};

struct queue { 
  int size = 0;
  Node* first = NULL;
  Node* last = NULL;
};

void push(queue*& q, double n) {
  if (q->size >= Maxsize) {
    cout << "������� �����������\n";
  }
  else {
    if (q->first == NULL) {
      q->first = q->last = new Node;
      q->first->num = q->last->num = n;
    }
    else {
      q->last = q->last->next = new Node;
      q->last->num = n;
    }
    q->size++;
  }
}

void pop(queue*& q) { 
  if (q->first == NULL) {
    cout << "������� �����\n";
  }
  else {
    Node* temp = q->first;
    q->first = q->first->next;
    if (q->first == NULL) {
      q->last = NULL;
    }
    q->size--;
    delete temp;
    cout << '\n';
  }
}

double top(queue*& q) { 
  if (q->first == NULL) {
    return 0;
  }
  return q->first->num;
}

void output(queue*& q) { 
  queue* p = new queue;
  if (q->first == NULL) {
    cout << "������� �����\n";
  }
  else {
    cout << "NULL <-- ";
    while (q->first) {
      cout << q->first->num << " <-- ";
      push(p, q->first->num);
      q->first = q->first->next;
    }
    cout << "NULL\n";
    q = p;
  }
  cout << '\n';
}

int search(queue*& q) {
  double max = -1000000;
  int maxpoz = 0;
  int currentpoz = 0;
  queue* p = new queue;
  while (q->first) {
    if (q->first->num > max) {
      max = q->first->num;
      maxpoz = currentpoz;
    }
    push(p, q->first->num);
    q->first = q->first->next;
    currentpoz++;
  }
  q = p;
  return maxpoz;
}

int main()
{
  SetConsoleCP(1251);
  SetConsoleOutputCP(1251);
  queue* q = new queue;
  char choice;
  cout << "������� ������������ ������ ��� �������\n";
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
    cout << "������������ ����\n";
    getline(cin, a);
    t = true;
  }
  Maxsize = stoi(a);
  do {
    cout << "�������:\n";
    cout << "1 - ��� ���������� �������� � �������\n";
    cout << "2 - ��� �������� ������� �������� �� �������\n";
    cout << "3 - ��� ������ ���� ��������� �������\n";
    cout << "4 - ��� ������������ ������ ���� ��������� �������, ����� ������������ ������� ���� ������\n";
    cout << "5 - ��� ������\n";
    getline(cin, a);
    while (a.length() != 1) {
      cout << "������������ ����\n";
      getline(cin, a);
    }
    choice = a[0];
    switch (choice) {

    case '1': {
      double n;
      cout << "������� ����� ��� ���������� � �������\n";
      getline(cin, a);
      while (!regex_match(a, doublenum)) {
        cout << "������������ ����\n";
        getline(cin, a);
      }
      n = stof(a);
      push(q, n);
      break;
    }

    case '2': {
      pop(q);
      break;
    }

    case '3': {
      output(q);
      break;
    }

    case '4': {
      int a = search(q);
      for (int i = 0; i < a; i++) {
        double f = q->first->num;
        pop(q);
        push(q, f);
      }
      break;
    }

    case '5': {
      break;
    }

    default: {
      cout << "������������ ����\n";
      break;
    }

    }
  } while (choice != '5');
}

