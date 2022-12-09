#include <iostream>
#include<cmath>
#include <numbers> 
using namespace std;

class Complex 
{
private:

  double real, imag;

public:

  Complex (double a=0, double b=0)
  {
      real = a; 
      imag = b;
  }
  
  Complex operator + (Complex const &right)
  {
    return Complex(real + right.real, imag + right.imag);
  }
  friend ostream& operator<<(ostream& os,Complex &obj)
  {
    os<< obj.real << " + i" << obj.imag << '\n';
    return os;
  }

};

class Circle 
{
private:

  double center_x; 
  double center_y;
  double radius;


public:

  Circle(double x, double y, double r)
  {
      center_x = x; 
      center_y = y;
      radius = r;
  }
  bool contains( double point_x, double point_y);
};

  bool Circle::contains(double point_x, double point_y)
  {
    int dist = (center_x-point_x)*(center_x-point_x) + (center_y-point_y)*(center_y-point_y);
      if (dist <= radius*radius)
      {
          return true;
      }
      else return false;
  } 

int main() 
{
	Complex c1;
	Complex c2(1.0, 2.5);
	Complex c3 = 2.5;
	Complex c4 = c2 + c3;
	cout << c4 << '\n';
	
	double x = 50, y = 62.5, r = 10;
	Circle c(x, y, r);
	cout << c.contains(x+8,y) << '\n';
	cout << c.contains(x+10,y) << '\n';
	cout << c.contains(x+10,y+3) << '\n';
	cout << c.contains(x,y+10) << '\n';
	double dx = r * cos(45 * std::numbers::pi / 180);
	cout << c.contains(x+dx, y+dx)<<'\n';
	
}