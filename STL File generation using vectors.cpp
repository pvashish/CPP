#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
using namespace std;


class triangles{
    
    public:
        double x, y, z, x1,  y1,  z1,  x2,  y2, z2, nx, ny, nz;
    
    public:
        //vector<double> List_of_triangles;
        triangles(double x, double y, double z, double x1, double y1, double z1, double x2, double y2, double z2): x(x), y(y), z(z), x1(x1), y1(y1), z1(z1), x2(x2), y2(y2), z2(z2){
            
        //double triangles[9] = {double x, double y, double z, double x1, double y1, double z1, double x2, double y2, double z2};
        
        double Ax = x1 - x;
        double Ay = y1 - y;
        double Az = z1 - z;
        double Bx = x2 - x;
        double By = y2 - y;
        double Bz = z2 - z;
         nx = Ay * Bz - Az * By;
         ny = Az * Bx - Ax * Bz;
         nz = Ax * Bz - Ay * Bx;
        }
};


class shape {
protected:
    double x, y, z;                 //  position
public:
    shape() : x(0), y(0), z(0) {}
    virtual void print(ostream& os) const = 0;
};

class cylinder : public shape{
    
    private:
    
        double r, h;
        //double triangles[9] = {};
        vector<triangles> List_of_triangles;
    
    
    public:
        
        //cylinder(double r, double h) : r(r), h(h){}
        
        cylinder(double r, double h, double num_facets = 100) : r(r), h(h){
            
            double tri_1_x = x+r;
            double tri_1_y = y;
            double tri_1_z = z;
        
            double tri_2_x, tri_2_y, tri_2_z;
        
            const double dtheta = (2*M_PI)/num_facets;
        
            for(int i = 1; i <= num_facets; i++){
                
                double angle = dtheta*i;
                tri_2_x = r * cos(angle);
                tri_2_y = r * sin(angle);
                tri_2_z = z;
                
                //for bottom triangles
                List_of_triangles.push_back(triangles(x,y,z,  tri_1_x, tri_1_y, tri_1_z,  tri_2_x, tri_2_y, tri_2_z));
            
                //for adding rectangles
                List_of_triangles.push_back(triangles(tri_1_x, tri_1_y, tri_1_z,  tri_2_x, tri_2_y, tri_2_z,  tri_1_x, tri_1_y, tri_1_z+h));
                List_of_triangles.push_back(triangles(tri_1_x, tri_1_y, tri_1_z+h,  tri_2_x, tri_2_y, tri_2_z+h,  tri_2_x, tri_2_y, tri_2_z));
                
                //for adding top triangles
                List_of_triangles.push_back(triangles(x, y, z+h,  tri_1_x, tri_1_y, tri_1_z+h,  tri_2_x, tri_2_y, tri_2_z+h));
                
                tri_1_x = tri_2_x;
                tri_1_y = tri_2_y;
                tri_1_z = tri_2_z;
            }
            
            //cylinder operator + ( const cylinder a, const cylinder b ){ return { a.x + b.x, a.y + b.y, a.z + b.z }; }
        }

    void print(ostream& os) const override{
        os << "solid Cylinder \n";
        for(triangles tri : List_of_triangles){
            os << "facet normal " << tri.nx << " " << tri.ny << " " << tri.nz << "\n";
            os << "outer loop\n";
            os << "vertex " << tri.x << " " << tri.y << " " << tri.z << "\n";
            os << "vertex " << tri.x1 << " " << tri.y1 << " " << tri.z1 << "\n";
            os << "vertex " << tri.x2 << " " << tri.y2 << " " << tri.z2 << "\n";
            os << "endloop\n";
            os << "endfacet\n";
        }
        os<<"endsolid Cylinder\n";
    }
    
    friend ostream& operator << (ostream& os, const cylinder cyl){
        return os << "radius= " << cyl.r << "\t\theight= " << cyl.h << endl;
    }
};


class cube : public shape {
    private:
        double length, breadth, height;
        
        void facet(ostream &os, double x1, double y1, double z1, double x2, double y2, double z2, double x3, double y3, double z3)const{
        double Ax = x2 - x1;
        double Ay = y2 - y1;
        double Az = z2 - z1;
        double Bx = x3 - x1;
        double By = y3 - y1;
        double Bz = z3 - z1;
        double nx = Ay * Bz - Az * By;
        double ny = Az * Bx - Ax * Bz;
        double nz = Ax * Bz - Ay * Bx;
        os << "facet normal " << nx << " " << ny << " " << nz << "\n";
        os << "outer loop\n";
        os << "vertex " << x1 << " " << y1 << " " << z1 << "\n";
        os << "vertex " << x2 << " " << y2 << " " << z2 << "\n";
        os << "vertex " << x3 << " " << y3 << " " << z3 << "\n";
        os << "endloop\n";
        os << "endfacet\n";
        }

        void rectangleFace(ostream &os, double x1, double y1, double z1, double x2, double y2, double z2, double x3, double y3,double z3, double x4, double y4, double z4) const{
                      facet(os, x1, y1, z1, x2, y2, z2, x3, y3, z3);
                      facet(os, x1,y1,z1 , x3,y3,z3 , x4,y4,z4);  
        }
        
        
    public:
        cube(){
            length = breadth = height = 0;
        }
        
        cube(double length, double breadth, double height) : length(length), breadth(breadth), height(height){}
        
        void print(ostream& os) const override{
            os << "solid Cube \n" ;
            rectangleFace(os, x,y,z,  x+length,y,z ,  x+length,y+breadth,z,  x,y+breadth,z);
            rectangleFace(os, x,y,z ,  x,y+breadth,z, x,y+breadth,z+height, x,y,z+height);
            rectangleFace(os, x,y+breadth,z ,  x+length,y+breadth,z , x+length,y+breadth,z+height ,  x,y+breadth,z+height );
            rectangleFace(os, x+length,y,z ,  x+length,y+breadth,z ,  x+length,y+breadth,z+height ,  x+length,y,z+height );
            rectangleFace(os, x,y,z ,  x+length,y,z ,  x+length,y,z+height , x,y,z+height );
            rectangleFace(os, x,y,z+height , x+length,y,z+height , x+length,y+breadth,z+height , x,y+breadth,z+height );
            os<<"endsolid Cube\n";
        }
        
        friend ostream &operator <<(ostream &os , const cube &c){
            return os << "<" << c.length << "," << c.breadth << "," << c.height << ">";
        }
};
class model {
private:
  vector<shape*> shapes;
  ofstream file;
public:
  model(const char filename[]) : file(filename) {
//    file.open(filename);
  }
    // clean up when we're done
  ~model() {
    for (auto s : shapes)
      delete s;

  }
  void add(shape* s) {
    shapes.push_back(s);
  }
  void print() {
    for (auto s : shapes)
      s->print(file);
  }

};

int main() {
  cube c1(1,2,3);
  cout << c1;
  cylinder c2(10, 30);
  cout << c2;

  model m("test1.stl");
  // Don't do this: m.add(&c1);
  m.add(new cube(4,5,6));
  m.add(new cylinder(10, 20));
  
  m.print();
}