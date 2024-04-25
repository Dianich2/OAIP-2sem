#include <iostream>
#include<Windows.h>
#include "func.h"
#include <string>
#include <fstream>
using namespace std;

void push(Stack*& myst, int& n) {
	Stack* temp = new Stack;
	temp->data = n;
	temp->next = myst;
	myst = temp;
}


void pop(Stack*& myst) {
	if (myst == NULL) {
		cout << "Стек пуст\n";
	}
	else {
		cout << "Извлеченное число = " << myst->data << '\n';
		Stack* temp = myst;
		myst = myst->next;
		delete temp;
	}
}


void tofile(Stack* myst) {
	Stack buf;
	ofstream fout("t.dat");
	if (fout.fail()) {
		cout << "Ошибка открытия файла\n";
	}
	else {
		while (myst) {
			buf = *myst;
			fout.write((char*)&buf, sizeof(Stack));
			myst = myst->next;
		}
		fout.close();
	}
}


void fromfile(Stack*& myst) {
	Stack buf;
	ifstream fin("t.dat");
	if (fin.fail()) {
		cout << "Ошибка открытия файла\n";
	}
	else {
		fin.read((char*)&buf, sizeof(Stack));
		while (!fin.eof()) {
			push(myst, buf.data);
			fin.read((char*)&buf, sizeof(Stack));
		}
		fin.close();
	}
}


void output_clean(Stack*& myst) {
	if (myst == NULL) {
		cout << "Стек пуст\n";
	}
	else {
		while (myst != NULL) {
			pop(myst);
		}
	}
}


void del_plus(Stack*& myst) {
	Stack* e = nullptr;
	bool t = false;
	while (myst) {
		if (myst->data > 0 and !t) {
			pop(myst);
			t = true;
		}
		else {
			push(e, myst->data);
			myst = myst->next;
		}
	}
	if (!t) {
		cout << "В стеке нет положительных элементов\n";
	}
	myst = e;
}