#include <iostream>

using namespace std;

class three {

public:
    int side1;
    int side2;
    int side3;

public:
    void checkTriangle(){
        cout << endl;
        if(side1==side2 && side2==side3 && side3 == side1){
            cout << "The triangle is Equilateral with sides " << side1 <<"," << side2 <<"," << side3 << endl;
        }
        else if(side1 != side2 && side2 != side3 && side3 != side1){
            cout << "The triangle is Scalene with sides " << side1 <<"," << side2 <<"," << side3 << endl;
        }
        else{
            cout << "The triangle is Isosceles with sides " << side1 <<"," << side2 <<"," << side3 << endl;
        }
    }
    void getInput(){
            cout << "Enter the sides of triangle respectively" <<endl;
            cin >> side1 >> side2 >> side3;
    }
};

int main(){

 three tri1;

 tri1.getInput();
 tri1.checkTriangle();

 return 0;

}
