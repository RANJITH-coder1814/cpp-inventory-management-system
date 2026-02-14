#include <iostream>
#include <fstream>
#include <iomanip>
using namespace std;

class Product {
public:
    int id;
    string name;
    int quantity;
    float price;

    void input() {
        cout << "Enter Product ID: ";
        cin >> id;
        cout << "Enter Product Name: ";
        cin >> name;
        cout << "Enter Quantity: ";
        cin >> quantity;
        cout << "Enter Price: ";
        cin >> price;
    }

    void display() {
        cout << left << setw(10) << id
             << setw(15) << name
             << setw(10) << quantity
             << setw(10) << price << endl;
    }
};

void addProduct() {
    Product p;
    ofstream file("inventory.txt", ios::app);
    p.input();
    file << p.id << " " << p.name << " " << p.quantity << " " << p.price << endl;
    file.close();
    cout << "Product Added Successfully!\n";
}

void displayProducts() {
    Product p;
    ifstream file("inventory.txt");

    cout << left << setw(10) << "ID"
         << setw(15) << "Name"
         << setw(10) << "Qty"
         << setw(10) << "Price" << endl;

    while (file >> p.id >> p.name >> p.quantity >> p.price) {
        p.display();
    }
    file.close();
}

void searchProduct() {
    int searchId;
    bool found = false;
    Product p;
    ifstream file("inventory.txt");

    cout << "Enter Product ID to search: ";
    cin >> searchId;

    while (file >> p.id >> p.name >> p.quantity >> p.price) {
        if (p.id == searchId) {
            cout << "\nProduct Found:\n";
            p.display();
            found = true;
            break;
        }
    }

    if (!found)
        cout << "Product Not Found!\n";

    file.close();
}

void updateProduct() {
    int searchId;
    bool found = false;
    Product p;

    cout << "Enter Product ID to update: ";
    cin >> searchId;

    ifstream file("inventory.txt");
    ofstream temp("temp.txt");

    while (file >> p.id >> p.name >> p.quantity >> p.price) {
        if (p.id == searchId) {
            cout << "Enter New Details:\n";
            p.input();
            found = true;
        }
        temp << p.id << " " << p.name << " " << p.quantity << " " << p.price << endl;
    }

    file.close();
    temp.close();

    remove("inventory.txt");
    rename("temp.txt", "inventory.txt");

    if (found)
        cout << "Product Updated Successfully!\n";
    else
        cout << "Product Not Found!\n";
}

void deleteProduct() {
    int searchId;
    bool found = false;
    Product p;

    cout << "Enter Product ID to delete: ";
    cin >> searchId;

    ifstream file("inventory.txt");
    ofstream temp("temp.txt");

    while (file >> p.id >> p.name >> p.quantity >> p.price) {
        if (p.id == searchId) {
            found = true;
            continue;
        }
        temp << p.id << " " << p.name << " " << p.quantity << " " << p.price << endl;
    }

    file.close();
    temp.close();

    remove("inventory.txt");
    rename("temp.txt", "inventory.txt");

    if (found)
        cout << "Product Deleted Successfully!\n";
    else
        cout << "Product Not Found!\n";
}

int main() {
    int choice;

    do {
        cout << "\n===== Inventory Management System =====\n";
        cout << "1. Add Product\n";
        cout << "2. Display Products\n";
        cout << "3. Search Product\n";
        cout << "4. Update Product\n";
        cout << "5. Delete Product\n";
        cout << "6. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: addProduct(); break;
            case 2: displayProducts(); break;
            case 3: searchProduct(); break;
            case 4: updateProduct(); break;
            case 5: deleteProduct(); break;
            case 6: cout << "Exiting...\n"; break;
            default: cout << "Invalid Choice!\n";
        }

    } while (choice != 6);

    return 0;
}
