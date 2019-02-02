#include "complex.h"
#include <iostream>
#include <cmath>
complex::complex(double re, double im) // конструктор от числа. Получаем на вход два значения, одно становится целой частью, другое мнимой
{
	Re = re;
	Im = im;
}
complex::complex(const complex &c) // конструктор от другого комплекса. Получаем на вход комплексное число и создаем его точную копию
{
	Re = c.Re;
	Im = c.Im;
}
complex complex::operator+(const complex &c) // оператор сложения комплексных чисел. Возвращает новое число, у которого целая и мнимая часть равны сумме целых и мнимых частей двух слагаемых чисел
{
	return complex(Re + c.Re, Im + c.Im);
}
complex complex::operator-(const complex &c) // оператор вычитания. То же самое, что сложение, только вычитание
{
	return complex(Re - c.Re, Im - c.Im);
}
complex complex::operator*(const complex &c) // оператор умножения. Комплексные числа хитро умножаются, поэтому мы вынуждены умножать на -1, чтобы чередовать знак, а так же вычитать целые и мнимые части. Вообще это просто формула из интернета
{
	return complex(-1*((Re*c.Re)-(Im*c.Im)),-1*((Re*c.Im)+(Im*c.Re)));
}
complex complex::operator/(const complex &c)
{
	return complex((Re*c.Re + Im*c.Im) / (Re*Re + Im*Im), (Im*c.Re - Re*c.Im) / (Re*Re + Im*Im))
}
complex& complex::operator=(const complex &c) // оператор присваивания комплексного числа
{
	if(&c == this)
	{
		return *this; // если два числа уже равны, то дальше ничего делать не надо, просто вернем само число
	}
	else
	{
		Re = c.Re;
		Im = c.Im;
		return *this; // приравниваем целые и мнимые части, возвращаем this. This это то, что находится внутри функции, в данном случае - комплексное число
	}
}
complex& complex::operator=(const int &c) // оператор приравнивания комплексного числа целому. 
{
	Re = c; // Целая часть приравнивается нашему числу
	Im=0;  // Мнимая часть обнуляется 
	return *this; // возвращаем this, как и в методе выше
}
bool complex::operator==(const complex &c)const // оператор сравнения двух комплексов
{
	return Re == c.Re && Im == c.Im; // возвращает true или false, в зависимости от того, равны два числа или нет
}
bool complex::operator!=(const complex &c)const // оператор проверки на неравенство
{
	return !operator==(c); // возвращает true если числа НЕ равны, false иначе
}
complex& complex::operator+=(const complex &c) // оператор +=, похож на сложение, только с присваиванием
{
	Re += c.Re;
	Im += c.Im;
	return *this;
}
void complex::set(double Re1, double Im1) // сеттер. Нужен чтобы задать число красиво, в виде a.set(1.2)
{
	Re = Re1;
	Im = Im1; // каждое число кладется в значение целой или дробной части
};
void complex::get() // геттер. Нужен, чтобы красиво вывести число на экран
{
	Im>0 ? // Проверка целой части на положительность. Нужна для вывода, потому что если она больше нуля, то знак плюс перед числом выводить не надо.
		std::cout << "Complex = " << Re << "+" << Im <<"i"<< std::endl: // выполняется если IM > 0
		std::cout << "Complex = " << Re << "-" <<fabs(Im)<<"i"<< std::endl; // выполняется если IM < 0
};
complex::operator float() // приведение к float(вещественному типу)
{
	return Re*Re+Im*Im; // возвращает сумму квадратов
}
complex& complex::operator() () // оператор (). Делает то что мы захотим, в данном случае - увеличивает Re часть и уменьшает Im часть
{
	Re++;
	Im--;
	return *this;
}
complex& complex::operator++() // оператор прибавления единицы. Прибавляет 1 к каждой части числа
{
	Re++;
	Im++;
	return *this;
}



