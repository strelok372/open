#ifndef _COMPLEX_H_ // проверяем, определен ли файл в программе. Эта проверка нужна, чтобы один и тот же кусок кода не компилировался по несколько раз
#define _COMPLEX_H_ // определяем файл в программе. 
#include <iostream>
using namespace std; // исполльзуем пространство имен std, для работы с потоками cin cout
class complex // создаем класс комплексных чисел
{
private:
	double Re, Im; // у косплексного числа есть целая и вещественная часть, описываем их 
public:
	complex(double = 0.0, double = 0.0); // конструктор по умолчанию, делает обе части комплексного числа равными нулю
	complex(const complex&);
	void set(double, double);
	void get(); // вывод комплекса на экран
	complex operator+(const complex&); // сложение двух комплексных чисел 
	complex operator-(const complex&); // вычитание
	complex operator*(const complex&); // умножение
	complex operator/(const complex&); // деление
	complex& operator=(const complex&); // присвоение одного комплексного числа другому
	complex& operator=(const int&); // присвоение комплексному числу значения, которое мы сами укажем
	//bool operator==(const complex&)const; // сравнение комплексных чисел
	//bool operator!=(const complex&)const; // проверка чисел на неравенство
	//complex& operator+=(const complex&); // операция +=    a+=b то же самое что a=a+b
	friend ostream& operator<<(ostream& os,complex&); 
	//friend istream& operator<<(istream& os,complex&); // Вывод и ввод числа через поток
	//operator float(); // оператор приведения типа. Вообще то, комплексное число нельзя привести к вещественному типу, поэтому эта функция просто возвращает сумму квадратов целой и мнимой части числа
	//complex& operator () (); // оператор () Делает то, что мы захотим.
	//complex& operator++(); // Оператор ++               a++ то же самое что a=a+1
};
#endif