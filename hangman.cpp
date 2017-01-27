//Steven Zilberberg
// 1/27/16
//Self challenge
//Started: 11:51PM
//Completed: 12:51AM
#include <iostream>
#include <string.h>
using namespace std;

#define MAX_GUESSES 6
#define NUM_LETTERS 26

//Draws the appropriate body parts based on number of guesses done from max
void drawMan(int x, int y)
{
  printf("          _________________\n");
  printf("            |       %s    \n", x > 0 ? "|" : " ");
  printf("            |       %s    \n", x > 0 ? "O" : " ");
  printf("            |       %s    \n", x > 1 ? "|" : " ");
  printf("            |      %s%s%s    \n", (x > 2 ? "/" : " "), (x > 1 ? "|" : " "), (x > 3 ? "\\" : " "));
  printf("            |     %s %s %s   \n", (x > 2 ? "/" : " "), (x > 1 ? "|" : " "), (x > 3 ? "\\" : " "));
  printf("            |       %s      \n", x > 1 ? "|" : " ");
  printf("            |      %s %s    \n", (x > 4 ? "/" : " "), (x > 5 ? "\\" : " "));
  printf("            |     %s   %s   \n", (x > 4 ? "/" : " "), (x > 5 ? "\\" : " "));
  printf("          _________________\n");
  printf("          Wrong Guesses: %d of %d tries\n", x, y);
}

//Checks the letter against the letters array for if it exists.
//If letter exists in array, return false. Otherwise add it to the array and return true
bool checkLetters(char * letters, int & index, const char letter)
{
  for(int c = 0; c < index; c++)
  {
    if(letter == letters[c])
      return false;
  }
  letters[index++] = letter;
  return true;
}

//Displays the letters already used
void displayLetters(const char * letters)
{
  cout << "Used Letters: ";
  for(int c = 0; c < NUM_LETTERS; c++)
  {
    if(letters[c] != ' ')
      cout << letters[c] << ", ";
  }
  cout << endl;
}

//Displays the current guess character array
void displayGuess(const char * guess, int len)
{
  cout << "Current Guess:";
  for(int c = 0; c < len; c++)
  {
    cout << guess[c] << "  ";
  }
  cout << endl;
}

//Looks at the letter guessed and finds all the matches for the letter within the original word
//Returns if a successful guess was made
bool checkGuess(const char * word, char * guess, int len, const char letter)
{
  bool hasLetter = false;
  for(int c = 0; c < len; c++)
  {
    if(word[c] == letter)
    {
      guess[c] = letter;
      hasLetter = true;
    }
  }
  return hasLetter;
}

int main(int argc, char ** argv)
{
  //Evaluate Args
  char * word = NULL;
  if(argc != 2)
  {
    printf("Enter a word as argument!\n");
    exit(1);
  }

  //Set up
  char letter = ' ';
  int letterIndex = 0;
  char letters[NUM_LETTERS];
  for(int c = 0; c < NUM_LETTERS; c++)
  {
    letters[c] = ' ';
  }
  int numGuesses = 0;
  word = argv[1];
  int len = string(word).length() + 1;
  char guess[len];
  memset(guess, '_', len - 1);

  //Start main game loop
  while(strstr(guess, "_") != NULL && numGuesses < MAX_GUESSES)
  {
    //Draw relevant information
    drawMan(numGuesses, MAX_GUESSES);
    displayGuess(guess, len);
    displayLetters(letters);

    //Indefinitely ask for input
    string input = "";
    while(1)
    {

      //Makes sure the input has a length of 1
      do
      {
        cout << "Make a guess: ";
        cin >> input;
      }while(input.length() != 1);

      //Create space in the console
      for(int c = 0; c < 10; c++)
      {
        cout << endl << endl << endl;
      }

      //Assign the letter to helper variable
      letter = input[0];

      //If this isn't in letters, break from infinite loop
      if(checkLetters(letters, letterIndex, letter))
      {
        break;
      }
      else
      {
        cout << "The letter \'" << letter << "\' has been used!" << endl;
      }
    }

    //Check the guessed letter
    if(checkGuess(word, guess, len, letter))
    {
      cout << "Correct! There is a " << letter << endl;
    }
    else
    {
      //If incorrect increment the number of guesses
      numGuesses++; 
      if(numGuesses >= MAX_GUESSES)
      {
        //Break the main game loop to prevent the next wrong message to show on last wrong guess
        break;
      }
      cout << "Wrong. \'" << letter << "\' doesn exist." << endl;
    }
  }

    //Game ended, Display man and guess one last time
    drawMan(numGuesses, MAX_GUESSES);
    displayGuess(guess, len);
    if(strstr(guess, "_") == NULL)
    {
      cout << "          WIN!" << endl;
    }
    else
    {
      cout << "          GAME OVER" << endl;
    }
}