#include <iostream>
using namespace std;

class Rectangle {
private:
    int length;
    int width;

public:
    Rectangle(int l, int w) : length(l), width(w) {}

    Rectangle(const Rectangle& other) {
        length = other.length;
        width = other.width;
    }

    int area() const {
        return length * width;
    }

    int perimeter() const {
        return 2 * (length + width);
    }

    void display() const {
        cout << "Length: " << length << ", Width: " << width << endl;
        cout << "Area: " << area() << ", Perimeter: " << perimeter() << endl;
    }
};

int main() {
    Rectangle rect1(10, 5);
    Rectangle rect2 = rect1;

    rect1.display();
    rect2.display();

    return 0;
}
