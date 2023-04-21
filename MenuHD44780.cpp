#include "MenuHD44780.hpp"
#include <cstring>
#include <algorithm>

char MenuHD44780::displayField[HD44780_ROWS][HD44780_COLUMNS+1] = {0};

MenuHD44780::MenuHD44780() = default;

void MenuHD44780::setMenuPtr(MenuHD44780 *) {}

void MenuHD44780::createItem(const char *formatter, void *varPtr, VarType varType, uint8_t rowPos, uint8_t colPos) {
    Item item = {formatter, varPtr, varType, rowPos, colPos};
    items.push_back(item);
}

void MenuHD44780::renewAll() {
    char row[HD44780_COLUMNS + 1];
    for (Item item: items) {
        switch (item.varType) {
            case STRTYPE:
                sprintf(row, item.format, (char *) item.varPtr);
                break;
            case INTTYPE:
                sprintf(row, item.format, *(int *) item.varPtr);
                break;
            case FLOATTYPE:
                sprintf(row, item.format, *(float *) item.varPtr);
                break;
        }
        strncpy(&MenuHD44780::displayField[item.rowPos][item.colPos], row, strlen(row));
    }
    for (auto & i : MenuHD44780::displayField) {
        std::replace(&i[0], &i[0] + HD44780_COLUMNS, '\0', ' ');
    }
}

char* MenuHD44780::getDisplayField(uint8_t row) {
    return &MenuHD44780::displayField[row][0];
//    return 0;
}