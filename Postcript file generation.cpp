#include <vector>
#include <iostream>
#include <fstream>
using namespace std;

class Shape  
{
    protected:
        double x, y; 

    public:
	    Shape(double x, double y) : x(x), y(y) {}
        
        virtual void print(ofstream &f) const = 0; 
};


class Circle : public Shape 
{
    private:
        double radius, r, g, b;

    public:
        Circle(double x, double y, double radius, int r, int g, int b) : Shape(x,y), radius(radius), r(r), g(g), b(b) {}
        void print(ofstream &f) const 
        {   
            //f.open ("out.ps", ios::out | ios::app);
            f<< x << ' ' << y << ' ' << radius << ' ' << "0" << ' ' << "360" << ' ' << "arc \n";
            f<<r<<' '<<g<<' '<<b<<" setrgbcolor \n";
   		    f<<"fill \n\n";
        }
};


class Rect : public Shape 
{
    private:
        double w, h, r,g,b; 
    
    public:
    
        Rect(double x, double y, double w, double h, int r, int g, int b) : Shape(x,y), w(w), h(h), r(r), g(g), b(b) { }
    
        void print(ofstream &f) const 
        {   
            
            //f.open ("out.ps", ios::out | ios::app);
            f<<x<<' '<< y <<" moveto \n";
		    f<<x+w<<' '<<y<<" lineto \n";
		    f<<x+w<<' '<<y+h<<" lineto \n";
		    f<<x<<' '<<y+h<<" lineto \n";
		    f<<"closepath \n";
		    f<<r<<' '<<g<<' '<<b<<" setrgbcolor \n";
		    f<<"fill \n\n";
        }
};

class Triangle : public Shape 
{
    private:
        double x2, y2, x3, y3,r,g,b; 
        
    public:
    
        Triangle(double x, double y, double x2, double y2, double x3, double y3, int r, int g, int b) : Shape(x,y), x2(x2), y2(y2), x3(x3), y3(y3), r(r), g(g), b(b) { }
    
        void print(ofstream &f) const 
        {   
           
            //f.open ("out.ps", ios::out | ios::app);
            f<<x<<' '<<y<<" moveto \n";
		    f<<x2<<' '<<y2<<" lineto \n";
		    f<<x3<<' '<<y3<<" lineto \n";
		    f<<"closepath \n";
		    f<<r<<' '<<g<<' '<<b<<" setrgbcolor \n";
		    f<<"fill \n";
        }
};


int main() 
{
  vector<Shape*> shapes; //shape = classname; shapes = object
                                              //r,g,b
  shapes.push_back(new Circle(100, 200, 50, 1, 0,0)); // bright red circle
  shapes.push_back(new Rect(200, 300, 50, 40,  0,1,0)); // bright green rect
  shapes.push_back(new Triangle(100, 500, 300,600, 400,500, 0,0,1)); //bright blue triangle
  

  //circle has to print r g b setrgbcolor x y r 0 360 arc fill
  //   1 0 0 setrgbcolor 100 200 50 0 360 arc fill

  // rect
  // r g b setrgbcolor x y moveto x+w y lineto x+w y+h lineto x y+h lineto closepath fill

  // triangle
  // r g b setrgbcolor x y moveto x2 y2 lineto x3 y3 lineto closepath fill

  ofstream f("out.ps", std::ios_base::app);
  
  
  for (auto s : shapes) 
  {
    s->print(f);
  }
  for (auto s : shapes) 
  {
    delete s; // free the memory used by each shape after we are done
  }
  f  << "showpage";
  f.close();
}