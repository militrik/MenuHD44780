#include "MenuHD44780.hpp"
#include <cstring>
#include <algorithm>

char MenuHD44780::firstString[17];
char MenuHD44780::secondString[17];


MenuHD44780::MenuHD44780() = default;

void MenuHD44780::setMenuPtr(MenuHD44780 *) {

}

void MenuHD44780::createItem(const char *formatter, void *varPtr, VarType varType, uint8_t pos) {
    Item item = {formatter, varPtr, varType, pos};
    items.push_back(item);
}

void MenuHD44780::renewAll() {
    char row[17];
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
        strncpy(item.pos < 40 ? firstString + item.pos : secondString + item.pos - 40, row, strlen(row));
    }
    std::replace((char*)firstString, &firstString[0]+sizeof (firstString)-1, '\0', ' ');
    std::replace((char*)secondString, &secondString[0]+sizeof (secondString)-1, '\0', ' ');
}

