/*
Solitaire Mini-game
  - 5 rows of cards
  - First card is faced up, the rest are faced down

  - Suits:
    - S: Spades (black)
    - C: Clubs (black)
    - D: Diamonds (red)
    - H: Hearts (red)

  - First input = The row/deck you want to move from
  - Second input = The row/deck you want to move to
  - Example user input:
    - Make your move: "3 4"
      - This means you are moving from row 3 to row 4

  - Target: Get all the cards faced up while alternating between suits/color and placing cards in order
*/

/*
Prompt:
1) g++ LL.cpp LL.h main.cpp
2) ./a.out deck1.txt or ./a.out deck2.txt
3) Card movement ("3 4") until end of game
*/

#include "LL.h"
#include "LL.cpp"
#include <iostream>
#include <fstream>

using namespace std;
struct cardType{
  int face;
  char suit;
  char color;
};

const int PILES = 5;
LL<cardType> piles[PILES];
LL<cardType>::iterator topOfPile[PILES];

int main(int agrc, char *argv[])
{
  ifstream textFile;
  textFile.open(argv[1]);
  
  cardType card;

  for(int i = 0; i < PILES; i++){
    for(int j = -1; j < i; j++){
      textFile >> card.face >> card.suit;
      // Checking the color and setting them to black or red
      if(card.suit == 'S'||card.suit == 'C'){
        card.color = 'b';
      }else
      if(card.suit == 'D'||card.suit == 'H'){
        card.color = 'r';
      }
      piles[i].tailInsert(card);
      topOfPile[i] = piles[i].end();
    }
  }

  // Implementing Rules
  int from = 0;
  int to = 0;
  bool cardsFaceup = false;
  int pileCounter = 0;

  // Display for first round of cards
  for (int i = 0; i < PILES; i++){
    cout << i + 1 << ": ";
    for (auto it = piles[i].begin(); it != topOfPile[i]; it++){
      cout << "__ ";
    }
    // Display the face up cards
    for (auto it = topOfPile[i]; it != nullptr; it++){
      cout << (*it).face << (*it).suit << " ";
    }
    cout << endl;
  }

  // while loop that goes until all the cards in the game are faced up
  while(!cardsFaceup){
    from = 0;
    to = 0;
    // Input from user
    cout << "Make your move: ";
    cin >> from >> to;

    // cout the value since we are reading from an input file
    cout << from << " " << to;
    cout << endl;

    // Setting from and to variables to minus 1 so we are at the correct spot when user input occurs
    from = from - 1;
    to = to - 1;

    // Checking if the movement from is out of range
    if(from < 0 || from > 4){
      cout << "Out of range" << endl;
    }
    // Checking if the movement to is out of range
    else if(to < 0 || to > 4){
      cout << "Out of range" << endl;
    }  
    // Checking if the pile I am moving from is empty
    else if(piles[from].isEmpty()){
      cout << "Cannot move card from empty stack" << endl;
    }
    // Checking if the pile I am moving to is empty
    else if(piles[to].isEmpty()){
      cout << "Cannot move card to an empty stack" << endl;
    }
    // Check if you can move the from value to the to value
    else if((*piles[to].end()).face != (*topOfPile[from]).face+1){
      cout << "Invalid move" << endl;
    }
    // If the suits are not equal, it means you cannot move from the pile to the other pile
    else if((*topOfPile[from]).color == (*(piles[to].end())).color){
      cout << "Invalid move" << endl;
    }
    else{

      /*
      Execute move
      - Moving cards from and to a pile
      - Every time you move a card away from the pile, that pile's iterator will move over 1
      - You are going to do a tail insert when you are moving to a pile
      - Reveal the card in the pile you moved away from
      */

      // Setting iterators to be passed in
      LL<cardType>::iterator fromTopOfPile = topOfPile[from];
      LL<cardType>::iterator fromPile = piles[from].end();
      
      // Remove function so that the card/pile you moved will be taken off and not repeated twice in the game
      piles[from].remove(fromTopOfPile);

      // Tail insert to move the pile from the "from" position to the "to" position
      piles[to].tailInsert(fromTopOfPile,fromPile);

      // Changing the end of the pile to face up when a card/pile of cards moves away from it
      topOfPile[from] = piles[from].end();
    }
    
    // Check if the top of the head of the pile is face up, meaning all the cards are faced up
    for(int i = 0; i < PILES; i++){
      if(piles[i].begin() == topOfPile[i]){
        pileCounter++; // Update counter
      }else{ 
        pileCounter = 0; // Reset counter
      }
      // If all piles in the game have cards that are all faced up
      if(pileCounter == PILES){
        cardsFaceup = true;
      }
    }

    // Display
    for (int i = 0; i < PILES; i++){
      // Display the numbers at the beginning of each row
      cout << i + 1 << ": ";
      // Display the face down cards
      for (auto it = piles[i].begin(); it != topOfPile[i]; it++){
        cout << "__ ";
      }
      // Display the face up cards
      for (auto it = topOfPile[i]; it != nullptr; it++){
        cout << (*it).face << (*it).suit << " ";
      }
      cout << endl;
    }
  }
  return 0;
}