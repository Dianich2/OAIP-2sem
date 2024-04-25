#include <iostream>
#include<Windows.h>
#include "func.h"
#include <string>
#include <fstream>
#include <regex>
using namespace std;

extern regex checknum;

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
		Stack *temp = myst;
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
			fout << (buf.data) << ' ';
			myst = myst->next;
		}
		fout.close();
	}
}


void fromfile(Stack* &myst) {
	Stack buf;
	ifstream fin("t.dat");
	if (fin.fail()) {
		cout << "������ �������� �����\n";
	}
	else {
		string b;
		while (!fin.eof()) {
			fin >> b;
			if (fin.eof()) {
				return;
			}
			if (!regex_match(b, checknum)) {
				cout << "������������ ������\n";
				cout << "���������� ������ ����������\n";
				return;
			}
			buf.data = stoi(b);
			push(myst, buf.data);
		}
		fin.close();
	}
}


void output_clean(Stack *&myst) {
	if (myst == NULL) {
		cout << "���� ����\n";
	}
	else {
		while (myst != NULL) {
			pop(myst);
		}
	}
}


void del_3(Stack* &myst) {
	Stack* e = nullptr;
	bool t = false;
	if (myst == NULL) {
		cout << "���� ����\n";
		return;
	}
	while (myst) {
		if (myst->data % 3 == 0 && myst->data != 0) {
			pop(myst);
			t = true;
		}
		else {
			push(e, myst->data);
			myst = myst->next;
		}
	}
	if (!t) {
		cout << "� ����� ��� ���������, ������� ������ 3\n";
	}
	myst = e;
}