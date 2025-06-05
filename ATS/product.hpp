#ifndef PRODUCT_HPP
#define PRODUCT_HPP

#include <string>
#include <vector>

class Product {
private:
    std::string productId;
    std::string name;
    std::string category;
    std::string price;
    std::string quantity;
    std::string storeLocation;
    std::string res;
    std::string filePath = "product_details.csv";
public:
    std::vector<std::string> askDetails();
    std::vector<std::string> appendDetails();
    bool isProductExist(std::string productId);
    std::vector<std::string> getDetails(std::string productId);
    bool updateProductDetails(std::string productId);
    std::vector<std::vector<std::string>> getProductsByCategory(std::string category);
    std::vector<std::vector<std::string>> getProducts();
};

#endif
