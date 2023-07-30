#include "MenuHD44780.hpp"
#include <cstring>
#include <algorithm>

char MenuHD44780::displayField[HD44780_ROWS][HD44780_COLUMNS + 1] = {0};

uint32_t MenuHD44780::blinkCounter = 0;

MenuHD44780::MenuHD44780() = default;

MenuHD44780::MenuHD44780(void (*enterF)(), void (*escF)(), void (*leftF)(), void (*rightF)())
        : enterF(enterF), escF(escF), leftF(leftF), rightF(rightF) {}

MenuHD44780 *MenuHD44780::menuPtr = nullptr;

void MenuHD44780::setMenuPtr(MenuHD44780 *menuptr) {
    MenuHD44780::menuPtr = menuptr;
}

MenuHD44780 *MenuHD44780::getMenuPtr() {
    return menuPtr;
}

void MenuHD44780::createItem(const char* name, Item item) {
    items[const_cast<char*>(name)] = item;
}

void MenuHD44780::renewAll() {
    blinkCounter++;
    memset(displayField, 0, sizeof(displayField));
    char row[HD44780_COLUMNS + 1];
    for (auto item: getMenuPtr()->items) {
        switch (item.second.varType) {
            case STRTYPE:
                snprintf(row, sizeof row, item.second.format, (char *) item.second.varPtr);
                break;
            case UINT8TYPE:
                snprintf(row, sizeof row, item.second.format, *(uint8_t *) item.second.varPtr);
                break;
            case SINT8TYPE:
                snprintf(row, sizeof row, item.second.format, *(int8_t *) item.second.varPtr);
                break;
            case UINT16TYPE:
                snprintf(row, sizeof row, item.second.format, *(uint16_t *) item.second.varPtr);
                break;
            case SINT16TYPE:
                snprintf(row, sizeof row, item.second.format, *(int16_t *) item.second.varPtr);
                break;
            case UINT32TYPE:
                snprintf(row, sizeof row, item.second.format, *(uint32_t *) item.second.varPtr);
                break;
            case SINT32TYPE:
                snprintf(row, sizeof row, item.second.format, *(int32_t *) item.second.varPtr);
                break;
            case FLOATTYPE:
                snprintf(row, sizeof row, item.second.format, *(float *) item.second.varPtr);
                break;
        }
        if (item.second.blinkTicks>=2){
            if (blinkCounter % item.second.blinkTicks < item.second.blinkTicks / 2)
                std::fill_n(row, strlen(row), ' ');
        }
        strncpy(&MenuHD44780::displayField[item.second.rowPos][item.second.colPos], row, strlen(row));
    }
    for (auto &i: MenuHD44780::displayField) {
        std::replace(i, i + HD44780_COLUMNS, '\0', ' ');
    }
}

char *MenuHD44780::getDisplayField(uint8_t row) {
    return &MenuHD44780::displayField[row][0];
}

bool MenuHD44780::enterAction() {
    if (getMenuPtr()->enterF != nullptr) {
        getMenuPtr()->enterF();
        renewAll();
        return true;
    }
    return false;
}

bool MenuHD44780::escAction() {
    if (getMenuPtr()->escF != nullptr) {
        getMenuPtr()->escF();
        renewAll();
        return true;
    }
    return false;
}

bool MenuHD44780::leftAction() {
    if (getMenuPtr()->leftF != nullptr) {
        getMenuPtr()->leftF();
        renewAll();
        return true;
    }
    return false;
}

bool MenuHD44780::rightAction() {
    if (getMenuPtr()->rightF != nullptr) {
        getMenuPtr()->rightF();
        renewAll();
        return true;
    }
    return false;
}

