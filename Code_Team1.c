#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX_LEN 1000

int main(void) {
    char text[MAX_LEN];

    printf("Enter a word or sentence to analyze: ");
    if (fgets(text, sizeof(text), stdin) == NULL) {
        printf("Error reading input.\n");
        return 1;
    }

    size_t len = strlen(text);
    if (len > 0 && text[len - 1] == '\n') {
        text[len - 1] = '\0';
        len--;
    }

    int total_chars = (int)len;
    int chars_no_spaces = 0;
    int words = 0;
    int vowels = 0;
    int consonants = 0;

    int curr_word_len = 0;
    int max_word_len = 0;
    char longest_word[MAX_LEN] = "";
    char current_word[MAX_LEN] = "";

    for (int i = 0; i <= len; i++) {
        unsigned char ch = (unsigned char)text[i];

        if (i < len) {
            if (!isspace(ch)) {
                chars_no_spaces++;
            }

            if (isalpha(ch)) {
                char lower_ch = (char)tolower(ch);
                if (lower_ch == 'a' || lower_ch == 'e' || lower_ch == 'i' || 
                    lower_ch == 'o' || lower_ch == 'u') {
                    vowels++;
                } else {
                    consonants++;
                }
            }
        }

        
        if (i < len && isalnum(ch)) {
            current_word[curr_word_len++] = (char)ch;
        } else {
            if (curr_word_len > 0) {
                words++;
                if (curr_word_len > max_word_len) {
                    max_word_len = curr_word_len;
                    current_word[curr_word_len] = '\0';
                    strcpy(longest_word, current_word);
                }
                curr_word_len = 0;
            }
        }
    }

    if (total_chars == 0 || chars_no_spaces == 0) {
        printf("\nError: Input is empty or contains only spaces. Please enter valid text.\n");
        return 0;
    }

   
    int is_palindrome = 0;
    int left = 0;
    int right = total_chars - 1;

    while (left <= right) {
        if (!isalnum((unsigned char)text[left])) {
            left++;
        } else if (!isalnum((unsigned char)text[right])) {
            right--;
        } else {
            is_palindrome = 1;
            if (tolower((unsigned char)text[left]) != tolower((unsigned char)text[right])) {
                is_palindrome = 0;
                break;
            }
            left++;
            right--;
        }
    }

    printf("\n--- Text Statistics Report ---\n");
    printf("Total Characters (with spaces)    : %d\n", total_chars);
    printf("Total Characters (without spaces) : %d\n", chars_no_spaces);
    printf("Total Words                       : %d\n", words);
    printf("Vowels                            : %d\n", vowels);
    printf("Consonants                        : %d\n", consonants);
    printf("Longest Word                      : %s\n", max_word_len > 0 ? longest_word : "N/A");
    printf("Is Palindrome?                    : %s\n", is_palindrome ? "Yes" : "No");
    printf("------------------------------\n");

    return 0;
}
