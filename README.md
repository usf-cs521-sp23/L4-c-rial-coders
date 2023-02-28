# Lab 4: Wordle

The lab is to create command line program that emulates wordle game, the program has following features:
1. Keep record of user name
2. Generate a random 5 letter words in the word list
3. Take in user's guess
4. Display letters in user's guess with different colors
    * Green means the letter is in the right position of the word
    * Yellow means the letter is in the word, but is not in the right position
    * Red means the letter is not in the word
5. User have 6 chances to guess the word
6. If 6 chances are used up, user will be asked if they want to play again, the program will repeat step 2 to 5
7. If the user decides not to continue playing, win/loss stats will be written into stats file

## Building

Run `make`

## Running + Example Usage

```
./wordle
Enter your name: John
You have 6 attempt(s) left
Enter your guess: track
You're a winner, John!
```


