#ifndef WAREHOUSE_H
#define WAREHOUSE_H

#include <vector>
#include <memory>
#include "Product.h"

class Warehouse {
public:
    // Добавление товара (вернёт true, если id уникален)
    bool addProduct(const Product& product);

    // Редактирование товара по id
    bool updateProduct(int id, const Product& newData);

    // Удаление товара по id
    bool removeProduct(int id);

    // Поиск товара по id (возвращает nullptr, если не найден)
    Product* findProduct(int id);

    // Получить все товары
    const std::vector<Product>& getAllProducts() const;

    // Получить товары, количество которых ниже порога
    std::vector<Product> getLowStockProducts() const;

private:
    std::vector<Product> m_products;
};

#endif // WAREHOUSE_H