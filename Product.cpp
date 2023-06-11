//
// Created by dumi on 10.06.2023.
//

#include "Product.h"

Product::Product(const std::string &name, std::string categories, int quantity, double price) : name(name),
                                                                                                categories(categories),
                                                                                                quantity(quantity),
                                                                                                price(price) {}

const std::string &Product::getName() const {
    return name;
}
void Product::setName(const std::string &name) {
    Product::name = name;
}

std::string Product::getCategories() const {
    return categories;
}
void Product::setCategories(std::string categories) {
    Product::categories = categories;
}

int Product::getQuantity() const {
    return quantity;
}
void Product::setQuantity(int quantity) {
    Product::quantity = quantity;
}
void Product::addQuantity(int quantity) {
    this->quantity+=quantity;
}
void Product::sellQuantity(int quantity){
    this->quantity-=quantity;
}

double Product::getPrice() const {
    return price;
}
void Product::setPrice(double price) {
    Product::price = price;
}

Product::Product() {

}

nlohmann::json Product::serialize() {
    nlohmann::json data;
    data["name"]= this->getName();
    data["categories"]= this->getCategories();
    data["quantity"]= this->getQuantity();
    data["price"]= this->getPrice();
    return data;
}
Product Product::deserialize(nlohmann::json data) {

    Product x = *new Product;
    x.setName(data["name"].get<std::string>());
    x.setCategories(data["categories"].get<std::string>());
    x.setQuantity(data["quantity"].get<int>());
    x.setPrice(data["price"].get<double>());
    return x;
}

std::ostream& operator<<(std::ostream& os, const Product& data)
{
    os<<"Name: "<<data.getName()<<"\n";
    os<<"Category: "<<data.getCategories()<<"\n";
    os<<"Price: "<<data.getPrice()<<"\n";
    os<<"Quantity: "<<data.getQuantity()<<"\n";
    return os;

}
bool operator== (const Product& p1, const Product& p2)
{
    return (p1.getName() == p2.getName() && p1.getPrice() == p2.getPrice());
}
