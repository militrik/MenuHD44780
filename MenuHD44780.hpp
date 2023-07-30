#ifndef __MENU
#define __MENU

#include <cstdarg>
#include <cstdio>
#include <cstdint>
#include <vector>

/* User definers begin */
#define HD44780_ROWS 2
#define HD44780_COLUMNS 16
/* User definers end */

#define HD44780_MIN_ADDRESS 0
#define HD44780_MAX_ADDRESS 80

class MenuHD44780 {
public:
    enum VarType {
        STRTYPE,
        UINT8TYPE,
        SINT8TYPE,
        UINT16TYPE,
        SINT16TYPE,
        UINT32TYPE,
        SINT32TYPE,
        FLOATTYPE,
    };
    struct Item {
        const char *format;
        void *varPtr;
        VarType varType;
        uint8_t rowPos;
        uint8_t colPos;
        uint16_t blinkTicks;
    };
    typedef void (*pAction)();

    static MenuHD44780 *menuPtr;

    MenuHD44780();
    MenuHD44780(void (*enterF)(), void (*escF)(), void (*leftF)(), void (*rightF)());

    static bool enterAction();
    static bool escAction();
    static bool leftAction();
    static bool rightAction();
    static void setMenuPtr(MenuHD44780 *menuptr);
    static MenuHD44780 *getMenuPtr();
    static char *getDisplayField(uint8_t row);
    static void renewAll();
    void createItem(const char *formatter, void *varPtr, VarType varType, uint8_t rowPos, uint8_t colPos, uint16_t blinkTicks);
    void replaceItem(uint8_t, const char *formatter, void *varPtr, VarType varType, uint8_t rowPos, uint8_t colPos, uint16_t blinkTicks);

private:
    static char displayField[HD44780_ROWS][HD44780_COLUMNS + 1];
    static uint32_t blinkCounter;
    pAction enterF, escF, leftF, rightF;
    //MenuHD44780 *enterVar, *escVar, *leftVar, *rightVar;
    std::vector<Item> items;
};

#endif