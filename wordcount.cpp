#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

void count_chars(FILE *file, int *char_count) {
    char ch;
    *char_count = 0;
    while ((ch = fgetc(file)) != EOF) {
        (*char_count)++;
    }
}

void count_words(FILE *file, int *word_count) {
    char ch;
    bool in_word = false;
    *word_count = 0;
    while ((ch = fgetc(file)) != EOF) {
        if (ch == ' ' || ch == ',' || ch == '\t' || ch == '\n') {
            if (in_word) {
                (*word_count)++;
                in_word = false;
            }
        } else {
            in_word = true;
        }
    }
    if (in_word) {
        (*word_count)++;
    }
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("Usage: %s [-c|-w] input_file_name\n", argv[0]);
        return 1;
    }

    char *arg_1 = argv[1];
    char *filename = argv[2];

    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("错误地打开文件: %s\n", filename);
        return 1;
    }

    int result;
    if (strcmp(arg_1, "-c") == 0) {
        count_chars(file, &result);
        printf("字符数: %d\n", result);
    } else if (strcmp(arg_1, "-w") == 0) {
        count_words(file, &result);
        printf("单词数: %d\n", result);
    } else {
        printf("Invalid parameter: %s\n", arg_1);
        printf("Usage: %s [-c|-w] input_file_name\n", argv[0]);
        return 1;
    }

    fclose(file);
    return 0;
}
