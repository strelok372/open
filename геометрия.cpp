// lab3.cpp: определяет точку входа для консольного приложения.


#include "stdafx.h"
#include <iostream>
#include <string>
#include <stdexcept>
using namespace std;

class Shape{
	public:
		virtual string name()const = 0; // Возвращает название данной геометрической фигуры
		virtual double area() const = 0; // Вычисляет площадь
		virtual double perimeter() const = 0; // Вычисляет периметер
		virtual ~Shape();
};

class Rectangle : public Shape {
	private:
		double height, weight;
	public:
		Rectangle(double _h, double _w) {
			if (_h <= 0 || _w <= 0)throw invalid_argument( "Ошибка: некорректные данные(Значение высоты и длины должно быть больше нуля)");
			height = _h;
			weight = _w;
		}
		
		string name()const{
			return "Rectangle";
		}
		double area()const {
			return height*weight;
		}
		virtual double perimeter()const {
			return 2 * weight + 2 * height;
		}
};

class Circle : public Shape {
	private:
		double radius;
	public:
		Circle(double _r) {
			if (_r <= 0)throw invalid_argument("Radius of a circle must be greater than zero.");
			radius = _r;
		}
		
		string name()const{
			return "Circle";
		}
		double area()const {
			return radius * radius * 3.14;
		}
		virtual double perimeter()const {
			return 2 * 3.14 * radius;
		}
};

class Triangle : public Shape {
	private:
		double catenary1, catenary2, hypotenuse;
public:
	Triangle(double _c1, double _c2, double _h) {
		if (_c1 <= 0 || _c2 <= 0 || _h <= 0)throw "Ошибка: некорректные данные(Значение сторон триугольника должно быть больше нуля)";
		catenary1 = _c1;
		catenary2 = _c2;
		hypotenuse = _h;
	}
	
	string name()const{
		return "Triangle";
	}
	double area()const {
		return 0.5 * catenary1 * catenary2;
	}
	virtual double perimeter()const {
		return catenary1 + catenary2 + hypotenuse;
	}
};
//-------test------
void print_perimeter(const Shape *shape) {
	std::cout << shape->name() << ": { ";
	std::cout << shape->area() << ", ";
	std::cout << shape->perimeter() << " }";
	std::cout << std::endl;
}

int main(int argc, char const *argv[]) {
	
	try {
		const int NUM_OF_SHAPES = 3;
		Shape *shapes[NUM_OF_SHAPES];
		shapes[0] = new Rectangle(1.0, 6.0);
		shapes[1] = new Circle(5.0);
		shapes[2] = new Triangle(2.0, 3.0, 4.0);

		for (int i = 0; i < NUM_OF_SHAPES; i++) {
			print_perimeter(shapes[i]);
			delete shapes[i];
		}
	}
	catch (exception e) {
		cout << e.what();
	}

	return 0;
}
