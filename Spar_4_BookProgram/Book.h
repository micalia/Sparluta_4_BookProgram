#pragma once
#include <iostream>
#include <unordered_map>
#include <vector>
#include <string>


using namespace std; // namespace std »ç¿ë

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

		return val;
	}
};