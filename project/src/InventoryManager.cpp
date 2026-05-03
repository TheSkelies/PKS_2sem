#include "InventoryManager.h"
#include <iostream>
#include <iomanip>
#include <sstream>

void InventoryManager::addToHistory(const std::string& entry) {
    m_history.push_back(entry);
}

bool InventoryManager::addProduct(int id, const std::string& name, int quantity, int minThreshold) {
    Product newProd(id, name, quantity, minThreshold);
    if (m_warehouse.addProduct(newProd)) {
        std::stringstream ss;
        ss << "Добавлен товар: ID=" << id << ", Название=" << name;
        addToHistory(ss.str());
        return true;
    }
    std::cerr << "Ошибка: товар с ID " << id << " уже существует.\n";
    return false;
}

bool InventoryManager::editProduct(int id, const std::string& newName, int newQuantity, int newThreshold) {
    Product* prod = m_warehouse.findProduct(id);
    if (!prod) {
        std::cerr << "Ошибка: товар с ID " << id << " не найден.\n";
        return false;
    }
    Product updated(id, newName, newQuantity, newThreshold);
    if (m_warehouse.updateProduct(id, updated)) {
        std::stringstream ss;
        ss << "Отредактирован товар ID=" << id;
        addToHistory(ss.str());
        return true;
    }
    return false;
}

bool InventoryManager::removeProduct(int id) {
    if (m_warehouse.removeProduct(id)) {
        std::stringstream ss;
        ss << "Удалён товар ID=" << id;
        addToHistory(ss.str());
        return true;
    }
    std::cerr << "Ошибка: товар с ID " << id << " не найден.\n";
    return false;
}

void InventoryManager::listAllProducts() const {
    const auto& products = m_warehouse.getAllProducts();
    if (products.empty()) {
        std::cout << "Склад пуст.\n";
        return;
    }
    std::cout << "\n=== Список товаров ===\n";
    std::cout << std::left << std::setw(6) << "ID" 
              << std::setw(20) << "Название" 
              << std::setw(10) << "Кол-во" 
              << std::setw(12) << "Порог" << std::endl;
    std::cout << "----------------------------------------\n";
    for (const auto& p : products) {
        std::cout << std::left << std::setw(6) << p.getId()
                  << std::setw(20) << p.getName()
                  << std::setw(10) << p.getQuantity()
                  << std::setw(12) << p.getMinThreshold() << std::endl;
    }
    std::cout << std::endl;
}

bool InventoryManager::registerIncome(int id, int amount) {
    if (amount <= 0) {
        std::cerr << "Количество прихода должно быть положительным.\n";
        return false;
    }
    Product* prod = m_warehouse.findProduct(id);
    if (!prod) {
        std::cerr << "Товар с ID " << id << " не найден.\n";
        return false;
    }
    int oldQty = prod->getQuantity();
    prod->setQuantity(oldQty + amount);
    std::stringstream ss;
    ss << "Приход: ID=" << id << ", +" << amount << " (было " << oldQty << ", стало " << prod->getQuantity() << ")";
    addToHistory(ss.str());

    // Проверка низкого остатка (если после прихода всё ещё ниже порога – уведомлять не обязательно, но можно)
    if (prod->getQuantity() < prod->getMinThreshold()) {
        std::cout << "Внимание: остаток товара \"" << prod->getName() << "\" ниже порога (" 
                  << prod->getQuantity() << " < " << prod->getMinThreshold() << ")\n";
    }
    return true;
}

bool InventoryManager::registerOutcome(int id, int amount) {
    if (amount <= 0) {
        std::cerr << "Количество расхода должно быть положительным.\n";
        return false;
    }
    Product* prod = m_warehouse.findProduct(id);
    if (!prod) {
        std::cerr << "Товар с ID " << id << " не найден.\n";
        return false;
    }
    int oldQty = prod->getQuantity();
    if (oldQty < amount) {
        std::cerr << "Ошибка: недостаточно товара на складе (доступно " << oldQty << ").\n";
        return false;
    }
    prod->setQuantity(oldQty - amount);
    std::stringstream ss;
    ss << "Расход: ID=" << id << ", -" << amount << " (было " << oldQty << ", стало " << prod->getQuantity() << ")";
    addToHistory(ss.str());

    if (prod->getQuantity() < prod->getMinThreshold()) {
        std::cout << "Внимание: остаток товара \"" << prod->getName() << "\" ниже порога (" 
                  << prod->getQuantity() << " < " << prod->getMinThreshold() << ")\n";
    }
    return true;
}

void InventoryManager::showLowStock() const {
    auto low = m_warehouse.getLowStockProducts();
    if (low.empty()) {
        std::cout << "Нет товаров с низким остатком.\n";
        return;
    }
    std::cout << "\n=== Товары с низким остатком ===\n";
    for (const auto& p : low) {
        std::cout << "ID: " << p.getId() 
                  << ", Название: " << p.getName()
                  << ", Остаток: " << p.getQuantity()
                  << ", Порог: " << p.getMinThreshold() << std::endl;
    }
    std::cout << std::endl;
}