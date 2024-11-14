#include <iostream>
#include <string>

using namespace std;

class Vehicle{
    protected:
    int vehicle_ID;
    string brand;
    float rent_rate;
    
    public:
    Vehicle(){
        cout << "Specify the Vehicle ID" << endl;
        cin >> vehicle_ID;
        cout << "Specify Brand" << endl;
        cin >> brand;
        cout << "Rental per day: ";
        cin >> rent_rate;
    }
    
    virtual void vehicleData() const{
        cout<< endl << "------Vehicle's Information-------" << endl;
        cout << "Vehicle ID: " << vehicle_ID << endl;
        cout << "Brand: " << brand << endl;
        cout << "Rental per day: $" << rent_rate << endl;
    }
};

class Car: virtual public Vehicle{
    protected:
    int seats;
    char air;
    
    public:
    Car(){
        cout << "Number of seats" << endl;
        cin >> seats ;
        cout << "Air conditioned?" << endl;
        cin >> air;
    }
    
    void vehicleData() const override {
        Vehicle :: vehicleData();
        cout << "Number of seats" << seats << endl;
        cout << "Air conditioned: " << air << endl;
    }
};

class Truck : virtual public Vehicle{
    protected:
    float cargo;
    int wheels;
    
    public:
    Truck(){
        cout << "Cargo capacity: ";
        cin>> cargo;
        cout << endl << "Number of wheels: ";
        cin >> wheels;
    }
    
    void vehicleData() const override{
        Vehicle :: vehicleData();
        
        cout << "Cargo capacity: " << cargo;
        cout << endl << "Number of wheels: " << wheels << endl;
    }
};

class PickupTruck : public Car, public Truck{
    public:
    PickupTruck(){
        cout << "Number of seats" << endl;
        cin >> seats ;
        cout << "Air conditioned?" << endl;
        cin >> air;
        cout << "Cargo capacity: ";
        cin>> cargo;
        cout << endl << "Number of wheels: ";
        cin >> wheels;
    }
    
    void vehicleData()const override {
        Vehicle :: vehicleData();
        Car :: vehicleData();
        Truck :: vehicleData();
    }
};

int main(){
    Vehicle * vehiclePtr = nullptr;
    int choice;
while(choice!=-1){
    cout << endl;
    cout << "Choose the type of vehicle to create:\n";
    cout << "1. Car\n";
    cout << "2. Truck\n";
    cout << "3. Pickup Truck\n";
    cout << "-1 to exit\n";
    cout << "Enter your choice: ";
    cin >> choice;
    
    switch (choice) {
        case 1:
            vehiclePtr = new Car();
            break;
        case 2:
            vehiclePtr = new Truck();
            break;
        case 3:
            vehiclePtr = new PickupTruck();
            break;
        case -1:
            exit(0);
            break;
        default:
            cout << "Invalid choice!" << endl;
            break;
    } 
    
    vehiclePtr->vehicleData();
    
    delete vehiclePtr;
}
    return 0;
}
