
#include <gtest.h>
#include "TString.h"

TEST(TStringGettersTest, EmptyString) {
  TString s;
  const char* expected = "";
  EXPECT_STREQ(expected, s.GetStr());  // Проверяем nullptr
  EXPECT_EQ(s.GetLen(), 1);       // Проверка длины
}

TEST(TStringGettersTest, NullTermination) {
  TString s("Hello");
  EXPECT_EQ(s.GetStr()[5], '\0');  // Проверка нуль-терминатора
}

TEST(TStringGettersTest, ConstVersion) {
  const TString s("Test");
  EXPECT_STREQ(s.GetStr(), "Test");  // Вызов константной версии
}

TEST(TStringGettersTest, NonEmptyString) {
  TString s("Hello");
  EXPECT_STREQ(s.GetStr(), "Hello");
  EXPECT_EQ(s.GetLen(), 5);
}

// Тестирование сеттеров
TEST(TStringSettersTest, SetStrBasic) {
  TString s;
  s.SetStr("Test");
  EXPECT_STREQ(s.GetStr(), "Test");
  EXPECT_EQ(s.GetLen(), 4);
}


TEST(TStringExceptionTest, SetStrNullThrows) {
  TString s;
  EXPECT_THROW(s.SetStr(nullptr), std::invalid_argument);
}

TEST(TStringOperatorTest, Concatenation) {
  TString s1("Hello");
  TString s2(" World");
  TString s3 = s1 + s2;

  EXPECT_STREQ(s3.GetStr(), "Hello World");
  EXPECT_EQ(s3.GetLen(), 11);
}

TEST(TStringOperatorsTest, Equality) {
  TString s1("Test");
  TString s2("Test");
  TString s3("Different");

  EXPECT_TRUE(s1 == s2);
  EXPECT_FALSE(s1 == s3);
}

TEST(TStringOperatorsTest, IndexAccess) {
  TString s("Hello");

  // Проверка чтения
  EXPECT_EQ(s[0], 'H');
  EXPECT_EQ(s[4], 'o');

  // Проверка записи
  s[0] = 'h';
  EXPECT_STREQ(s.GetStr(), "hello");

  // Проверка выхода за границы
  EXPECT_THROW(s[5], std::out_of_range);
}

TEST(TStringMethodsTest, FindSubstring) {
  TString s("Hello World");

  EXPECT_EQ(s.Find(TString("Hello")), 0);
  EXPECT_EQ(s.Find(TString("World")), 6);
  EXPECT_EQ(s.Find(TString("o W")), 4);
  EXPECT_EQ(s.Find(TString("XYZ")), -1);
  EXPECT_EQ(s.Find(TString("")), 0);
}

TEST(TStringMethodsTest, Substring) {
  TString s("Hello World");

  EXPECT_STREQ(s.Substring(0, 5).GetStr(), "Hello");
  EXPECT_STREQ(s.Substring(6).GetStr(), "World");
  EXPECT_STREQ(s.Substring(2, 3).GetStr(), "llo");
  EXPECT_THROW(s.Substring(20), std::out_of_range);
}

TEST(TStringOperatorsTest, Multiplication) {
  // Базовый тест
  TString s("ab");
  TString doubled = s * 3;
  EXPECT_STREQ(doubled.GetStr(), "ababab");
  EXPECT_EQ(doubled.GetLen(), 6);
}

