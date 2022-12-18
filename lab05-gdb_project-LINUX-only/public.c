#include <stdio.h>
#include <stdlib.h>
#include <string.h>

extern void private_init(int *len);
extern void private_array_check(const int *array);
extern void private_copy_init(const char *string, size_t len);
extern void private_copy_check(const char *string);
extern void private_sort_check(const int *array);

void initialize_array();
void copy_string();
void bubble_sort();

#define TEST_ARRAY  0x1
#define TEST_STRING 0x2
#define TEST_SORT   0x4
#define TEST_ALL (TEST_ARRAY | TEST_STRING | TEST_SORT)

/*
 * Main simply calls each of the tests in turn.
 */
int main(int argc, char *argv[]) {
    int numbers[5];
    int len;
    int task = 0;

    for (int i = 1; i < argc; i++) {
        if (!strcmp(argv[i], "--array")) {
            task |= TEST_ARRAY;
        } else if (!strcmp(argv[i], "--string")) {
            task |= TEST_STRING;
        } else if (!strcmp(argv[i], "--sort")) {
            task |= TEST_SORT;
        } else {
            fprintf(stderr, "Unknown option '%s'\n", argv[i]);
            return 1;
        }
    }
    if (task == 0) {
        task = TEST_ALL;
    }

    private_init(&len);

    printf("Starting tests.\n");
    fflush(stdout);

    if (task & TEST_ARRAY) {
        initialize_array(numbers, len);
    }

    if (task & TEST_STRING) {
        copy_string();
    }

    if (task & TEST_SORT) {
        bubble_sort();
    }

    return (0);
}

/*
 * This function allocates and initializes the array numbers[] to
 * contain the digits 1-4 and 0.
 */
void initialize_array(int numbers[], int len) {
    int i;

    for (int i = 0; i < len; i++) {
        numbers[i] = i + 1;
    }
    numbers[i] = 0;

    private_array_check(numbers);
}

/*
 * This function copies a C string into an allocated buffer.
 *
 * You can assume that copy behaves like a character array.
 */
void copy_string() {
    char string[] = "This is a string that I will copy.";
    char *copy;
    int i;

    copy = malloc(strlen(string) + 1);
    private_copy_init(copy, strlen(string) + 1);
    for (i = 0; string[i] != '\0'; i++) {
        copy[i] = string[i];
    }

    printf("Copied string: %s\n", copy);

    private_copy_check(copy);

    free(copy);
}

/*
 * This function takes an unsorted array of integers and
 * bubble sorts it.
 */
void bubble_sort() {
#define ARRAYSIZE 12
    int array[ARRAYSIZE] = { 5, 7, 99, 12, 42, 31, 1, 23, 9, 21, 22, 45 };

    for (int i = ARRAYSIZE - 2; i > 0; i--) {
        for (int j = i; j < ARRAYSIZE - 1; j++) {
            if (array[j] > array[j + 1]) {
                int temp = array[j];
                array[j] = array[j + 1];
                array[j + 1] = temp;
            } else {
                break;
            }
        }
    }

    private_sort_check(array);
}
