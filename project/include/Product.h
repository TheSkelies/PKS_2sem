#ifndef PRODUCT_H
#define PRODUCT_H

#include <string>

class Product {
public:
    Product(int id, const std::string& name, int quantity, int minThreshold);

    int getId() const;
    std::string getName() const;
    int getQuantity() const;
    int getMinThreshold() const;

    void setName(const std::string& name);
    void setQuantity(int quantity);
    void setMinThreshold(int threshold);

private:
    int m_id;
    std::string m_name;
    int m_quantity;
    int m_minThreshold;
};

#endif // PRODUCT_H