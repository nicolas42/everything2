// g++ cpp_classes.cpp && ./a.out

// classes are the same as structs except their data is private by default
// function pointers are not stored within the struct.
// methods can be defined inside or outside of the class
// but prototypes are always required inside the class definition
// C++ bool is the same as int.
// the public: and private: labels can be used to specify the visibility of elements in a class

#include <iostream>

using namespace std;

struct Box {
    float length;
    float breadth;
    float height;
    float volume() {
        return length * breadth * height;
    }
    float do_something();
};

float Box::do_something(){
    return 0.5 * volume();
}

int main() {

    cout << "\n\n";
    cout << "function pointers are not stored within structs/classes\n";
    cout << "sizeof(Box): " << sizeof(Box) << "\n";

    Box b;
    b.length = 1;
    b.breadth = 2;
    b.height = 3;

    cout << "volume: " << b.volume() << endl;
    cout << b.do_something() << endl;

   return 0;
}
