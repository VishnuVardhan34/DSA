//q1
#include <iostream>
#include <stdexcept>

class ArrayHandler {
private:
    static const int SIZE = 5;
    int arr[SIZE];

public:
    void inputElements() {
        std::cout << "Enter " << SIZE << " elements for the array:\n";
        for (int i = 0; i < SIZE; ++i) {
            std::cin >> arr[i];
        }
    }

    int getElement(int index) {
        if (index < 0 || index >= SIZE) {
            throw std::out_of_range("Index out of bounds");
        }
        return arr[index];
    }
};

int main() {
    ArrayHandler arrayHandler;
    int index;

    arrayHandler.inputElements();

    std::cout << "Enter an index to access an element (0 to 4): ";
    std::cin >> index;

    try {
        int element = arrayHandler.getElement(index);
        std::cout << "Element at index " << index << " is: " << element << std::endl;
    }
    catch (const std::out_of_range& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    return 0;
}

