#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <ctype.h> // 소문자 변환용

void recommend_menu(const char* category) {
    const char* korean[] = { "비빔밥", "김치찌개", "불고기", "제육볶음", "된장찌개", "삼겹살" };
    const char* chinese[] = { "짜장면", "짬뽕", "탕수육", "마파두부", "양장피" };
    const char* japanese[] = { "초밥", "라멘", "돈부리", "우동", "가라아게" };
    const char* western[] = { "스테이크", "파스타", "리조또", "햄버거", "피자" };
    const char* school_food[] = { "떡볶이", "김밥", "순대", "튀김", "라면" };

    srand((unsigned int)time(NULL));
    int random_index = rand() % 5;

    if (strcmp(category, "한식") == 0) {
        printf("추천 메뉴: %s\n", korean[random_index]);
    }
    else if (strcmp(category, "중식") == 0) {
        printf("추천 메뉴: %s\n", chinese[random_index]);
    }
    else if (strcmp(category, "일식") == 0) {
        printf("추천 메뉴: %s\n", japanese[random_index]);
    }
    else if (strcmp(category, "양식") == 0) {
        printf("추천 메뉴: %s\n", western[random_index]);
    }
    else if (strcmp(category, "분식") == 0) { 
        printf("추천 메뉴: %s\n", school_food[random_index]);
    }
    else { 
        printf("잘못된 입력입니다. 한식, 중식, 일식, 양식, 분식 중에서 선택해주세요.\n");
    }
}

int main() {
    char category[10];
    int valid = 0;

    printf("메뉴 추천 프로그램입니다\n");
    printf("원하시는 음식 종류를 선택하세요: 한식, 중식, 일식, 양식, 분식\n");

    while (!valid) {
        printf("음식 종류: ");
        scanf_s("%9s", category, (unsigned)_countof(category));

        // 입력을 소문자로 변환
        for (int i = 0; category[i]; i++) {
            category[i] = tolower(category[i]);
        }

        if (strcmp(category, "한식") == 0 || strcmp(category, "중식") == 0 ||
            strcmp(category, "일식") == 0 || strcmp(category, "양식") == 0 ||
            strcmp(category, "분식") == 0) {
            valid = 1;
        }
        else {
            printf("잘못된 입력입니다. 다시 시도하세요.\n");
        }
    }

    recommend_menu(category);

    return 0;
}