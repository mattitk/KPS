#include "includes.h"
#include "bot_interface.h"
#include "students/MY_BOT_kauppila.h"
#include "students/MY_BOT_kauppila2.h"

#define NOF_BOTS 2
#define NOF_TOURS 10
// #define WAIT_FOR_KEYPRESS

Bot* create_bot(int);				// Create a new bot object.
void err_exit(const std::string&);	// Exit program with an error message.
int get_throw_score(int, int);		// Get score for a single throw.


/*
	Rock-Paper-Scissors tournament.
*/
int main()
{
	// Initialize RNG, in case that some bots need random numbers. 
	// This should NOT be done again in bots' code.
	srand((unsigned)time(0));

	// Several tournaments...
	double tour_score[NOF_BOTS] = {};
	for (int t = 0; t < NOF_TOURS; ++t)
	{

		int match_no = 0;
		for (int i = 0; i < (NOF_BOTS - 1); ++i)
			for (int j = i + 1; j < NOF_BOTS; ++j)
			{
			// Start a new match.
			match_no += 1;
			Bot* blue = create_bot(i);
			Bot* red = create_bot(j);
			printf
				(
				"MATCH %3d : %-30s vs. %-30s ",
				match_no,
				blue->get_name().c_str(),
				red->get_name().c_str()
				);

#ifdef WAIT_FOR_KEYPRESS
			//getch();
#endif

			// Play the rounds.
			signed int blue_score = 0;
			signed int red_score = 0;
			for (int r = 0; r < ROUNDS; ++r)
			{
				int blue_throw = blue->get_throw(r);
				int red_throw = red->get_throw(r);
				if (blue_throw < 0 || blue_throw > 2 || red_throw < 0 || red_throw > 2)
					printf(" REALLY?!\n");

				blue_score += get_throw_score(blue_throw, red_throw);
				red_score += get_throw_score(red_throw, blue_throw);
				blue->own_throw[r] = blue_throw;
				blue->opp_throw[r] = red_throw;
				red->own_throw[r] = red_throw;
				red->opp_throw[r] = blue_throw;
			}

			// Decide the winner and update tournament scores.
			std::string winner;
			if (blue_score > red_score)
			{
				winner = "won by " + blue->get_name();/*
				if(blue->am_i_learning())
					blue->set_value(blue_score - red_score);
				else if(red->am_i_learning())
					red->set_value(red_score - blue_score);
						*/
				tour_score[i] += 1.0;
			}
			else if (red_score > blue_score)
			{
				winner = "won by " + red->get_name();
			/*	if(red->am_i_learning())
					red->set_value(red_score - blue_score);
				else if(blue->am_i_learning())
					blue->set_value(blue_score - red_score);*/
				tour_score[j] += 1.0;
			}
			else
			{
				winner = "draw ";
				tour_score[i] += 0.5;
				tour_score[j] += 0.5;
			}
			printf("%-35s (%4d - %4d)\n", winner.c_str(), blue_score, red_score);

			// Get rid of the competitors.
			delete blue;
			delete red;
			}
	}

	// Announce tournament results.
	printf("\n=====================================================================================================================\n");
	printf("FINAL SCORES\n");
	printf("=====================================================================================================================\n");
	std::multimap<double, std::string> scores;
	for (int i = 0; i < NOF_BOTS; ++i)
	{
		Bot* b = create_bot(i);
		scores.insert(std::pair<double, std::string>(-tour_score[i], b->get_name()));
		delete b;
	}
	for (auto s : scores)
	{
		printf("%-30s : %.2f / %d (%.2f)\n", s.second.c_str(), -s.first, (NOF_BOTS - 1) * NOF_TOURS, -s.first / ((NOF_BOTS - 1) * NOF_TOURS));
	}

	return 0;
}


Bot* create_bot(int id)
{
	switch (id)
	{
	case 0	: return new My_bot_kauppila;
	case 1 : return new My_bot_kauppila2;

	default	: return 0;
	}
}


void err_exit(const std::string& msg)
{
	printf("%s\n", msg.c_str());
	exit(1);
}


int get_throw_score(int own_throw, int opp_throw)
{
	// Wins.
	if (own_throw == ROCK && opp_throw == SCISSORS)
		return 1;
	if (own_throw == PAPER && opp_throw == ROCK)
		return 1;
	if (own_throw == SCISSORS && opp_throw == PAPER)
		return 1;

	// A loss or a tie.
	return 0;
}
