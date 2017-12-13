// Authors: Deitel & Deitel - C How to Program

#include"header.h"

int main(void)
{
	srand((unsigned)time(NULL));

	const char *suit[4] = { "Hearts", "Diamonds", "Clubs", "Spades" };
	const char *face[13] = { "Ace", "Deuce", "Three", "Four", "Five", "Six", "Seven", "Eight",
		"Nine", "Ten", "Jack", "Queen", "King" };
	int deck[4][13] = { 0 };
	int turn = 0, playing = 0;

	Deck cards;
	cards.current_card = 0;
	Hand player, dealer;
	player.score = 0;
	player.points = 0;
	dealer.score = 0;
	dealer.points = 0;
	dealer.straight = 0;

	welcome_screen();
	shuffle(deck);
	deal(deck, face, suit, &cards);
	initalize_hand(&cards, &player, &dealer, face, suit);

	while (turn < 10)
	{
		printf("Round %d\n", turn + 1);
		if (playing == 0)
		{
			printf("PLAYER\n");
			current_cards(&player, face, suit);
			check_hand(&cards, &player, face, suit);
			changing_cards(&player, &cards, deck, face, suit, &dealer);
			current_cards(&player, face, suit);
			check_hand(&cards, &player, face, suit);
			playing++;
			printf("Press enter to contine\n");
			getch();
			system("cls");
		}
		if (playing == 1)
		{
			printf("DEALER\n");
			//current_cards(&dealer, face, suit);
			check_hand(&cards, &dealer, face, suit);
			dealers_choices(&cards, &dealer, &player, face, suit, deck);
			current_cards(&dealer, face, suit);
			check_hand(&cards, &dealer, face, suit);
			playing--;
			printf("Press enter to contine\n");
			getch();
			system("cls");
		}
		which_hand_is_better(&player, &dealer);
		get_new_hand(&cards, &player, &dealer, face, suit, deck);

		printf("Press enter to contine\n");
		getch();
		system("cls");

		turn++;
	}
	winner(&player, &dealer);

	return 0;
}
