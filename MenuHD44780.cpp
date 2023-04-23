#include "MenuHD44780.hpp"
#include <cstring>
#include <algorithm>

char MenuHD44780::displayField[HD44780_ROWS][HD44780_COLUMNS + 1] = {0};

MenuHD44780::MenuHD44780() = default;

MenuHD44780 *MenuHD44780::menuPtr = nullptr;

void MenuHD44780::setMenuPtr(MenuHD44780 *menuptr) {
    MenuHD44780::menuPtr = menuptr;
}

MenuHD44780 *MenuHD44780::getMenuPtr() {
    return menuPtr;
}

void MenuHD44780::createItem(const char *formatter, void *varPtr, VarType varType, uint8_t rowPos, uint8_t colPos) {
    Item item = {formatter, varPtr, varType, rowPos, colPos};
    items.push_back(item);
}

void MenuHD44780::renewAll() {
#include <cstring> // For memset

    memset(displayField, 0, sizeof(displayField));
    char row[HD44780_COLUMNS + 1];
    for (Item item: getMenuPtr()->items) {
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
    for (auto &i: MenuHD44780::displayField) {
        std::replace(i, i + HD44780_COLUMNS, '\0', ' ');
    }

////////////
    for (uint8_t i = 0; i < HD44780_ROWS; ++i) {
        printf("%s\n", MenuHD44780::getDisplayField(i));
    }
    /////////////

}

char *MenuHD44780::getDisplayField(uint8_t row) {
    return &MenuHD44780::displayField[row][0];
//    return 0;
}


bool MenuHD44780::enterAction() {
    if (getMenuPtr()->enterF != nullptr) {
        getMenuPtr()->enterF(getMenuPtr()->enterVar);
        renewAll();
        return true;
    }
    return false;
}

bool MenuHD44780::escAction() {
    if (getMenuPtr()->enterF != nullptr) {
        getMenuPtr()->enterF(getMenuPtr()->enterVar);
        renewAll();
        return true;
    }
    return false;
}

bool MenuHD44780::leftAction() {
    if (getMenuPtr()->enterF != nullptr) {
        getMenuPtr()->enterF(getMenuPtr()->enterVar);
        renewAll();
        return true;
    }
    return false;
}

bool MenuHD44780::rightAction() {
    if (getMenuPtr()->enterF != nullptr) {
        getMenuPtr()->enterF(getMenuPtr()->enterVar);
        renewAll();
        return true;
    }
    return false;
}

MenuHD44780::MenuHD44780(void (*enterF)(MenuHD44780 *), MenuHD44780 *enterVar,
                         void (*escF)(MenuHD44780 *), MenuHD44780 *escVar,
                         void (*leftF)(MenuHD44780 *), MenuHD44780 *leftVar,
                         void (*rightF)(MenuHD44780 *), MenuHD44780 *rightVar) :
        enterF(enterF), enterVar(enterVar),
        escF(escF), escVar(escVar),
        leftF(leftF), leftVar(leftVar),
        rightF(rightF), rightVar(rightVar) {}


