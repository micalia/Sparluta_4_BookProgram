#include <iostream>
#include <unordered_map>
#include <vector>
#include <string>


using namespace std; // namespace std 사용

class Book {
public:
	string title;
	string author;

	Book(const string& title, const string& author)
		: title(title), author(author) {}

	bool operator==(const Book& other) const
	{
		return (title == other.title
			&& author == other.author);
	}
};

template <>
struct std::hash<Book>
{
	std::size_t operator()(const Book& k) const
	{
		using std::size_t;
		using std::hash;
		using std::string;

		auto val = (hash<string>()(k.title) ^ (hash<string>()(k.author) << 1)) >> 1;
		cout<<"hash 화 : " << val << endl;

		return val;
	}
};

class BorrowManager {
private:
	unordered_map<Book, int> stock;
public:
	void initializeStock(Book book, int quantitiy = 3){
		stock.insert(make_pair(book, quantitiy));
	} //책들 갯수 저장
	void borrowBook(string title){
		bool findBook = false;
		for (auto &pair : stock)
		{
			if (pair.first.title == title) {
				if (pair.second == 0) {
					cout<< "책은 찾았으나 재고가 없습니다."<<endl;
				}
				else {
					pair.second--;
					cout<< "대여 성공" << endl;
				}
				findBook = true;
			}
		}

		if (findBook == false) {
			cout<< "대여할 책이 없음" << endl;
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

	void displayStock(){
		cout << "<<<대여여부 확인>>>"<< endl;
		for (auto it = stock.begin(); it != stock.end(); it++) {
			cout<< "작가 : " << it->first.author<< " / 책이름 : "<< it->first.title << " / 재고 : " << it->second << endl;
		}
	} // 대여여부 확인
};

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

	Book* getBookByTitle(string title){
		for (auto& book : books)
		{
			if (book.title == title) {
				return &book;
			}
		}
		return nullptr;
	};

	Book* getBookByAuthor(string author){
		for (auto& book : books)
		{
			if (book.author == author) {
				return &book;
			}
		}
		return nullptr;
	};
};

int main() {
	BookManager manager;
	BorrowManager borrowManager;
	// 도서관 관리 프로그램의 기본 메뉴를 반복적으로 출력하여 사용자 입력을 처리합니다.
	// 프로그램 종료를 선택하기 전까지 계속 동작합니다.
	while (true) {
		cout << "\n도서관 관리 프로그램" << endl;
		cout << "1. 책 추가" << endl; // 책 정보를 입력받아 책 목록에 추가
		cout << "2. 모든 책 출력" << endl; // 현재 책 목록에 있는 모든 책 출력
		cout << "3. 책 제목으로 검색" << endl; // 현재 책 목록에 있는 모든 책 출력
		cout << "4. 작가로 검색" << endl; // 현재 책 목록에 있는 모든 책 출력
		cout << "5. 책 대여 여부 확인" << endl; // 현재 책 목록에 있는 모든 책 출력
		cout << "6. 책 제목으로 대여" << endl; // 현재 책 목록에 있는 모든 책 출력
		cout << "7. 책 제목으로 반납" << endl; // 현재 책 목록에 있는 모든 책 출력
		cout << "9. 종료" << endl; // 프로그램 종료
		cout << "선택: ";

		int choice; // 사용자의 메뉴 선택을 저장
		cin >> choice;

		if (choice == 1) {
			// 1번 선택: 책 추가
			// 사용자로부터 책 제목과 저자명을 입력받아 BookManager에 추가합니다.
			string title, author;
			cout << "책 제목: ";
			cin.ignore(); // 이전 입력의 잔여 버퍼를 제거
			getline(cin, title); // 제목 입력 (공백 포함)
			cout << "책 저자: ";
			getline(cin, author); // 저자명 입력 (공백 포함)
			manager.addBook(title, author); // 입력받은 책 정보를 추가
			Book* FindBook = manager.getBookByTitle(title);
			borrowManager.initializeStock(*FindBook);
		}
		else if (choice == 2) {
			// 2번 선택: 모든 책 출력
			// 현재 BookManager에 저장된 책 목록을 출력합니다.
			manager.displayAllBooks();
		}
		else if (choice == 3) {
			string title;
			cout << "책 제목: ";
			cin.ignore(); // 이전 입력의 잔여 버퍼를 제거
			getline(cin, title); // 제목 입력 (공백 포함)
			auto val = manager.getBookByTitle(title);
			if (val) {
				cout << "제목으로 책을 찾았음. author : " <<val->author << " / title : " << val->title << endl;
			}
			else {
				cout<<"책이 존재하지 않음" << endl;
			}
		}
		else if (choice == 4) {
			string author;
			cout << "책 저자: ";
			cin.ignore(); // 이전 입력의 잔여 버퍼를 제거
			getline(cin, author); // 제목 입력 (공백 포함)
			auto val = manager.getBookByAuthor(author);
			if (val) {
				cout << "작가이름으로 책을 찾았음. author : " << val->author << " / title : " << val->title << endl;
			}
			else {
				cout<<"책이 존재하지 않음" << endl;
			}
		}
		else if (choice == 5) {
			borrowManager.displayStock();
		}
		else if (choice == 6) {
			string title; // 책 제목으로 대여

			cout << "대여할 책 제목: ";
			cin.ignore(); // 이전 입력의 잔여 버퍼를 제거
			getline(cin, title); // 제목 입력 (공백 포함)
			borrowManager.borrowBook(title);
		}
		else if (choice == 7) {
			string title; // 책 제목으로 반납

			cout << "반납할 책 제목: ";
			cin.ignore(); // 이전 입력의 잔여 버퍼를 제거
			getline(cin, title); // 제목 입력 (공백 포함)
			borrowManager.returnBook(title);
		}
		else if (choice == 9) {
			// 3번 선택: 종료
			// 프로그램을 종료하고 사용자에게 메시지를 출력합니다.
			cout << "프로그램을 종료합니다." << endl;
			break; // while 루프 종료
		}
		else {
			// 잘못된 입력 처리
			// 메뉴에 없는 번호를 입력했을 경우 경고 메시지를 출력합니다.
			cout << "잘못된 입력입니다. 다시 시도하세요." << endl;
		}
	}

	return 0; // 프로그램 정상 종료
}
