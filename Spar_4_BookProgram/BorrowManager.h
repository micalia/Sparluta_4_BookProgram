#pragma once
#include <iostream>
#include <unordered_map>
#include <vector>
#include <string>
#include "Book.h"


using namespace std; // namespace std ���

class BorrowManager {
private:
	unordered_map<Book, int> stock;
public:
	void initializeStock(Book book, int quantitiy = 3) {
		stock.insert(make_pair(book, quantitiy));
	} //å�� ���� ����
	void borrowBook(string title) {
		bool findBook = false;
		for (auto& pair : stock)
		{
			if (pair.first.title == title) {
				if (pair.second == 0) {
					cout << "å�� ã������ ��� �����ϴ�." << endl;
				}
				else {
					pair.second--;
					cout << "�뿩 ����" << endl;
				}
				findBook = true;
			}
		}

		if (findBook == false) {
			cout << "�뿩�� å�� ����" << endl;
		}

		displayStock();
	}//  å�������κ�����
	void returnBook(string title) {
		bool findBook = false;
		for (auto& pair : stock)
		{
			if (pair.first.title == title) {
				pair.second++;
				cout << "�ݳ� ����" << endl;
				findBook = true;
			}
		}

		if (findBook == false) {
			cout << "�Է��Ͻ� å ������ �����ϴ�" << endl;
		}

		displayStock();

	} // å�� �ݳ��Ѵ�

	void displayStock() {
		cout << "<<<�뿩���� Ȯ��>>>" << endl;
		for (auto it = stock.begin(); it != stock.end(); it++) {
			cout << "�۰� : " << it->first.author << " / å�̸� : " << it->first.title << " / ��� : " << it->second << endl;
		}
	} // �뿩���� Ȯ��
};