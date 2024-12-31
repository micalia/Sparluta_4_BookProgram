#pragma once
#include <iostream>
#include <unordered_map>
#include <vector>
#include <string>
#include "Book.h"


using namespace std; // namespace std 사용

class BorrowManager {
private:
	unordered_map<Book, int> stock;
public:
	void initializeStock(Book book, int quantitiy = 3) {
		stock.insert(make_pair(book, quantitiy));
	} //책들 갯수 저장
	void borrowBook(string title) {
		bool findBook = false;
		for (auto& pair : stock)
		{
			if (pair.first.title == title) {
				if (pair.second == 0) {
					cout << "책은 찾았으나 재고가 없습니다." << endl;
				}
				else {
					pair.second--;
					cout << "대여 성공" << endl;
				}
				findBook = true;
			}
		}

		if (findBook == false) {
			cout << "대여할 책이 없음" << endl;
		}

		displayStock();
	}//  책제목으로빌린다
	void returnBook(string title) {
		bool findBook = false;
		for (auto& pair : stock)
		{
			if (pair.first.title == title) {
				pair.second++;
				cout << "반납 성공" << endl;
				findBook = true;
			}
		}

		if (findBook == false) {
			cout << "입력하신 책 정보가 없습니다" << endl;
		}

		displayStock();

	} // 책을 반납한다

	void displayStock() {
		cout << "<<<대여여부 확인>>>" << endl;
		for (auto it = stock.begin(); it != stock.end(); it++) {
			cout << "작가 : " << it->first.author << " / 책이름 : " << it->first.title << " / 재고 : " << it->second << endl;
		}
	} // 대여여부 확인
};