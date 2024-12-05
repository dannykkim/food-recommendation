#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include "menu.h" // 메뉴 데이터를 위한 헤더
#include "menu.c" // 메뉴 데이터 포함

// 사용자 입력에서 키워드를 추출하는 함수
void extract_keywords(const char* input, char* keyword, size_t keyword_size) {
    const char* delimiters = " ,.!?"; // 단어 구분 문자
    char buffer[100];
    strncpy(buffer, input, sizeof(buffer) - 1);
    buffer[sizeof(buffer) - 1] = '\0';

    char* token = strtok(buffer, delimiters);
    while (token != NULL) {
        if (strcmp(token, "거") != 0 && strcmp(token, "땡겨") != 0 && strcmp(token, "추천") != 0) {
            strncpy(keyword, token, keyword_size - 1);
            keyword[keyword_size - 1] = '\0';
            return;
        }
        token = strtok(NULL, delimiters);
    }
    keyword[0] = '\0'; // 키워드를 찾지 못한 경우
}

// 메뉴를 추천하는 함수
void recommend_menu(const char* user_input, int* found, char* last_category) {
    srand((unsigned int)time(NULL));
    char keyword[50] = "";
    extract_keywords(user_input, keyword, sizeof(keyword));

    if (strlen(keyword) == 0) {
        printf("추천할 메뉴를 찾지 못했습니다. 키워드 예시: 매운, 바삭한, 담백한 등을 입력해보세요.\n");
        *found = 0;
        return;
    }

    for (int i = 0; i < sizeof(menus) / sizeof(menus[0]); i++) {
        for (int j = 0; j < menus[i].count; j++) {
            if (strstr(menus[i].items[j].traits, keyword)) {
                printf("추천 메뉴: [%s] %s (특징: %s)\n", menus[i].category, menus[i].items[j].name, menus[i].items[j].traits);
                *found = 1;
                strncpy(last_category, menus[i].category, 50); // 마지막 추천 카테고리 저장
                return;
            }
        }
    }

    printf("추천할 메뉴를 찾지 못했습니다. 키워드 예시: 매운, 바삭한, 담백한 등을 입력해보세요.\n");
    *found = 0;
}

// 같은 카테고리 내에서 다른 메뉴를 추천하는 함수
void recommend_another(const char* category) {
    srand((unsigned int)time(NULL));
    for (int i = 0; i < sizeof(menus) / sizeof(menus[0]); i++) {
        if (strcmp(menus[i].category, category) == 0) {
            int random_index = rand() % menus[i].count;
            printf("다른 추천 메뉴: [%s] %s (특징: %s)\n", category, menus[i].items[random_index].name, menus[i].items[random_index].traits);
            return;
        }
    }
    printf("해당 카테고리에서 더 이상 추천할 메뉴가 없습니다.\n");
}

int main() {
    char user_input[100];
    char continue_response[10];
    char last_category[50] = ""; // 마지막 추천된 카테고리 저장
    int recommending = 1;

    printf("메뉴 추천 프로그램입니다.\n");
    printf("원하는 음식을 자유롭게 묘사하세요! 예: 매운 게 땡겨, 바삭한 음식 추천\n");

    while (recommending) {
        printf("입력: ");
        if (fgets(user_input, sizeof(user_input), stdin) == NULL) {
            printf("입력을 받는 중 오류가 발생했습니다. 다시 시도해주세요.\n");
            continue;
        }
        user_input[strcspn(user_input, "\n")] = 0; // 개행 문자 제거

        int found = 0;
        recommend_menu(user_input, &found, last_category); // 마지막 카테고리를 업데이트하도록 변경

        if (found) {
            printf("다른 메뉴를 추천해드릴까요? (네/아니요/다른)\n");
            printf("응답: ");
            if (fgets(continue_response, sizeof(continue_response), stdin) == NULL) {
                printf("응답을 받는 중 오류가 발생했습니다. 다시 시도해주세요.\n");
                continue;
            }
            continue_response[strcspn(continue_response, "\n")] = 0; // 개행 문자 제거

            if (strcmp(continue_response, "아니요") == 0) {
                recommending = 0;
            } else if (strcmp(continue_response, "다른") == 0) {
                recommend_another(last_category); // 같은 카테고리 내 다른 메뉴 추천
            }
        }
    }

    printf("프로그램을 종료합니다. 좋은 하루 되세요!\n");
    return 0;
}
