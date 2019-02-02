#include "stdafx.h" 
#include <iostream> 
using namespace std;

class String {
private:
	char* str;
	int len;
public:
	//������� ����� ������; 
	int length(const char *s) {
		int count = 1;
		for (int i = 0; s[i]; ++i)count += 1;
		return count;
	}
	//�������� s � str; 
	void copy(char *str, const char *s) {
		for (int i = 0; i < len; ++i)str[i] = s[i];
	}
	//����� ������������ ����� ������ ������� ������ � �������� ���� ������ s
	void oStr(const char *s) {
		len = length(s);
		str = new char[len];
		copy(str, s);
	}
	//����������� ��� ������ 
	String(const char *s) {
		oStr(s);
	}
	//����������� ��� ������� 
	String(const String &other) {
		oStr(other.str);
	}

	String() {

	}
	//����������+
	String operator+(const String &other) {
		int newlen = len + other.len;
		char *newstr = new char[newlen];
		
		copy(newstr, str);
		strcat(newstr, other.str);

		String s;
		s.str = newstr;
		s.len = newlen - 1;
		return s;

		//str=other.str  ��� ����� �� ������ �.�. ������� ���������
	}
	//����������=
	String &operator=(const String &other) {
		
		if (this == &other) {
			return *this;
		}
		oStr(other.str);
		return *this;
	}
	//���������� +=
	String &operator+=(const String &other) {
		return operator=(operator+(other));
	}
	//������������ ������
	char* get() const {
		return str;
	}
	~String() {
		delete str;
	}
};
//���������� ������ � �����;
ostream &operator<<(ostream &out, const String &other) {
	out << other.get()<< "\n";
	return cout;
}

int main()
{
	try {
		String s1("Hello");
		String s2(" World!");

		String s3 = s1 + s2 + String(" hi");;
		s1 += String(" my friend");

		String s4 = "Hello";
		s4 = s4;

		cout << s3;
		cout << s1;
		cout << s4;
	}
	catch (exception e) {
		cout << e.what();
	}
	return 0;
}