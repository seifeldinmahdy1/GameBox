#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>
#include <vector>

using namespace std;

class HangmanGame {
private:
    vector<string> words = {"apple", "university", "plane", "orange", "car"};
    string chosenWord;
    string hiddenWord;
    int maxGuesses = 7;
    int guessesLeft = maxGuesses;

public:
    HangmanGame() {
        srand(time(nullptr));
        chosenWord = words[rand() % words.size()];
        hiddenWord = string(chosenWord.length(), '_');
    }

    void play() {
        cout << "Welcome to Hangman Game !" << endl;
        cout << "The word has " << chosenWord.length() << " letters." << endl;
        cout << hiddenWord << endl << endl;

        while (guessesLeft > 0 && hiddenWord != chosenWord) {
            char guess = getGuess();
            if (checkGuess(guess)) {
                cout << "Good guess!" << endl << endl;
                hiddenWord = getHiddenWord();
            } else {
                cout << "Sorry, that's not in the word." << endl << endl;
                guessesLeft--;
                displayHangman();
            }
            cout << hiddenWord << endl << endl;
        }

        if (hiddenWord == chosenWord) {
            cout << "Congratulations, you guessed the word!" << endl;
        } else {
            cout << "Sorry, you ran out of guesses. The word was " << chosenWord << "." << endl;
        }
    }

private:
    char getGuess() {
        char guess;
        cout << "You have " << guessesLeft << " guesses left." << endl;  //tell the person no. of gusses left
        cout << "Enter a letter: ";       // tells the person to enter the letter
        cin >> guess;                   // enter the letter
        return guess;
    }

// checks if the guess is correct or not
    bool checkGuess(char guess) {
        bool correct = false;
        for (int i = 0; i < chosenWord.length(); i++) {
            if (chosenWord[i] == guess) {
                hiddenWord[i] = guess;
                correct = true;
            }
        }
        return correct;
    }

    string getHiddenWord() {
        string hidden = "";
        for (int i = 0; i < chosenWord.length(); i++) {
            hidden += hiddenWord[i];
        }
        return hidden;
    }
// draws the hang man every time the letter is wrong
    void displayHangman() {
        switch (guessesLeft) {
            case 5:
                cout << "  _______" << endl;
                cout << " |/" << endl;
                cout << " |" << endl;
                cout << " |" << endl;
                cout << " |" << endl;
                cout << " |" << endl;
                cout << "_|___" << endl;
                break;
            case 4:
                cout << "  _______" << endl;
                cout << " |/      |" << endl;
                cout << " |" << endl;
                cout << " |" << endl;
                cout << " |" << endl;
                cout << " |" << endl;
                cout << "_|___" << endl;
                break;
            case 3:
                cout << "  _______" << endl;
                cout << " |/      |" << endl;
                cout << " |      (_)" << endl;
                cout << " |" << endl;
                cout << " |" << endl;
                cout << " |" << endl;
                cout << "_|___" << endl;
                break;
            case 2:
                cout << "  _______" << endl;
                cout << " |/      |" << endl;
                cout << " |     /|\\" << endl;
                cout << " |      |" << endl;
                cout << " |" << endl;
                cout << "_|___" << endl;
                break;
            case 1:
                cout << "  _______" << endl;
                cout << " |/      |" << endl;
                cout << " |      (_)" << endl;
                cout << " |     /|\\" << endl;
                cout << " |      |" << endl;
                cout << " |" << endl;
                cout << "_|___" << endl;
                break;
            case 0:
                cout << "  _______" << endl;
                cout << " |/      |" << endl;
                cout << " |      (_)" << endl;
                cout << " |     /|\\" << endl;
                cout << " |      |" << endl;
                cout << " |     / \\" << endl;
                cout << "_|___" << endl;
                break;
            default:
                break;
        }
    }
};
void StartHangman() {
    HangmanGame game;
    game.play();
}