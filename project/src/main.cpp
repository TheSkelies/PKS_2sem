#ifdef _WIN32
#include <windows.h>
#endif

#include "InventoryManager.h"
#include <iostream>
#include <limits>
#include <string>

using namespace std;

void printMenu() {
    cout << "\n======= СИСТЕМА УПРАВЛЕНИЯ СКЛАДОМ =======\n";
    cout << "1. Добавить товар\n";
    cout << "2. Редактировать товар\n";
    cout << "3. Удалить товар\n";
    cout << "4. Просмотреть все товары\n";
    cout << "5. Приход товара\n";
    cout << "6. Расход товара\n";
    cout << "7. Показать товары с низким остатком\n";
    cout << "8. Выйти\n";
    cout << "Ваш выбор: ";
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
        cin >> choice;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Неверный ввод. Попробуйте снова.\n";
            continue;
        }

        switch (choice) {
            case 1: {
                int id, qty, thr;
                string name;
                cout << "Введите ID товара: ";
                cin >> id;
                cout << "Введите название: ";
                cin.ignore();
                getline(cin, name);
                cout << "Введите начальное количество: ";
                cin >> qty;
                cout << "Введите порог низкого остатка: ";
                cin >> thr;
                manager.addProduct(id, name, qty, thr);
                break;
            }
            case 2: {
                int id, newQty, newThr;
                string newName;
                cout << "Введите ID товара для редактирования: ";
                cin >> id;
                cout << "Новое название: ";
                cin.ignore();
                getline(cin, newName);
                cout << "Новое количество: ";
                cin >> newQty;
                cout << "Новый порог: ";
                cin >> newThr;
                manager.editProduct(id, newName, newQty, newThr);
                break;
            }
            case 3: {
                int id;
                cout << "Введите ID товара для удаления: ";
                cin >> id;
                manager.removeProduct(id);
                break;
            }
            case 4:
                manager.listAllProducts();
                break;
            case 5: {
                int id, amount;
                cout << "Введите ID товара: ";
                cin >> id;
                cout << "Количество прихода: ";
                cin >> amount;
                manager.registerIncome(id, amount);
                break;
            }
            case 6: {
                int id, amount;
                cout << "Введите ID товара: ";
                cin >> id;
                cout << "Количество расхода: ";
                cin >> amount;
                manager.registerOutcome(id, amount);
                break;
            }
            case 7:
                manager.showLowStock();
                break;
            case 8:
                running = false;
                cout << "Выход из программы.\n";
                break;
            default:
                cout << "Неверный пункт меню.\n";
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