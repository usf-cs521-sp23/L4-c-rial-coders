#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>

/*
    1. Find out who is playing the game
    2. Open a text file with words to use (maybe in /usr/share/dict ?)
        - Make a word list from those words (only 5 letters, no special chars)
    3. Pick one word randomly
    4. Read guesses on standard input (stdin) -- but only give them 6 chances
        - Check if it's actually a valid word, no uppercase, punctuation
        - Check if the letter is in the right spot, or at least in the word
    5. Let user know which letters have already been used
        - Track which letters were wrong
    6. Have some way of showing what was right/wrong, how many times guessed, how many left
    7. Either print that they win or lose (with personalization, e.g., "You are terrible Matthew")
    8. Ask them if they want to play again
*/

int generate_wordlist()
{
    // 1. Find out who is playing the game
    // 2. Open a text file with words to use (maybe in /usr/share/dict ?)
    //    - Make a word list from those words (only 5 letters, no special chars)
    //    - Count the number of words in the word file

    FILE *file = fopen("/usr/share/dict/words", "r");
    if (file == NULL) {
        perror("fopen");
    }

    FILE *file1 = fopen("./words.txt", "w");
    if (file1 == NULL) {
        perror("fopen");
    }

    char line[500];
    int num_of_words = 0;
    while (fgets(line, 500, file) != NULL) {
        if (strlen(line) == 6 && strstr(line, "'") == NULL && strstr(line, "é") == NULL) {
            fputs(line, file1);
            num_of_words++;
        }
    }
    fclose(file);
    fclose(file1);
    return num_of_words;
}

char* generate_new_word(int num_of_words) 
{
    srand(time(NULL));
    // 3. Pick one word randomly
    //      - Generate a random number between 1 and the number of lines in words.txt
    //      - Pick the word based on the random number that is generated from last step
    int r = rand() % (num_of_words + 1);
    printf("random number is %d\n", r);

    FILE *file3 = fopen("./words.txt", "r");
    if (file3 == NULL) {
        perror("fopen");
    }

    char line[6];
    char *word = (char*) malloc(6);
    while (r > 0) {
        word = fgets(line, 6, file3);
        r--;
    }
    printf("random word is %s\n", word);
    
    fclose(file3);

    return word;
}

int main(void) 
{
    
    bool is_play_again = true;
    int num_of_chances = 6;

    int num_of_words = generate_wordlist();
    // printf("number of words is %d\n", num_of_words);

    char *target = generate_new_word(num_of_words);
    printf("target is %s\n", target);

    // 4. Read guesses on standard input (stdin) -- but only give them 6 chances
    //    - Check if it's actually a valid word, no uppercase, punctuation
    //    - Check if the letter is in the right spot, or at least in the word
    while (is_play_again && num_of_chances > 0){
        char guess[100];
        char is_play[2];
        printf("Enter your guess: ");
        scanf("%s", guess);

        if (strlen(guess) > 5) {
            printf("Word exeeds 5 character limits.\n");
            continue;
        }

        if (strlen(guess) < 5) {
            printf("Word is less than 5 characters. \n");
            continue;
        }

        // 5. Let user know which letters have already been used
        //    - Track which letters were wrong
        printf("                : ");
        for (int j = 0; j< 5; j++) {
            if (target[j] == guess[j]) {
                printf("o");
            } else if (strchr(target, guess[j]) == NULL) {
                printf("a");
            } else {
                printf("x");
            }
            if (j == 4) {
                printf("\n");
            }
        }

        // 6. Have some way of showing what was right/wrong, how many times guessed, how many left
        num_of_chances--;
        if (strcmp(target, guess) == 0) {
            printf("YOU WIN!\n");
            printf("Do you wanna play again? (y/n)");
            scanf("%s", is_play);
            if (strcmp(is_play, "y") == 0) {
                is_play_again = true;
                num_of_chances = 6;
            } else {
                is_play_again= false;
            }
        } else {
            if (num_of_chances == 0) {
                printf("You have no chance left, do you wanna play again? (y/n)");
                scanf("%s", is_play);
                if (strcmp(is_play, "y") == 0) {
                    is_play_again = true;
                } else {
                    is_play_again = false;
                }
            } else {
                printf("You have %d chances left\n", num_of_chances);
            }
        }        
    }
    free(target);
}