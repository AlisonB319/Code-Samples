/* Programmer: Alison Burgess
Class: CptS, PA 8
Programming Assignment: Poker
Date: 4/14/17
Description: In this game, I created a game of poker. Each player has 5 cards at a time, and can change up to 3 every round.
There are 10 rounds in the game, and then a winner is determined. The game compares each players 5 card deck and determines
who wins the round, or it can end in a draw. Note that the dealer's cards are displayed after it redraws cards, similar to how 
to determine a winner each player would show their cards.
*/

#include<stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct deck
{
	int face[52];
	int suit[52];
	int current_card;
}Deck;
typedef struct hand
{
	int playing_face[5];
	int playing_suit[5];
	int type_of_card[6];
	int score;
	int points;
	int pair[5];
	int two_pair[5];
	int three_of_a_kind[5];
	int four_of_a_kind[5];
	int straight;
}Hand;

void welcome_screen(void);
void shuffle(int wDeck[][13]);
Deck deal(const int wDeck[][13], const char *wFace[], const char *wSuit[], Deck *cards);
Deck initalize_hand(Deck *cards, Hand *hand_player, Hand *hand_dealer, const char *wFace[], const char *wSuit[]);
Deck pairs(Deck *cards, Hand *person, const char *wFace[], const char *wSuit[]);
Deck three_of_a_kind(Deck *cards, Hand *person, const char *wFace[], const char *wSuit[]);
Deck four_of_a_kind(Deck *cards, Hand *person, const char *wFace[], const char *wSuit[]);
Deck straight(Deck *cards, Hand *person, const char *wFace[], const char *wSuit[]);
Deck flush(Deck *cards, Hand *person, const char *wFace[], const char *wSuit[]);
Deck check_hand(Deck *cards, Hand *person, const char *wFace[], const char *wSuit[]);
Deck calculate_hand(Deck *cards, Hand *person, const char *wFace[], const char *wSuit[]);
Hand which_hand_is_better(Hand *player, Hand *dealer);
Deck changing_cards(Hand *player, Deck *cards, const int wDeck[][13], const char *wFace[], const char *wSuit[], Hand *dealer);
Hand current_cards(Hand *person, const char *wFace[], const char *wSuit[]);
Hand dealers_choices(Deck *cards, Hand *dealer, Hand *player, const char *wFace[], const char *wSuit[], const int wDeck[][13]);
Hand winner(Hand *player, Hand *dealer);
Hand get_new_hand(Deck *cards, Hand *hand_player, Hand *hand_dealer, const char *wFace[], const char *wSuit[], int wDeck[][13]);
Deck replenish_deck(const int wDeck[][13], const char *wFace[], const char *wSuit[], Deck *cards, Hand *hand_player, Hand *hand_dealer);








