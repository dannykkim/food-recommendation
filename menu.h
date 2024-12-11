#ifndef MENU_H
#define MENU_H

typedef struct {
    const char* name;
    const char* traits; // 음식의 특성 키워드
} MenuItem;

typedef struct {
    const char* category; // 음식 종류
    const MenuItem* items;
    int count;
} Menu;

// 메뉴 아이템 데이터 선언
extern const Menu menus[];

#endif // MENU_H