# Опис класу MenuHD44780

Клас `MenuHD44780` забезпечує можливість створення та керування меню на дисплеї з контролером HD44780. Цей клас надає зручний інтерфейс для додавання елементів меню, зчитування та відображення значень змінних, а також обробку взаємодії з користувачем.

## Поля класу

### `/* User definers begin */`

Ці директиви `#define` дозволяють користувачу налаштувати розміри дисплея HD44780, що використовується для відображення меню. Користувач може встановити значення констант `HD44780_ROWS` та `HD44780_COLUMNS` залежно від конфігурації свого дисплея.

- `HD44780_ROWS`: Визначає кількість рядків на дисплеї.
- `HD44780_COLUMNS`: Визначає кількість стовпців на дисплеї.

Ці константи можна змінити за бажанням, а клас `MenuHD44780` буде автоматично використовувати нові значення для налаштування розмірів дисплея.

### `enum VarType`

Це перерахування визначає типи даних змінних, які можуть використовуватись у меню. Доступні типи даних:
- `STRTYPE`: Рядковий тип (char*)
- `UINT8TYPE`: Беззнаковий 8-бітний тип (uint8_t)
- `SINT8TYPE`: Знаковий 8-бітний тип (int8_t)
- `UINT16TYPE`: Беззнаковий 16-бітний тип (uint16_t)
- `SINT16TYPE`: Знаковий 16-бітний тип (int16_t)
- `UINT32TYPE`: Беззнаковий 32-бітний тип (uint32_t)
- `SINT32TYPE`: Знаковий 32-бітний тип (int32_t)
- `FLOATTYPE`: Тип з плаваючою точкою (float)

### `struct Item`

Структура `Item` представляє елемент меню. Кожен елемент містить наступні поля:
- `const char *format`: Формат для відображення значення змінної на дисплеї.
- `void *varPtr`: Вказівник на змінну, значення якої буде відображатись на дисплеї.
- `VarType varType`: Тип даних змінної, що зберігається за вказівником `varPtr`.
- `uint8_t rowPos`: Позиція рядка на дисплеї, де буде відображатись значення елемента.
- `uint8_t colPos`: Позиція стовпця на дисплеї, де буде відображатись значення елемента.
- `uint16_t blinkTicks`: Інтервал між морганням значення елемента в тактах. Якщо `blinkTicks` дорівнює 0, моргання буде вимкнено.

### `pAction`

`pAction` - це тип вказівника на функцію, яка використовується для обробки дій користувача в меню. Клас містить наступні поля для керування діями користувача:
- `pAction enterF`: Функція, яка викликається при натисканні клавіші "Enter".
- `pAction escF`: Функція, яка викликається при натисканні клавіші "Esc".
- `pAction leftF`: Функція, яка викликається при натисканні клавіші "Left".
- `pAction rightF`: Функція, яка викликається при натисканні клавіші "Right".

## Методи класу

### `MenuHD44780::MenuHD44780()`

Конструктор за замовчуванням класу. Не приймає аргументів і ініціалізує об'єкт класу з порожніми значеннями.

### `MenuHD44780::MenuHD44780(void (*enterF)(), void (*escF)(), void (*leftF)(), void (*rightF)())`

Конструктор з параметрами дозволяє передати функції обробки (`enterF`, `escF`, `leftF`, `rightF`) як аргументи під час створення об'єкту `MenuHD44780`. Це дозволяє зручно визначити обробку дій користувача без необхідності визначати окремі функції. Рекомендується використовувати лямбда-функції для оголошення обробників натискань кнопок, оскільки це дозволяє зберегти визначення функцій безпосередньо в місці їх використання, що полегшує читання та розуміння коду.

### `void MenuHD44780::setMenuPtr(MenuHD44780 *menuptr)`

Статичний метод `setMenuPtr` встановлює вказівник `menuPtr` на об'єкт класу. Цей вказівник використовується для доступу до даних та методів класу у статичних методах. Використовується для зміни вказівника на меню при обробці натискань кнопок.

### `MenuHD44780 *MenuHD44780::getMenuPtr()`

Статичний метод `getMenuPtr` повертає вказівник на об'єкт класу, на який вказує `menuPtr`. Це д

озволяє здійснити доступ до даних та методів об'єкта з інших місць програми.

### `void MenuHD44780::createItem(const char* name, Item item)`

Метод `createItem` додає новий елемент меню до `items`. Він приймає `name` - назву елемента та `item` - структуру `Item`, що містить параметри елемента. Якщо елемент з таким ім'ям вже існує, він буде замінений новим.

### `void MenuHD44780::renewAll()`

Метод `renewAll` викликається для оновлення вмісту дисплея. Він перераховує всі елементи `items`, форматує їх значення згідно типів та форматів, вказаних у структурах `Item`, і зберігає результат у внутрішньому масиві `displayField`. Також він здійснює моргання значеннями, якщо це передбачено параметром `blinkTicks` у структурах `Item`.

### `char *MenuHD44780::getDisplayField(uint8_t row)`

Метод `getDisplayField` повертає вказівник на рядок `displayField` з вказаного рядка дисплея (`row`). Це дозволяє виводити вміст дисплея у зовнішній код.

### Статичні методи для обробки дій користувача

Клас містить статичні методи, які викликають функції обробки `enterF`, `escF`, `leftF`, `rightF` у відповідь на дії користувача. Ці методи оновлюють вміст дисплея після кожного виклику. Якщо функції обробки не встановлені, вони не викликаються.

## Висновок

Клас `MenuHD44780` забезпечує зручний інтерфейс для створення та керування меню на дисплеї з контролером HD44780. Він дозволяє легко додавати елементи меню, зчитувати та відображати значення змінних на дисплеї та обробляти дії користувача. Завдяки його функціональності, взаємодія з користувачем стає простою та зрозумілою.