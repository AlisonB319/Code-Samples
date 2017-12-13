#include"header.h"


void welcome_screen(void)
/*
The welcome message
*/
{
	printf("Welcome to Poker! You are about to begin a game against the dealer!\n");
	printf("There will be 10 rounds, good luck beating the house\n");
}
void shuffle(int wDeck[][13])
/* deal cards in deck */
{
	int row = 0;    /* row number */
	int column = 0; /*column number */
	int card = 0;   /* card counter */
	int i = 0;

	for (row = 0; row < 4; row++)
	{
		for (column = 0; column < 13; column++)
		{
			wDeck[row][column] = 0;
		}
	}


	/* for each of the 52 cards, choose slot of deck randomly */
	for (card = 1; card <= 52; card++)
	{
		/* choose new random location until unoccupied slot found */
		do
		{
			row = rand() % 4;
			column = rand() % 13;
		} while (wDeck[row][column] != 0);

		/* place card number in chosen slot of deck */
		wDeck[row][column] = card;
	}
}
Deck deal(const int wDeck[][13], const char *wFace[], const char *wSuit[], Deck *cards)
{
	int row = 0;    /* row number */
	int column = 0; /*column number */
	int card = 0;   /* card counter */
	int i = 0, j = 5, k = 10;

	cards->current_card = 0;
	/* deal each of the 52 cards */
	for (card = 1; card <= 52; card++)
	{
		/* loop through rows of wDeck */
		for (row = 0; row <= 3; row++)
		{
			/* loop through columns of wDeck for current row */
			for (column = 0; column <= 12; column++)
			{
				/* if slot contains current card, display card */
				if (wDeck[row][column] == card)
				{
					//printf("%d) %5s of %-8s%c", card, wFace[column], wSuit[row], card % 4 == 0 ? '\n' : '\t');
					cards->face[i] = column;
					cards->suit[i] = row;
					i++;
				}
			}
		}
	}
}
Deck initalize_hand(Deck *cards, Hand *hand_player, Hand *hand_dealer, const char *wFace[], const char *wSuit[])
/*
This deck is to initialize the first 5 cards go to the right hand, either the player or the dealer
*/
{
	int i = 0, j = 0, k = 0;

	for (i = 0; i < 5; i++)
	{
		hand_player->playing_face[i] = cards->face[cards->current_card];
		hand_player->playing_suit[i] = cards->suit[cards->current_card];
		hand_player->type_of_card[i] = 0;
		hand_player->type_of_card[5] = 0;
		cards->current_card++;
	}
	printf("\n");
	for (j = 0; j < 5; j++)
	{
		hand_dealer->playing_face[j] = cards->face[cards->current_card];
		hand_dealer->playing_suit[j] = cards->suit[cards->current_card];
		hand_dealer->type_of_card[j] = 0;
		hand_dealer->type_of_card[5] = 0;
		cards->current_card++;
	}
}
Deck pairs(Deck *cards, Hand *person, const char *wFace[], const char *wSuit[])
/*
This function will check for pair, two pair
*/
{
	int i = 0, j = 0, x = 0, k = 0;

	for (k = 0; k < 5; k++)
	{
		person->pair[k] = 0;
		person->two_pair[k] = 0;
		person->three_of_a_kind[k] = 0;
		person->four_of_a_kind[k] = 0;
	}
	for (i = 0; i < 5; i++)
	{
		for (j = i + 1; j < 5; j++)
		{
			if (person->playing_face[i] == person->playing_face[j])
			{
				x++;
				if (x == 1)
				{
					person->type_of_card[0] = 1;
					person->pair[i] = 1;
					person->pair[j] = 1;
					person->two_pair[i] = 1;
					person->two_pair[j] = 1;
				}
				if (x == 2)
				{
					person->type_of_card[1] = 2;
					person->two_pair[i] = 1;
					person->two_pair[j] = 1;
				}
			}
		}
		if (x == 0)
		{
			//printf("No Pairs\n");
		}
	}
}
Deck three_of_a_kind(Deck *cards, Hand *person, const char *wFace[], const char *wSuit[])
/*
This will check to see if there is a 3 of a kind
*/
{
	int i = 0, j = 0, x = 0;

	if (person->type_of_card[3] != 4) //will not run if there is a 4 of a kind
	{
		for (i = 0; i < 5; i++)
		{
			for (j = i + 1; j < 5; j++)
			{
				if (person->playing_face[i] == person->playing_face[j])
				{
					x++;
					person->three_of_a_kind[i] = 1;
					person->three_of_a_kind[j] = 1;
					if (x == 3)
					{
						person->type_of_card[2] = 3;
					}
				}
			}
		}
	}
}
Deck four_of_a_kind(Deck *cards, Hand *person, const char *wFace[], const char *wSuit[])
/*
This will check to see if there is a 4 of a kind
*/
{
	int i = 0, j = 0, x = 0;

	for (i = 0; i < 5; i++)
	{
		for (j = i + 1; j < 5; j++)
		{
			if (person->playing_face[i] == person->playing_face[j])
			{
				x++;
				person->four_of_a_kind[i] = 1;
				person->four_of_a_kind[j] = 1;

				if (x == 4)
				{
					person->type_of_card[3] = 4;
					goto end_nested_loop;
				}

			}
		}
	}
end_nested_loop:;
}
Deck straight(Deck *cards, Hand *person, const char *wFace[], const char *wSuit[])
/*
This will check to see if there is a straight
*/
{
	if (person->playing_face[0] == person->playing_face[1] &&
		person->playing_face[1] == person->playing_face[2] &&
		person->playing_face[2] == person->playing_face[3] &&
		person->playing_face[3] == person->playing_face[4] &&
		person->playing_face[4] == person->playing_face[0])
	{
		person->type_of_card[4] = 5;
		person->type_of_card[3] = 0;
		person->straight = 1;
	}
}
Deck flush(Deck *cards, Hand *person, const char *wFace[], const char *wSuit[])
/*
This will check to see if there is a flush
*/
{
	if (person->playing_suit[0] == person->playing_suit[1] &&
		person->playing_suit[1] == person->playing_suit[2] &&
		person->playing_suit[2] == person->playing_suit[3] &&
		person->playing_suit[3] == person->playing_suit[0])
	{
		printf("Flush!\n");
		person->type_of_card[5] = 6;
	}
}
Deck check_hand(Deck *cards, Hand *person, const char *wFace[], const char *wSuit[])
/*
This function is so that I do not have to run all ofthe check functions, instead this one will call all of them
*/
{
	pairs(cards, person, wFace, wSuit);
	four_of_a_kind(cards, person, wFace, wSuit);
	three_of_a_kind(cards, person, wFace, wSuit);
	straight(cards, person, wFace, wSuit);
	flush(cards, person, wFace, wSuit);
	calculate_hand(cards, person, wFace, wSuit);
}
Deck calculate_hand(Deck *cards, Hand *person, const char *wFace[], const char *wSuit[])
/*
This evaluates the score based on what the cards are
*/

{
	int i = 0, k = 0;

	//printf("\n");
	if (person->type_of_card[4] == 5)
	{
		person->score = person->type_of_card[4] + person->type_of_card[5];
		printf("Straight!\n");
		goto end_loop_here;
	}
	if (person->type_of_card[3] == 4)
	{
		person->score = person->type_of_card[3] + person->type_of_card[5];
		printf("Four of a kind!\n");
		goto end_loop_here;
	}
	if (person->type_of_card[2] == 3)
	{
		person->score = person->type_of_card[2] + person->type_of_card[5];
		printf("Three of a kind!\n");
		goto end_loop_here;
	}
	if (person->type_of_card[1] == 2)
	{
		person->score = person->type_of_card[1] + person->type_of_card[5];
		printf("2 pairs!\n");
		goto end_loop_here;
	}
	if (person->type_of_card[0] == 1)
	{
		person->score = person->type_of_card[0] + person->type_of_card[5];
		printf("1 pair!\n");
		goto end_loop_here;
	}
	else
	{
		printf("No pairs\n");
	}
end_loop_here:;
}
Hand which_hand_is_better(Hand *player, Hand *dealer)
/*
This function will evaluate which is the better hand
*/
{
	if (player->score > dealer->score)
	{
		printf("Player has a better hand than the dealer\n");
		player->points += 1;
	}
	if (player->score < dealer->score)
	{
		printf("Dealer has a better hand than the player\n");
		dealer->points += 1;
	}
	if (player->score == dealer->score)
	{
		printf("The hands are equal\n");
	}
	player->score = 0;
	dealer->score = 0;
}
Deck changing_cards(Hand *player, Deck *cards, const int wDeck[][13], const char *wFace[], const char *wSuit[], Hand *dealer)
/*
This will let the player change their cards
*/
{
	int change_card = 0, i = 0, card_num = 0, d = 10;
	do
	{
		printf("\nYou may change up to 3 cards!\n");
		printf("How many cards would you like to change: ");
		scanf("%d", &change_card);
	} while (change_card < 0 || change_card > 3);

	if (change_card != 0)
	{
		for (i = 0; i < change_card; i++)
		{
			printf("Please enter the card number that you wish to change: ");
			scanf("%d", &card_num);
			player->playing_face[card_num - 1] = cards->face[cards->current_card];
			player->playing_suit[card_num - 1] = cards->suit[cards->current_card];
			cards->current_card++;
			replenish_deck(wDeck, wFace, wSuit, cards, player, dealer);
			player->type_of_card[i] = 0;
		}
	}
	else
	{
		printf("No cards were changed.\n");
	}
}
Hand current_cards(Hand *person, const char *wFace[], const char *wSuit[])
/*
This function allows for the users cards to be printed out
*/
{
	int i = 0, k = 1;

	for (i = 0; i < 5; i++)
	{
		printf("Card %d) %s of %s\n", k, wFace[person->playing_face[i]], wSuit[person->playing_suit[i]]);
		k++;
	}
}
Hand dealers_choices(Deck *cards, Hand *dealer, Hand *player, const char *wFace[], const char *wSuit[], const int wDeck[][13])
/*
This function will decide what the dealer does during the game
*/
{
	int i = 0, j = 0, k = 0, found = 0, choice = 0, card1 = 0, card2 = 0, card3 = 0,
		sum_pair = 0, sum_twopair = 0, sum_three = 0, sum_four = 0;

	for (i = 0; i <= 5; i++)
	{
		sum_pair += dealer->pair[i];
		sum_twopair += dealer->two_pair[i];
		sum_three += dealer->three_of_a_kind[i];
		sum_four += dealer->four_of_a_kind[i];
	}
	if (dealer->straight == 1)
	{
		printf("The dealer did not change any cards\n");
		cards->current_card++;
		goto end_of_loop;
	}
	//changing 1 card
	if (sum_four == 4) // four of a kind and 2 of a kind
	{
		printf("The computer is replacing 1 card\n");

		for (i = 0; i < 5; i++)
		{
			if (dealer->four_of_a_kind[i] == 0)
			{
				dealer->playing_face[i] = cards->face[cards->current_card];
				dealer->playing_suit[i] = cards->suit[cards->current_card];
			}
		}
		cards->current_card++;
		replenish_deck(wDeck, wFace, wSuit, cards, player, dealer);
		goto end_of_loop;
	}
	//changing 2 cards
	if (sum_three == 4) // 3 of a kind
	{
		printf("The computer is replacing 2 cards\n");

		for (i = 0; i < 5; i++)
		{
			if (dealer->four_of_a_kind[i] == 0)
			{
				dealer->playing_face[i] = cards->face[cards->current_card];
				dealer->playing_suit[i] = cards->suit[cards->current_card];
				cards->current_card++;
				replenish_deck(wDeck, wFace, wSuit, cards, player, dealer);
			}
		}
		goto end_of_loop;
	}
	//	2 pair was taken care of by 4
	// change 3 cards for 1 pair
	if (sum_pair == 2)
	{
		printf("The computer is changing 3 cards\n");
		for (i = 0; i < 5; i++)
		{
			if (dealer->four_of_a_kind[i] == 0)
			{
				dealer->playing_face[i] = cards->face[cards->current_card];
				dealer->playing_suit[i] = cards->suit[cards->current_card];
				cards->current_card++;
				replenish_deck(wDeck, wFace, wSuit, cards, player, dealer);
				k++;
				if (k == 3)
				{
					goto end_of_loop;
				}
			}
		}
	}
	else // if there are no pairs 
	{
		printf("The computer is changing 3 cards\n");
		for (i = 0; i < 3; i++)
		{
			if (dealer->four_of_a_kind[i] == 0)
			{
				dealer->playing_face[i] = cards->face[cards->current_card];
				dealer->playing_suit[i] = cards->suit[cards->current_card];
				cards->current_card++;
				replenish_deck(wDeck, wFace, wSuit, cards, player, dealer);
			}
		}
	}
end_of_loop:;
}
Hand winner(Hand *player, Hand *dealer)
/*
This function will determine the winner of the game
*/
{
	if (player->points > dealer->points)
	{
		printf("The player has beat the dealer! Congradulations!\n");
		printf("Player won %d games, while dealer won %d games\n", player->points, dealer->points);
	}
	if (player->points < dealer->points)
	{
		printf("The dealer has beat the player! Try again next time!\n");
		printf("Player won %d games, while dealer won %d games\n", player->points, dealer->points);
	}
	else
	{
		printf("The game has ended in a draw!");
		printf("Player won %d games, while dealer won %d games\n", player->points, dealer->points);
	}
}
Hand get_new_hand(Deck *cards, Hand *hand_player, Hand *hand_dealer, const char *wFace[], const char *wSuit[], int wDeck[][13])
/*
This functions gives 5 new cards for when it is a new round
*/
{
	int i = 0, k = 0, j = 0;

	for (i = 0; i < 5; i++)
	{
		hand_player->playing_face[i] = cards->face[cards->current_card];
		hand_player->playing_suit[i] = cards->suit[cards->current_card];

		hand_player->type_of_card[i] = 0;
		hand_player->type_of_card[5] = 0;
		cards->current_card++;
		replenish_deck(wDeck, wFace, wSuit, cards, hand_player, hand_dealer);
	}
	for (j = 0; j < 5; j++)
	{
		hand_dealer->playing_face[j] = cards->face[cards->current_card];
		hand_dealer->playing_suit[j] = cards->suit[cards->current_card];

		hand_dealer->type_of_card[j] = 0;
		hand_dealer->type_of_card[5] = 0;
		cards->current_card++;
		replenish_deck(wDeck, wFace, wSuit, cards, hand_player, hand_dealer);
	}
}
Deck replenish_deck(const int wDeck[][13], const char *wFace[], const char *wSuit[], Deck *cards, Hand *hand_player, Hand *hand_dealer)
/*
This function will reshuffle and deal the deck if all 52 cards are used
*/
{
	int i = 0;
	if (cards->current_card == 52)
	{
		cards->current_card == 0;
		for (i = 0; i++; i < 52)
		{
			cards->face[i] = 0;
			cards->suit[i] = 0;
		}
		shuffle(wDeck);
		deal(wDeck, wFace, wSuit, cards);
		initalize_hand(cards, hand_player, hand_dealer, wFace, wSuit);
	}
}
