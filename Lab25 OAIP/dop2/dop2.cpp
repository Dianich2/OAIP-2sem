#include <iostream>
#include<Windows.h>
#include <conio.h>
#include <fstream>
#include <string>
using namespace std;

struct Node { // структура узла очереди
  char symbol;
  Node* next = NULL;
};

struct queue { // структура очереди
  Node* first = NULL;
  Node* last = NULL;
};

void push(queue*& q, char n) { // функция для ввода
  if (q->first == NULL) {
    q->first = q->last = new Node;
    q->first->symbol = q->last->symbol = n;
  }
  else {
    q->last = q->last->next = new Node;
    q->last->symbol = n;
  }
}

int main()
{
  SetConsoleCP(1251);
  SetConsoleOutputCP(1251);
  queue* sym = new queue;
  queue* num = new queue;
  string a;
  ifstream fin("f.txt");
  ofstream fout("g.txt");
  while (!fin.eof()) {
    getline(fin, a);
    for (int i = 0; i < a.size(); i++) {
      if (a[i] >= '0' and a[i] <= '9') {
        push(num, a[i]);
      }
      else {
        push(sym, a[i]);
      }
    }
    while (sym->first != NULL) {
      fout.write((char*)&sym->first->symbol, sizeof(char));
      sym->first = sym->first->next;
    }
    fout << ' ';
    while (num->first != NULL) {
      fout.write((char*)&num->first->symbol, sizeof(char));
      num->first = num->first->next;
    }
    fout << '\n';
  }
  fin.close();
  fout.close();
}
