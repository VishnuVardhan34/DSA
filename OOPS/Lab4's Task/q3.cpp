#include <iostream>
using namespace std;

class Vector3D {
private:
    double x, y, z;

public:
    Vector3D(double xVal = 0, double yVal = 0, double zVal = 0) : x(xVal), y(yVal), z(zVal) {}

    double operator*(const Vector3D& other) const {
        return x * other.x + y * other.y + z * other.z;
    }

    void display() const {
        cout << "(" << x << ", " << y << ", " << z << ")";
    }
};

int main() {
    double x1, y1, z1, x2, y2, z2;
    cout << "Enter the x, y, and z components of the first vector: ";
    cin >> x1 >> y1 >> z1;
    Vector3D vec1(x1, y1, z1);

    cout << "Enter the x, y, and z components of the second vector: ";
    cin >> x2 >> y2 >> z2;
    Vector3D vec2(x2, y2, z2);

    double dotProduct = vec1 * vec2;

    cout << "First vector: ";
    vec1.display();
    cout << "\nSecond vector: ";
    vec2.display();
    cout << "\nDot product: " << dotProduct << endl;

    return 0;
}

