#include "complex.h"
#include <iostream>
#include <cmath>
complex::complex(double re, double im) // ����������� �� �����. �������� �� ���� ��� ��������, ���� ���������� ����� ������, ������ ������
{
	Re = re;
	Im = im;
}
complex::complex(const complex &c) // ����������� �� ������� ���������. �������� �� ���� ����������� ����� � ������� ��� ������ �����
{
	Re = c.Re;
	Im = c.Im;
}
complex complex::operator+(const complex &c) // �������� �������� ����������� �����. ���������� ����� �����, � �������� ����� � ������ ����� ����� ����� ����� � ������ ������ ���� ��������� �����
{
	return complex(Re + c.Re, Im + c.Im);
}
complex complex::operator-(const complex &c) // �������� ���������. �� �� �����, ��� ��������, ������ ���������
{
	return complex(Re - c.Re, Im - c.Im);
}
complex complex::operator*(const complex &c) // �������� ���������. ����������� ����� ����� ����������, ������� �� ��������� �������� �� -1, ����� ���������� ����, � ��� �� �������� ����� � ������ �����. ������ ��� ������ ������� �� ���������
{
	return complex(-1*((Re*c.Re)-(Im*c.Im)),-1*((Re*c.Im)+(Im*c.Re)));
}
complex complex::operator/(const complex &c)
{
	return complex((Re*c.Re + Im*c.Im) / (Re*Re + Im*Im), (Im*c.Re - Re*c.Im) / (Re*Re + Im*Im))
}
complex& complex::operator=(const complex &c) // �������� ������������ ������������ �����
{
	if(&c == this)
	{
		return *this; // ���� ��� ����� ��� �����, �� ������ ������ ������ �� ����, ������ ������ ���� �����
	}
	else
	{
		Re = c.Re;
		Im = c.Im;
		return *this; // ������������ ����� � ������ �����, ���������� this. This ��� ��, ��� ��������� ������ �������, � ������ ������ - ����������� �����
	}
}
complex& complex::operator=(const int &c) // �������� ������������� ������������ ����� ������. 
{
	Re = c; // ����� ����� �������������� ������ �����
	Im=0;  // ������ ����� ���������� 
	return *this; // ���������� this, ��� � � ������ ����
}
bool complex::operator==(const complex &c)const // �������� ��������� ���� ����������
{
	return Re == c.Re && Im == c.Im; // ���������� true ��� false, � ����������� �� ����, ����� ��� ����� ��� ���
}
bool complex::operator!=(const complex &c)const // �������� �������� �� �����������
{
	return !operator==(c); // ���������� true ���� ����� �� �����, false �����
}
complex& complex::operator+=(const complex &c) // �������� +=, ����� �� ��������, ������ � �������������
{
	Re += c.Re;
	Im += c.Im;
	return *this;
}
void complex::set(double Re1, double Im1) // ������. ����� ����� ������ ����� �������, � ���� a.set(1.2)
{
	Re = Re1;
	Im = Im1; // ������ ����� �������� � �������� ����� ��� ������� �����
};
void complex::get() // ������. �����, ����� ������� ������� ����� �� �����
{
	Im>0 ? // �������� ����� ����� �� ���������������. ����� ��� ������, ������ ��� ���� ��� ������ ����, �� ���� ���� ����� ������ �������� �� ����.
		std::cout << "Complex = " << Re << "+" << Im <<"i"<< std::endl: // ����������� ���� IM > 0
		std::cout << "Complex = " << Re << "-" <<fabs(Im)<<"i"<< std::endl; // ����������� ���� IM < 0
};
complex::operator float() // ���������� � float(������������� ����)
{
	return Re*Re+Im*Im; // ���������� ����� ���������
}
complex& complex::operator() () // �������� (). ������ �� ��� �� �������, � ������ ������ - ����������� Re ����� � ��������� Im �����
{
	Re++;
	Im--;
	return *this;
}
complex& complex::operator++() // �������� ����������� �������. ���������� 1 � ������ ����� �����
{
	Re++;
	Im++;
	return *this;
}



