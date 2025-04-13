#include <iostream>
#include <cmath>
#include <vector>
#include "TString.h"

TString::TString()
{
	len = 1;
	str = new char[1] {'\0'};
}

TString::TString(const TString& p) : len(p.len), str(new char[p.len + 1]) {
	std::copy(p.str, p.str + len + 1, str);
}


TString::TString(TString&& p) noexcept: len(p.len), str(p.str) {
	p.str = nullptr;  // Источник теряет владение
	p.len = 0;
}

TString::TString(char* str_, int len_) : len(len_) {
	if (len_ <= 0) throw std::invalid_argument("Invalid length");
	str = new char[len + 1];
	std::copy(str_, str_ + len, str);
	str[len] = '\0';
}


TString::TString(const char* str_) {
	if (!str_) throw std::invalid_argument("Null pointer");
	len = strlen(str_);
	str = new char[len + 1];
	std::copy(str_, str_ + len + 1, str);
}

TString::~TString()
{
	if (str != nullptr)
		delete[] str;
	str = nullptr;
}

const char* TString::GetStr() const{
    return str ? str : "";  // Возвращаем пустую строку если str == nullptr
}

int TString::GetLen() 
{
	return len;
}

void TString::SetStr(const char* str_)
{
	if (str_ == nullptr) throw std::invalid_argument("Null pointer");

	len = strlen(str_);
	delete[] str;  // Освобождаем старую память
	str = new char[len + 1];  // +1 для \0
	std::copy(str_, str_ + len + 1, str);
}

void TString::SetLen(int len_)
{
	if (len_ <= 0)
		throw "len_ <= 0";
	if (len == len_)
		return;

	char* str_ = new char[len + 1];
	for (int i = 0; i < std::min(len, len_); i++)
		str_[i] = str[i];
	for (int i = std::min(len, len_); i < len_; i++)
		str_[i] = 0;

	str = str_;
	len = len_;
}

int TString::Find(const TString& substring) const {
	if (substring.len == 0) return 0;
	if (len < substring.len) return -1;

	for (size_t i = 0; i <= len - substring.len; ++i) {
		if (std::equal(substring.str, substring.str + substring.len, str + i)) {
			return static_cast<int>(i);
		}
	}
	return -1;
}

TString TString::Substring(size_t start, size_t count) const {
	if (start >= len) throw std::out_of_range("Invalid start position");

	size_t actual_count = std::min(count, len - start);
	TString result;
	result.len = actual_count;
	result.str = new char[actual_count + 1];

	std::copy(str + start, str + start + actual_count, result.str);
	result.str[actual_count] = '\0';

	return result;
}

TString TString::operator+(const TString& other) const {
	TString result;
	result.len = this->len + other.len;
	result.str = new char[result.len + 1];  // Выделяем память напрямую

	if (this->str) std::copy(this->str, this->str + this->len, result.str);
	if (other.str) std::copy(other.str, other.str + other.len + 1, result.str + this->len);

	return result;
}

TString TString::operator*(int count) const {
	if (count <= 0) {
		return TString();  // Возвращаем пустую строку
	}

	TString result;
	result.len = len * count;
	result.str = new char[result.len + 1];  // +1 для '\0'

	for (int i = 0; i < count; ++i) {
		std::copy(str, str + len, result.str + i * len);
	}

	result.str[result.len] = '\0';  // Добавляем терминатор
	return result;
}


TString& TString::operator=(const TString& other) {
	if (this != &other) {  // Проверка на самоприсваивание
		delete[] str;      // 1. Освобождаем старые ресурсы

		len = other.len;   // 2. Копируем длину
		str = new char[len + 1];  // 3. Выделяем новую память
		std::copy(other.str, other.str + len + 1, str);  // 4. Копируем данные
	}
	return *this;  // 5. Возвращаем текущий объект
}

bool TString::operator==(const TString& other) const {
	if (len != other.len) return false;
	return std::equal(str, str + len, other.str);
}

char& TString::operator[](size_t index) {
	if (index >= len) throw std::out_of_range("Index out of range");
	return str[index];
}

const char& TString::operator[](size_t index) const {
	if (index >= len) throw std::out_of_range("Index out of range");
	return str[index];
}

std::ostream& operator<<(std::ostream& os, const TString& str) {
	if (str.str) {  // Проверка на nullptr
		os.write(str.str, str.len);  // Эффективный вывод без лишних копий
	}
	return os;  // Возвращаем поток для цепочки операций
}

std::istream& operator>>(std::istream& is, TString& str) {
	const size_t BUFFER_SIZE = 256;
	char buffer[BUFFER_SIZE];

	// Читаем до пробела или новой строки
	if (is >> buffer) {
		size_t len = strlen(buffer);
		char* new_str = new char[len + 1];  // +1 для '\0'
		std::copy(buffer, buffer + len + 1, new_str);

		// Освобождаем старую память
		delete[] str.str;

		// Присваиваем новые значения
		str.str = new_str;
		str.len = len;
	}

	return is;  // Возвращаем поток
}

