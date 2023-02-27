#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h> //included for toLower function

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
    FILE *dict = fopen("/usr/share/dict/words", "r");
    if (dict == NULL) {
        perror("fopen");
    }

    FILE *words = fopen("./words.txt", "w");
    if (words == NULL) {
        perror("fopen");
    }

    char line[500];
    int num_of_words = 0;
    while (fgets(line, 500, dict) != NULL) {
        if (strlen(line) == 6 && strstr(line, "'") == 0 && strstr(line, "é") == NULL) {
            fputs(line, words);
            num_of_words++;
        }
    }
    fclose(dict);
    fclose(words);
    return num_of_words;
}

char* generate_new_word(int num_of_words) 
{
    srand(time(NULL));
    int r = rand() % (num_of_words + 1);
    printf("random number is %d\n", r);

    FILE *file = fopen("./words.txt", "r");
    if (file == NULL) {
        perror("fopen");
    }

    char line[7];
    char *word = NULL;

    for (int i = r; i > 0; i--) {
        fgets(line, sizeof(line), file);
    }
    fclose(file);

    //replace newline char with null char
    line[strcspn(line, "\n")] = '\0';
    word = malloc(strlen(line) + 1);
    strcpy(word, line);
    word[0] = tolower(word[0]);

    printf("random word is %s\n", word);
    return word;
}



int main(void) 
{
    int num_of_words = generate_wordlist();
    
    char name[20];
    printf("--- Welcome to Wordle ---\n");
    printf("Enter your name: ");
    scanf("%s", name);
    bool win = false;

    while (true)
    {
        char *target = generate_new_word(num_of_words);
        printf("target is %s\n", target);

        for (int i = 6; i > 0; i--) {
            char guess[100];
            printf("You have %d attempt(s) left.\n", i);
            printf("Enter your guess: ");
            scanf("%s", guess);

            if (strlen(guess) != 5) {
                printf("That is not 5 characters. Please try again.\n");
                i++;
                continue;
            }
            
            printf("                  ");
            for (int j = 0; j < 5; j++) {
                if (target[j] == guess[j]) {
                    printf("o");
                } else if (strchr(target, guess[j]) != NULL) {
                    printf("a");
                } else {
                    printf("x");
                }
            }
            puts("");

            if (strncmp(target, guess, 5) == 0) {
                win = true;
                break;
            }
        }
        if (win) {
            printf("You're a winner, %s!\n", name);
        } else {
            printf("You lose, %s!\n", name);
        }
        char user_input[5];
        printf("%s", "Would you like to play again? (y/n)\n");
        scanf("%s", user_input);
        if (strcmp(user_input, "y")) 
        {
            break;
        }
    }

}