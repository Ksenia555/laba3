#pragma once
#include <vector>
#include <cmath>
#include <iostream>

class TString
{
protected:
	char* str;
	int len;
public:
	TString();// по умолчанию
	TString(const TString& p); //копирования
	TString(TString&& p) noexcept; // перемещения
	TString(char* str_, int len_);
	TString(const char* str_);
	~TString();

	const char* GetStr() const;
	int GetLen();

	void SetStr(const char* str_);
	void SetLen(int len_);

	int Find(const TString& substring) const;

	TString Substring(size_t start, size_t count = -1) const;

	TString operator+(const TString& other) const;
	TString operator*(int count) const;
	TString& operator=(const TString& other);

	bool operator==(const TString& other) const;

	char& operator[](size_t index);
	const char& operator[](size_t index) const;


	friend std::ostream& operator<<(std::ostream& os, const TString& str);
	friend std::istream& operator>>(std::istream& is, TString& str);
};