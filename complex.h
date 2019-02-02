#ifndef _COMPLEX_H_ // ���������, ��������� �� ���� � ���������. ��� �������� �����, ����� ���� � ��� �� ����� ���� �� �������������� �� ��������� ���
#define _COMPLEX_H_ // ���������� ���� � ���������. 
#include <iostream>
using namespace std; // ����������� ������������ ���� std, ��� ������ � �������� cin cout
class complex // ������� ����� ����������� �����
{
private:
	double Re, Im; // � ������������ ����� ���� ����� � ������������ �����, ��������� �� 
public:
	complex(double = 0.0, double = 0.0); // ����������� �� ���������, ������ ��� ����� ������������ ����� ������� ����
	complex(const complex&);
	void set(double, double);
	void get(); // ����� ��������� �� �����
	complex operator+(const complex&); // �������� ���� ����������� ����� 
	complex operator-(const complex&); // ���������
	complex operator*(const complex&); // ���������
	complex operator/(const complex&); // �������
	complex& operator=(const complex&); // ���������� ������ ������������ ����� �������
	complex& operator=(const int&); // ���������� ������������ ����� ��������, ������� �� ���� ������
	//bool operator==(const complex&)const; // ��������� ����������� �����
	//bool operator!=(const complex&)const; // �������� ����� �� �����������
	//complex& operator+=(const complex&); // �������� +=    a+=b �� �� ����� ��� a=a+b
	friend ostream& operator<<(ostream& os,complex&); 
	//friend istream& operator<<(istream& os,complex&); // ����� � ���� ����� ����� �����
	//operator float(); // �������� ���������� ����. ������ ��, ����������� ����� ������ �������� � ������������� ����, ������� ��� ������� ������ ���������� ����� ��������� ����� � ������ ����� �����
	//complex& operator () (); // �������� () ������ ��, ��� �� �������.
	//complex& operator++(); // �������� ++               a++ �� �� ����� ��� a=a+1
};
#endif