#pragma once
#include <iostream>
#include <unordered_map>
#include <vector>
#include <string>
#include "Book.h"

class BookManager {
private:
	vector<Book> books; // 책 목록 저장

public:
	// 책 추가 메서드
	void addBook(const string& title, const string& author) {
		books.push_back(Book(title, author)); // push_back 사용
		cout << "책이 추가되었습니다: " << title << " by " << author << endl;
	}

	// 모든 책 출력 메서드
	void displayAllBooks() const {
		if (books.empty()) {
			cout << "현재 등록된 책이 없습니다." << endl;
			return;
		}

		cout << "현재 도서 목록:" << endl;
		for (size_t i = 0; i < books.size(); i++) { // 일반적인 for문 사용
			cout << "- " << books[i].title << " by " << books[i].author << endl;
		}
	}

	/*Book* findBookiByTitle(string title);

	Book* findBookByAuthor(string author);*/

	Book* getBookByTitle(string title) {
		for (auto& book : books)
		{
			if (book.title == title) {
				return &book;
			}
		}
		return nullptr;
	};

	Book* getBookByAuthor(string author) {
		for (auto& book : books)
		{
			if (book.author == author) {
				return &book;
			}
		}
		return nullptr;
	};
};