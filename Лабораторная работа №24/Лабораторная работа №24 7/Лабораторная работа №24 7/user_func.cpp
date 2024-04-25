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
		cout << "���� ����\n";
	}
	else {
		cout << "����������� ����� = " << myst->data << '\n';
		Stack* temp = myst;
		myst = myst->next;
		delete temp;
	}
}


void tofile(Stack* myst) {
	Stack buf;
	ofstream fout("t.dat");
	if (fout.fail()) {
		cout << "������ �������� �����\n";
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
		cout << "������ �������� �����\n";
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
		cout << "���� ����\n";
	}
	else {
		while (myst != NULL) {
			pop(myst);
		}
	}
}


void del_great_100(Stack*& myst) {
	Stack* e = nullptr;
	bool t = false;
	while (myst) {
		if (myst->data > 100 and !t) {
			pop(myst);
			t = true;
		}
		else {
			push(e, myst->data);
			myst = myst->next;
		}
	}
	if (!t) {
		cout << "� ����� ���������, ������� ������ 100\n";
	}
	myst = e;
}