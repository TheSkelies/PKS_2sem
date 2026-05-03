#ifndef INVENTORYMANAGER_H
#define INVENTORYMANAGER_H

#include "Warehouse.h"
#include <vector>
#include <string>

class InventoryManager {
public:
    // Основные операции
    bool addProduct(int id, const std::string& name, int quantity, int minThreshold);
    bool editProduct(int id, const std::string& newName, int newQuantity, int newThreshold);
    bool removeProduct(int id);
    void listAllProducts() const;
    bool registerIncome(int id, int amount);   // приход
    bool registerOutcome(int id, int amount);  // расход
    void showLowStock() const;

private:
    Warehouse m_warehouse;
    // История операций (для простоты – вектор строк)
    std::vector<std::string> m_history;

    void addToHistory(const std::string& entry);
};

#endif // INVENTORYMANAGER_H