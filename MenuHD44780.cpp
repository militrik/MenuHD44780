#include "MenuHD44780.hpp"
#include <cstring>
#include <algorithm>

char MenuHD44780::displayField[HD44780_ROWS][HD44780_COLUMNS + 1] = {0};
MenuHD44780::MenuHD44780() = default;
MenuHD44780 * MenuHD44780::menuPtr = nullptr;

void MenuHD44780::setMenuPtr(MenuHD44780 *menuptr) {
    MenuHD44780::menuPtr = menuptr;
}

MenuHD44780 *MenuHD44780::getMenuPtr() {
    return menuPtr;
}

void MenuHD44780::createItem(const char *formatter, void *varPtr, VarType varType,  uint8_t rowPos, uint8_t colPos) {
    Item item = {formatter, varPtr, varType, rowPos, colPos};
    items.push_back(item);
}

void MenuHD44780::renewAll() {
#include <cstring> // For memset
    memset(displayField, 0, sizeof(displayField));
    char row[HD44780_COLUMNS + 1];
    for (Item item: (*MenuHD44780::menuPtr).items) {
        switch (item.varType) {
            case STRTYPE:
                snprintf(row, sizeof row, item.format, (char *) item.varPtr);
                break;
            case INTTYPE:
                snprintf(row, sizeof row, item.format, *(uint8_t *) item.varPtr);
                break;
            case FLOATTYPE:
                snprintf(row, sizeof row, item.format, *(float *) item.varPtr);
                break;
        }
        strncpy(&MenuHD44780::displayField[item.rowPos][item.colPos], row, strlen(row));
    }
//    for (uint8_t i = 0; i < HD44780_ROWS; ++i) {
//        std::replace(&MenuHD44780::displayField[i][0], &MenuHD44780::displayField[i][0] + HD44780_COLUMNS, '\0', ' ');
//    }
    for (auto &i: MenuHD44780::displayField) {
        std::replace(i, i + HD44780_COLUMNS, '\0', ' ');
    }
}

char *MenuHD44780::getDisplayField(uint8_t row) {
    return &MenuHD44780::displayField[row][0];
//    return 0;
}

MenuHD44780::MenuHD44780(MenuHD44780 *enterPtr, MenuHD44780 *escPtr, MenuHD44780 *leftPtr,
                         MenuHD44780 *rightPtr) : enterPtr(enterPtr), escPtr(escPtr),
                                                     leftPtr(leftPtr), rightPtr(rightPtr) {}

void MenuHD44780::enterAction() {
    menuPtr = MenuHD44780::menuPtr->enterPtr;
    MenuHD44780::renewAll();
}

void MenuHD44780::escAction() {
    menuPtr = MenuHD44780::menuPtr->escPtr;
    MenuHD44780::renewAll();
}

void MenuHD44780::leftAction() {
    menuPtr = MenuHD44780::menuPtr->leftPtr;
    MenuHD44780::renewAll();
}

void MenuHD44780::rightAction() {
    menuPtr = MenuHD44780::menuPtr->rightPtr;
    MenuHD44780::renewAll();
}

