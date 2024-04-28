#include <iostream>
#include <string>
#include <ctime>
using namespace std;

struct Product {
    string name;
    unsigned long long expiryDate;
    int size;
//public:
//    Product();
//    Product(string name, int size, unsigned long long expiryDate ) {
//        this->name = name;
//        this->expiryDate = expiryDate;
//        this->size = size;
//    }
};

class Fridge {
private:
    string model;
    int size;
    int prodSize = 0;
    int prodCount = 0;
    Product* products = new Product[0];
public:
    Fridge(string model, int size) {
        this->model = model;
        this->size = size;
    }
    string getModel() {
        return this->model;
    }
    int getSize() {
        return this->size;
    }
    int getProductsAmt() {
        return this->prodCount;
    }
    Product* getProducts() {
        Product* buf = new Product[this->prodCount];

        for (int i = 0; i < this->prodCount; i++) {
            buf[i] = Product{ this->products[i].name, this->products[i].expiryDate, this->products[i].size };
        }
        return buf;
    }
    void showProducts() {
        for (int i = 0; i < this->prodCount; i++) {
            cout << "Название продукта: " << this->products[i].name << ", Размер продукта: " << this->products[i].size << ", Срок годности: " << this->products[i].expiryDate << endl;
        }
    }
    void addProduct(Product product) {
        if (prodSize == this->size || prodSize + product.size > this->size) {
            cout << "Холодильник заполнен." << endl;
        }
        Product* buf = new Product[this->prodCount + 1];

        for (int i = 0; i < this->prodCount; i++) {
            buf[i] = this->products[i];
        }
        buf[this->prodCount++] = product;
        this->prodSize += product.size;
        delete[]this->products;
        this->products = buf;
    }
    
    void removeProduct(string name) {
        bool flag = false;
        for (int i = 0; i < this->prodCount; i++) {
            if (this->products[i].name == name) {
                flag = true;
                break;
            }
        }
        if (flag) {
            cout << "Продукта с таким именем нет..." << endl;
            return;
        }
        flag = false;
        Product* buf = new Product[this->prodCount - 1];
        for (int i = 0, k = 0; i < this->prodCount; i++) {
            if (!flag && this->products[i].name == name) {
                this->prodSize -= products[i].size;
                continue;
            }
            buf[k++] = this->products[i];
        }

        this->prodCount--;
        delete[]this->products;
        this->products = buf;
    }
    void prodTimeout() {
        int count = 0;
        unsigned long long timeNow = time(0);
        for (int i = 0; i < this->prodCount; i++) {
            if (this->products[i].expiryDate <= timeNow) {
                count++;
            }
        }
        if (count == 0) {
            return;
        }
        Product* buf = new Product[this->prodCount - count];
        for (int i = 0, k = 0; i < this->prodCount; i++) {
            if (this->products[i].expiryDate <= timeNow) {
                this->prodSize -= products[i].size;
                continue;
            }
            buf[k++] = this->products[i];
        }

        this->prodCount -= count;
        delete[]this->products;
        this->products = buf;
    }
    ~Fridge() {
        delete[]this->products;
    }
};

Product createProduct(string name, int size , unsigned long long expiryDate ) {

    Product product;
    product.name = name;
    product.size = size;
    product.expiryDate = expiryDate;
    return product;
}
int main()
{
    setlocale(LC_ALL, "rus");
    Fridge fr1("Hiens", 52);
    Product pr1 = createProduct("Бананы", 24, 55555);
    fr1.addProduct(pr1);
    fr1.showProducts();

}
