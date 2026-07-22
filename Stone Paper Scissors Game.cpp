#include <iostream>

using namespace std;

enum enGameChoise { Stone = 1, Paper = 2, Scissor = 3 };

enum enWinner { Player = 1, Computer = 2, Draw = 3 };

struct stRoundInfo
{
	short RoundNumber = 0;
	enGameChoise Player1Choise;
	enGameChoise ComputerChoise;
	enWinner Winner;
	string WinnerName;
};

struct stGameResult
{
	short GameRound = 0;
	short Player1WonTimes = 0;
	short ComputerWonTimes = 0;
	short DrawTimes = 0;
	enWinner Winner;
	string WinnerName = "";

};

short ReadHowManyRounds()
{
	short Round = 1;

	do {
		cout << "How many rounds 1 to 10?\n";
		cin >> Round;

	} while (Round < 1 || Round > 10);
		
	return Round;
}

short RandomNumber(int From, int To) {
	int RandNum = rand() % (To - From + 1) + From;
	return RandNum;
}

enWinner WhoWonTheRound(stRoundInfo RoundInfo)
{
	if (RoundInfo.Player1Choise == RoundInfo.ComputerChoise)
		return enWinner::Draw;

	switch (RoundInfo.Player1Choise) {
	case enGameChoise::Paper:
		if (RoundInfo.ComputerChoise == enGameChoise::Scissor)
			return enWinner::Computer;
	case enGameChoise::Stone:
		if (RoundInfo.ComputerChoise == enGameChoise::Paper)
			return enWinner::Computer;
	case enGameChoise::Scissor:
		if (RoundInfo.ComputerChoise == enGameChoise::Stone)
			return enWinner::Computer;
	}
	return (enWinner)Player;
}

enGameChoise GetComputerChoise()
{
	return 	(enGameChoise)RandomNumber(1, 3);

}

enGameChoise ReadPlayerChoise()
{
	short Player1Choise = 1;
	do {
		cout << ("\nchoose [1]stone , [2]paper, [3]scissor : ");
		cin >> Player1Choise;

	} while (Player1Choise < 1 || Player1Choise > 3);

	return (enGameChoise)Player1Choise;
}

string Tabs(short NumberOfTabs)
{
	string t = " ";

	for (int i = 1;i <= NumberOfTabs;i++)
	{
		cout << "\t";
		cout << t;
	}
	return t;
}

string WinnerName(enWinner Winner)
{
	string arrWinnerName[3] = { "Player1", "Computer", "No Winner (Draw)" };
	return (string)arrWinnerName[Winner - 1];
}

string GameChoise(enGameChoise GameChoise)
{
	string arrGameChoise[3] = { "Stone", "Paper", "Scissor" };
	return arrGameChoise[GameChoise - 1];
}

void ShowTheGameOver() {

	cout << endl << Tabs(6) << "___________________________________________________________\n";
	cout << endl << Tabs(6) << "___________________+++ G A M E  O V E R +++________________\n";
	cout << endl << Tabs(6) << "___________________________________________________________\n";
}

enWinner WhoWonTheGame(short Player1wonTimes, short ComputerWonTimes)
{
	stGameResult GameResult;

	if (Player1wonTimes > ComputerWonTimes)
		return enWinner::Player;
	else if (Player1wonTimes < ComputerWonTimes)
		return enWinner::Computer;
	else
		return enWinner::Draw;
}

stGameResult FullGameResult(short NumberOfRounds, short Player1WonTimes, short ComputerWonTimes, short DrawTimes)
{
	stGameResult GameResult;

	GameResult.GameRound = NumberOfRounds;
	GameResult.Player1WonTimes = Player1WonTimes;
	GameResult.ComputerWonTimes = ComputerWonTimes;
	GameResult.Winner = WhoWonTheGame(Player1WonTimes, ComputerWonTimes);
	GameResult.WinnerName = WinnerName(GameResult.Winner);

	return GameResult;
}

void PrintRoundResults(stRoundInfo RoundInfo)
{
	cout << "Player1 Choice: " << GameChoise(RoundInfo.Player1Choise) << endl;
	cout << "Computer Choice: " << GameChoise(RoundInfo.ComputerChoise) << endl;
	cout << "Round Winner   : [" << RoundInfo.WinnerName << "]\n";
	cout << "_________________________________________\n" << endl;
}

void SetTheColorOnScreen(enWinner Winner) {

	switch (Winner)
	{
	case enWinner::Player:
		system("color 2F");
		break;
	case enWinner::Computer:
		system("color 4F");
		cout << "\a";

		break;
	default:
		system("color 6F");
		break;
	}
}

void PrintGameResults(stGameResult GameResult)
{
	cout << endl << Tabs(6) << "___________________[G A M E  R E S U L T]___________________\n";
	cout << endl << Tabs(6) << "Game Rounds  : " << GameResult.GameRound << endl;
	cout << endl << Tabs(6) << "Player1 won times : " << GameResult.Player1WonTimes << endl;
	cout << endl << Tabs(6) << "Computer won times : " << GameResult.ComputerWonTimes << endl;
	cout << endl << Tabs(6) << "Draw times : " << GameResult.DrawTimes << endl;
	cout << endl << Tabs(6) << "Final Winner : " << GameResult.WinnerName << endl;
	cout << endl << Tabs(6) << "____________________________________________________________\n";


}


stGameResult playGame(short NumberOfRounds)
{

	stRoundInfo RoundInfo;

	short PlayerHowManyWow = 0, ComputerHowManyWow = 0, DrawTimes = 0;

	for (short GameRound = 1;GameRound<= NumberOfRounds;GameRound++)
	{
		cout << "\nRound[" << GameRound << "] beigns : \n";

		cout << "\n_______________ Round[" << GameRound << "]" << "_______________\n";

		RoundInfo.RoundNumber = GameRound;
		RoundInfo.Player1Choise = ReadPlayerChoise();
		RoundInfo.ComputerChoise = GetComputerChoise();
		RoundInfo.Winner = WhoWonTheRound(RoundInfo);
		RoundInfo.WinnerName = WinnerName(RoundInfo.Winner);
		cout << "\n________________________________________________________\n";

		PrintRoundResults(RoundInfo);
		SetTheColorOnScreen(RoundInfo.Winner);


		if (RoundInfo.Winner == enWinner::Player)
			PlayerHowManyWow++;

		else if (RoundInfo.Winner == enWinner::Computer)
			ComputerHowManyWow++;
		else
			DrawTimes++;

	}


	return FullGameResult(NumberOfRounds, PlayerHowManyWow, ComputerHowManyWow, DrawTimes);
}

void ResetGame()
{
	system("cls");
	system("color 0F");
}

void StartGame() {

	string PlayAgain = "Y";
	do {
		ResetGame();
		stGameResult GameResult = playGame(ReadHowManyRounds());
		ShowTheGameOver();
		PrintGameResults(GameResult);

		cout << endl << Tabs(6) << "Do you want to play again ? Y or  N    : ";
		cin >> PlayAgain;

	} while (PlayAgain == "y" || PlayAgain == "Y");
}

int main()
{
	srand((unsigned)time(NULL));
	StartGame();
}
