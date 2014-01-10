#include "NormalModeGraphScene.h"
#include <gl\glut.h>
#include <gl\freeglut.h>
#include "GraphFactory.h"
#include "HangmanScene.h"
#include "TicTacToeScene.h"
#include "MazeScene.h"

NormalModeGraphScene::NormalModeGraphScene(SocialGamePublicAPIClient *client, std::string loginEmail, int level):GraphScene(client, loginEmail)
{
	gameOn = false;
	graph = getGraph(loginEmail, level);
	for each(User * u in graph->users){
		if (u->graphLevel == level){
			targetUser = u;
			targetUser->isTarget = true;
			break;
		}	
	}
	createMessage("Mission mode");
}

Graph * NormalModeGraphScene::getGraph(std::string loginEmail, int level){
	return  GraphFactory::buildRandomGraph(level, loginEmail);
}

void NormalModeGraphScene::Draw3dObjects(void){
	if (gameOn) return game->Draw3dObjects();
	graph->draw(true);
}

void NormalModeGraphScene::DrawOverlay(void){


	if (gameOn) return game->DrawOverlay();

}

void NormalModeGraphScene::Key(unsigned char key, int x, int y) {
	if (gameOn) return game->Key(key, x, y);
		
	GraphScene::Key(key, x, y);
	if (key == 'G') {
		game = new HangmanScene(GraphScene::apiClient, GraphScene::email);
		gameOn = true;
	}
	if (key == 'T') {
		game = new TicTacToeScene(GraphScene::apiClient, GraphScene::email);
		gameOn = true;
	}
	if (key == 'M' || key == 'm') {
		game = new MinigamesMaze::MazeScene(GraphScene::apiClient, GraphScene::email);
		gameOn = true;
	}

	GraphScene::Key(key, x, y);
}

void NormalModeGraphScene::SpecialKey(int key, int x, int y)
{
	if (gameOn) return game->SpecialKey(key, x, y);

	GraphScene::Key(key, x, y);
}

void NormalModeGraphScene::SpecialKeyUp(int key, int x, int y)
{
	if (gameOn) return game->SpecialKeyUp(key, x, y);


}

void NormalModeGraphScene::Timer(int value){
	if (gameOn) return game->Timer(value);
	GraphScene::Timer(value);
	if (returningToGame)
	{
		createMessage("Mission Mode");
		returningToGame = false;
	}
}

void NormalModeGraphScene::PassiveMotion(int x, int y) {
	if (gameOn) return game->PassiveMotion(x, y);
	GraphScene::PassiveMotion(x, y);
}

void NormalModeGraphScene::verticeClicked(User * previousUser,User * nextUser ){
	//generate random user response
	srand(time(0));
	int userDecision = rand()%3;
	int randomGame;
	switch (userDecision){
	//User rejects introduction
	case 0:
		createMessage("User " + nextUser->email + "has rejected to introduce you");
		break;
		//User asks for game to be played in order to accept introduction
	case 1:
		//Random Game
		createMessage("User " + nextUser->email + " asked you to play a game");
		//DEBUg
		break;
		randomGame = rand() % 2;
		//debug
		randomGame = 2;
		switch (randomGame){
		case 0:
			game = new HangmanScene(GraphScene::apiClient, GraphScene::email);
		case 1:
			game = new TicTacToeScene(GraphScene::apiClient, GraphScene::email);
		case 2:
			game = new MinigamesMaze::MazeScene(GraphScene::apiClient, GraphScene::email);
		}
		gameOn = true;
		break;
		//User accepts introduction
	case 2:
		createMessage("User " + nextUser->email + "has accepted to introduce you");
		graph->changeUser(nextUser->email);
		break;
	}
	
}