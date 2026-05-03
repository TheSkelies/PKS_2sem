#include "Warehouse.h"
#include <algorithm>

bool Warehouse::addProduct(const Product& product) {
    if (findProduct(product.getId()) != nullptr) {
        return false; // id уже существует
    }
    m_products.push_back(product);
    return true;
}

bool Warehouse::updateProduct(int id, const Product& newData) {
    for (auto& p : m_products) {
        if (p.getId() == id) {
            p = newData;
            return true;
        }
    }
    return false;
}

bool Warehouse::removeProduct(int id) {
    auto it = std::remove_if(m_products.begin(), m_products.end(),
                             [id](const Product& p) { return p.getId() == id; });
    if (it != m_products.end()) {
        m_products.erase(it, m_products.end());
        return true;
    }
    return false;
}

Product* Warehouse::findProduct(int id) {
    for (auto& p : m_products) {
        if (p.getId() == id) {
            return &p;
        }
    }
    return nullptr;
}

const std::vector<Product>& Warehouse::getAllProducts() const {
    return m_products;
}

std::vector<Product> Warehouse::getLowStockProducts() const {
    std::vector<Product> low;
    for (const auto& p : m_products) {
        if (p.getQuantity() < p.getMinThreshold()) {
            low.push_back(p);
        }
    }
    return low;
}