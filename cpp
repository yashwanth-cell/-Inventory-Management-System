#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
using namespace std;

// Product class to handle product information
class Product {
public:
    string name;
    float price;
    int quantity;
    
    Product(string productName, float productPrice, int productQuantity)
        : name(productName), price(productPrice), quantity(productQuantity) {}

    void displayProduct() {
        cout << "Product Name: " << name << endl;
        cout << "Price: " << fixed << setprecision(2) << price << endl;
        cout << "Quantity: " << quantity << endl;
    }
};

// Inventory class to manage products in the inventory
class Inventory {
private:
    vector<Product> products;

public:
    // Add a new product to the inventory
    void addProduct(const Product& product) {
        products.push_back(product);
        cout << "Product added successfully!" << endl;
    }

    // Display all products in the inventory
    void displayInventory() {
        if (products.empty()) {
            cout << "No products in the inventory!" << endl;
            return;
        }

        cout << "Inventory List: " << endl;
        for (const auto& product : products) {
            product.displayProduct();
            cout << "----------------------------" << endl;
        }
    }

    // Update the quantity of a product in the inventory
    void updateStock(string productName, int quantity) {
        for (auto& product : products) {
            if (product.name == productName) {
                product.quantity += quantity;
                cout << "Stock updated successfully!" << endl;
                return;
            }
        }
        cout << "Product not found!" << endl;
    }

    // Search for a product in the inventory
    void searchProduct(string productName) {
        for (const auto& product : products) {
            if (product.name == productName) {
                cout << "Product found!" << endl;
                product.displayProduct();
                return;
            }
        }
        cout << "Product not found!" << endl;
    }
};

// Sales class to handle sales transactions
class Sales {
public:
    // Make a sale and update the inventory
    void makeSale(Inventory& inventory, string productName, int quantity) {
        for (auto& product : inventory.products) {
            if (product.name == productName && product.quantity >= quantity) {
                product.quantity -= quantity;
                cout << "Sale Successful!" << endl;
                cout << "Total Amount: " << fixed << setprecision(2) << (quantity * product.price) << endl;
                return;
            }
        }
        cout << "Product not found or insufficient stock!" << endl;
    }
};

// Main function to provide a menu-driven interface
int main() {
    Inventory inventory;
    Sales sales;
    int choice;

    while (true) {
        cout << "\nInventory Management System\n";
        cout << "1. Add Product\n";
        cout << "2. Display Inventory\n";
        cout << "3. Update Stock\n";
        cout << "4. Search Product\n";
        cout << "5. Make Sale\n";
        cout << "6. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: {
                string name;
                float price;
                int quantity;

                cout << "Enter product name: ";
                cin >> name;
                cout << "Enter product price: ";
                cin >> price;
                cout << "Enter product quantity: ";
                cin >> quantity;

                Product newProduct(name, price, quantity);
                inventory.addProduct(newProduct);
                break;
            }
            case 2:
                inventory.displayInventory();
                break;

            case 3: {
                string productName;
                int quantity;

                cout << "Enter product name to update stock: ";
                cin >> productName;
                cout << "Enter quantity to add: ";
                cin >> quantity;

                inventory.updateStock(productName, quantity);
                break;
            }
            case 4: {
                string productName;
                cout << "Enter product name to search: ";
                cin >> productName;

                inventory.searchProduct(productName);
                break;
            }
            case 5: {
                string productName;
                int quantity;

                cout << "Enter product name to sell: ";
                cin >> productName;
                cout << "Enter quantity to sell: ";
                cin >> quantity;

                sales.makeSale(inventory, productName, quantity);
                break;
            }
            case 6:
                cout << "Exiting the system. Goodbye!" << endl;
                return 0;

            default:
                cout << "Invalid choice! Please try again." << endl;
        }
    }

    return 0;
}
