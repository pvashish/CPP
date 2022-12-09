#include <iostream>
using namespace std;

class DynArray {
    
private:
	int* data;
	uint32_t len;
	uint32_t capacity;

	void grow();
	
public:
	
	DynArray(uint32_t capacity) : capacity(capacity), len(0) {
	    data = new int[capacity];
	}
	
	~DynArray(){ 
	    delete[] data; 
	}
	
	void add(int v);
	
	friend ostream& operator <<(ostream& s, const DynArray& d){
	    for (int i = 0; i < d.len; i++) {
            s<<d.data[i]<<" ";
        }
        return s;
	}
};

void DynArray::add(int v)
{
    if (len == capacity) {
            grow(); 
    }
    data[len] = v;
    len++;
}

void DynArray::grow()
{
    int* temp = new int[capacity];
    //int *temp= nullptr;
    if (len == capacity) {
        temp = new int[len * 2];
        for (int i = 0; i < len; i++) {
            temp[i] = data[i];
        }
	}
	delete[] data;
    data = temp;
    len = len * 2;
}


int main(){
    
  DynArray a(100); // preallocate 100 size
  for (int i = 0; i < 100; i++)
    a.add(i); // this should take O(100) time
  a.add(101);
  cout<<"the dynamic array is: "<<"\n"<<a;
}