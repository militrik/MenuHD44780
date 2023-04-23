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

//onFunc;

class MenuHD44780 {
public:
    typedef void (*pAction)(MenuHD44780 *);

    static MenuHD44780 *menuPtr;

    MenuHD44780();
    MenuHD44780(void (*enterF)(MenuHD44780 *), MenuHD44780 *enterVar,
                void (*escF)(MenuHD44780 *), MenuHD44780 *escVar,
                void (*leftF)(MenuHD44780 *), MenuHD44780 *leftVar,
                void (*rightF)(MenuHD44780 *), MenuHD44780 *rightVar);
    static bool enterAction();
    static bool escAction();
    static bool leftAction();
    static bool rightAction();
    static void setMenuPtr(MenuHD44780 *menuptr);
    static MenuHD44780 *getMenuPtr();
    static char *getDisplayField(uint8_t row);
    static void renewAll();
    void createItem(const char *formatter, void *varPtr, VarType varType, uint8_t rowPos, uint8_t colPos);

private:
    static char displayField[HD44780_ROWS][HD44780_COLUMNS + 1];
    pAction enterF, escF, leftF, rightF;
    MenuHD44780 *enterVar, *escVar, *leftVar, *rightVar;
    std::vector<Item> items;
};

#endif