#pragma once
#include <iostream>
#include <unordered_map>
#include <vector>
#include <string>
#include "Book.h"

class BookManager {
private:
	vector<Book> books; // å ��� ����

public:
	// å �߰� �޼���
	void addBook(const string& title, const string& author) {
		books.push_back(Book(title, author)); // push_back ���
		cout << "å�� �߰��Ǿ����ϴ�: " << title << " by " << author << endl;
	}

	// ��� å ��� �޼���
	void displayAllBooks() const {
		if (books.empty()) {
			cout << "���� ��ϵ� å�� �����ϴ�." << endl;
			return;
		}

		cout << "���� ���� ���:" << endl;
		for (size_t i = 0; i < books.size(); i++) { // �Ϲ����� for�� ���
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