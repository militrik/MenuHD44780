#ifndef __MENU
#define __MENU

#include <cstdarg>
#include <cstdio>
#include <cstdint>
#include <vector>

/* User definers */
#define HD44780_ROWS 2
#define HD44780_COLUMNS 16

#define HD44780_MIN_ADDRESS 0
#define HD44780_MAX_ADDRESS 80

enum VarType {
    STRTYPE, INTTYPE, FLOATTYPE
};

struct Item {
    const char *format;
    void *varPtr;
    VarType varType;
    uint8_t rowPos;
    uint8_t colPos;
};

class MenuHD44780 {
public:
    static MenuHD44780 *menuPtr;


    MenuHD44780();

    static void setMenuPtr(MenuHD44780 *);

    void createItem(const char *formatter, void *varPtr, VarType varType, uint8_t rowPos, uint8_t colPos);

    void renewAll();

    static char* getDisplayField(uint8_t);

private:
    static char displayField[HD44780_ROWS][HD44780_COLUMNS+1];
    std::vector<Item> items;
};

#endif