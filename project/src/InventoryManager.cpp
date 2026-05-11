#include "InventoryManager.h"
#include <iostream>
#include <iomanip>
#include <sstream>

using namespace std;

void InventoryManager::addToHistory(const string& entry) {
    m_history.push_back(entry);
}

bool InventoryManager::addProduct(int id, const string& name, int quantity, int minThreshold) {
    Product newProd(id, name, quantity, minThreshold);
    if (m_warehouse.addProduct(newProd)) {
        stringstream ss;
        ss << "Добавлен товар: ID=" << id << ", Название=" << name;
        addToHistory(ss.str());
        return true;
    }
    cerr << "Ошибка: товар с ID " << id << " уже существует.\n";
    return false;
}

bool InventoryManager::editProduct(int id, const string& newName, int newQuantity, int newThreshold) {
    Product* prod = m_warehouse.findProduct(id);
    if (!prod) {
        cerr << "Ошибка: товар с ID " << id << " не найден.\n";
        return false;
    }
    Product updated(id, newName, newQuantity, newThreshold);
    if (m_warehouse.updateProduct(id, updated)) {
        stringstream ss;
        ss << "Отредактирован товар ID=" << id;
        addToHistory(ss.str());
        return true;
    }
    return false;
}

bool InventoryManager::removeProduct(int id) {
    if (m_warehouse.removeProduct(id)) {
        stringstream ss;
        ss << "Удалён товар ID=" << id;
        addToHistory(ss.str());
        return true;
    }
    cerr << "Ошибка: товар с ID " << id << " не найден.\n";
    return false;
}

void InventoryManager::listAllProducts() const {
    const auto& products = m_warehouse.getAllProducts();
    if (products.empty()) {
        cout << "Склад пуст.\n";
        return;
    }
    cout << "\n=== Список товаров ===\n";
    cout << left << setw(6) << "ID" 
              << setw(20) << "Название" 
              << setw(10) << "Кол-во" 
              << setw(120) << "Порог" << endl;
    cout << "----------------------------------------\n";
    for (const auto& p : products) {
        cout << left << setw(6) << p.getId()
                  << setw(20) << p.getName()
                  << setw(10) << p.getQuantity()
                  << setw(12) << p.getMinThreshold() << endl;
    }
    cout << endl;
}

bool InventoryManager::registerIncome(int id, int amount) {
    if (amount <= 0) {
        cerr << "Количество прихода должно быть положительным.\n";
        return false;
    }
    Product* prod = m_warehouse.findProduct(id);
    if (!prod) {
        cerr << "Товар с ID " << id << " не найден.\n";
        return false;
    }
    int oldQty = prod->getQuantity();
    prod->setQuantity(oldQty + amount);
    stringstream ss;
    ss << "Приход: ID=" << id << ", +" << amount << " (было " << oldQty << ", стало " << prod->getQuantity() << ")";
    addToHistory(ss.str());

    if (prod->getQuantity() < prod->getMinThreshold()) {
        cout << "Внимание: остаток товара \"" << prod->getName() << "\" ниже порога (" 
                  << prod->getQuantity() << " < " << prod->getMinThreshold() << ")\n";
    }
    return true;
}

bool InventoryManager::registerOutcome(int id, int amount) {
    if (amount <= 0) {
        cerr << "Количество расхода должно быть положительным.\n";
        return false;
    }
    Product* prod = m_warehouse.findProduct(id);
    if (!prod) {
        cerr << "Товар с ID " << id << " не найден.\n";
        return false;
    }
    int oldQty = prod->getQuantity();
    if (oldQty < amount) {
        cerr << "Ошибка: недостаточно товара на складе (доступно " << oldQty << ").\n";
        return false;
    }
    prod->setQuantity(oldQty - amount);
    stringstream ss;
    ss << "Расход: ID=" << id << ", -" << amount << " (было " << oldQty << ", стало " << prod->getQuantity() << ")";
    addToHistory(ss.str());

    if (prod->getQuantity() < prod->getMinThreshold()) {
        cout << "Внимание: остаток товара \"" << prod->getName() << "\" ниже порога (" 
                  << prod->getQuantity() << " < " << prod->getMinThreshold() << ")\n";
    }
    return true;
}

void InventoryManager::showLowStock() const {
    auto low = m_warehouse.getLowStockProducts();
    if (low.empty()) {
        cout << "Нет товаров с низким остатком.\n";
        return;
    }
    cout << "\n=== Товары с низким остатком ===\n";
    for (const auto& p : low) {
        cout << "ID: " << p.getId() 
                  << ", Название: " << p.getName()
                  << ", Остаток: " << p.getQuantity()
                  << ", Порог: " << p.getMinThreshold() << endl;
    }
    cout << endl;
}