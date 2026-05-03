#ifdef _WIN32
#include <windows.h>
#endif

#include "InventoryManager.h"
#include <iostream>
#include <limits>
#include <string>

void printMenu() {
    std::cout << "\n======= СИСТЕМА УПРАВЛЕНИЯ СКЛАДОМ =======\n";
    std::cout << "1. Добавить товар\n";
    std::cout << "2. Редактировать товар\n";
    std::cout << "3. Удалить товар\n";
    std::cout << "4. Просмотреть все товары\n";
    std::cout << "5. Приход товара\n";
    std::cout << "6. Расход товара\n";
    std::cout << "7. Показать товары с низким остатком\n";
    std::cout << "8. Выйти\n";
    std::cout << "Ваш выбор: ";
}

int main() {
    #ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);
    #endif


    InventoryManager manager;
    int choice;
    bool running = true;

    while (running) {
        printMenu();
        std::cin >> choice;

        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Неверный ввод. Попробуйте снова.\n";
            continue;
        }

        switch (choice) {
            case 1: {
                int id, qty, thr;
                std::string name;
                std::cout << "Введите ID товара: ";
                std::cin >> id;
                std::cout << "Введите название: ";
                std::cin.ignore();
                std::getline(std::cin, name);
                std::cout << "Введите начальное количество: ";
                std::cin >> qty;
                std::cout << "Введите порог низкого остатка: ";
                std::cin >> thr;
                manager.addProduct(id, name, qty, thr);
                break;
            }
            case 2: {
                int id, newQty, newThr;
                std::string newName;
                std::cout << "Введите ID товара для редактирования: ";
                std::cin >> id;
                std::cout << "Новое название: ";
                std::cin.ignore();
                std::getline(std::cin, newName);
                std::cout << "Новое количество: ";
                std::cin >> newQty;
                std::cout << "Новый порог: ";
                std::cin >> newThr;
                manager.editProduct(id, newName, newQty, newThr);
                break;
            }
            case 3: {
                int id;
                std::cout << "Введите ID товара для удаления: ";
                std::cin >> id;
                manager.removeProduct(id);
                break;
            }
            case 4:
                manager.listAllProducts();
                break;
            case 5: {
                int id, amount;
                std::cout << "Введите ID товара: ";
                std::cin >> id;
                std::cout << "Количество прихода: ";
                std::cin >> amount;
                manager.registerIncome(id, amount);
                break;
            }
            case 6: {
                int id, amount;
                std::cout << "Введите ID товара: ";
                std::cin >> id;
                std::cout << "Количество расхода: ";
                std::cin >> amount;
                manager.registerOutcome(id, amount);
                break;
            }
            case 7:
                manager.showLowStock();
                break;
            case 8:
                running = false;
                std::cout << "Выход из программы.\n";
                break;
            default:
                std::cout << "Неверный пункт меню.\n";
        }
    }
    return 0;
}


#ifdef _WIN32
#include <windows.h>
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    return main();
}
#endif