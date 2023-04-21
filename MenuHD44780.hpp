#ifndef __MENU
#define __MENU

#include <cstdarg>
#include <cstdio>
#include <cstdint>
#include <vector>

enum VarType {
    STRTYPE, INTTYPE, FLOATTYPE
};

struct Item {
    const char *format;
    void *varPtr;
    VarType varType;
    uint8_t pos;
};

class MenuHD44780 {
public:
    static MenuHD44780 *menuPtr;
    static char firstString[];
    static char secondString[];

    MenuHD44780();

    static void setMenuPtr(MenuHD44780 *);

    void createItem(const char *formatter, void *varPtr, VarType varType, uint8_t pos);

    void renewAll();

private:
    std::vector<Item> items;


};

#endif