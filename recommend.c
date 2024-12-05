#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include "menu.h" 
#include "menu.c" 

void extract_keywords(const char* input, char* keyword, size_t keyword_size) {
    const char* delimiters = " ,.!?"; // 단어를 구분하는 문자
    char buffer[100];
    strncpy(buffer, input, sizeof(buffer) - 1); // 안전 복사
    buffer[sizeof(buffer) - 1] = '\0';          // Null-terminate 보장

    char* token = strtok(buffer, delimiters);
    while (token != NULL) {
        if (strcmp(token, "거") != 0 && strcmp(token, "땡겨") != 0) { // 의미 없는 단어 무시
            strncpy(keyword, token, keyword_size - 1); // 안전 복사
            keyword[keyword_size - 1] = '\0';          // Null-terminate 보장
            return;
        }
        token = strtok(NULL, delimiters);
    }
    keyword[0] = '\0'; // 키워드를 찾지 못한 경우
}

// 메뉴 추천
void recommend_menu(const char* user_input, int* found) {
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
                printf("추천 메뉴: [%s] %s\n", menus[i].category, menus[i].items[j].name);
                *found = 1;
                return;
            }
        }
    }

    printf("추천할 메뉴를 찾지 못했습니다. 키워드 예시: 매운, 바삭한, 담백한 등을 입력해보세요.\n");
    *found = 0;
}

int main() {
    char user_input[100];
    char continue_response[10];
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
        recommend_menu(user_input, &found);

        if (found) {
            printf("다른 메뉴를 추천해드릴까요? (네/아니요)\n");
            printf("응답: ");
            if (fgets(continue_response, sizeof(continue_response), stdin) == NULL) {
                printf("응답을 받는 중 오류가 발생했습니다. 다시 시도해주세요.\n");
                continue;
            }
            continue_response[strcspn(continue_response, "\n")] = 0; // 개행 문자 제거

            if (strcmp(continue_response, "아니요") == 0) {
                recommending = 0;
            }
        }
    }

    printf("프로그램을 종료합니다. 좋은 하루 되세요!\n");
    return 0;
}