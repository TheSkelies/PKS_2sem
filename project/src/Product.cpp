#include "Product.h"

Product::Product(int id, const std::string& name, int quantity, int minThreshold)
    : m_id(id), m_name(name), m_quantity(quantity), m_minThreshold(minThreshold) {}

int Product::getId() const { return m_id; }
std::string Product::getName() const { return m_name; }
int Product::getQuantity() const { return m_quantity; }
int Product::getMinThreshold() const { return m_minThreshold; }

void Product::setName(const std::string& name) { m_name = name; }
void Product::setQuantity(int quantity) { m_quantity = quantity; }
void Product::setMinThreshold(int threshold) { m_minThreshold = threshold; }