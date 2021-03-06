#include "NormalModeGraphScene.h"
#include <gl\glut.h>
#include <gl\freeglut.h>
#include "GraphFactory.h"
#include "HangmanScene.h"
#include "TicTacToeScene.h"
#include "MazeScene.h"
#include "IMinigame.h"
#include "GraphPLEngine.h"

NormalModeGraphScene::NormalModeGraphScene(SocialGamePublicAPIClient *client, std::string loginEmail, int level) :GraphScene(client, loginEmail)
{
	gameOn = false;
	this->realUser = realUser;
	graph = getGraph(loginEmail, level);

	int highestLevel = 0;
	for each(User * u in graph->users){
		if (u->graphLevel >= highestLevel){			
			targetUser = u;			
			highestLevel = u->graphLevel;
		}	
	}
	targetUser->isTarget = true;

	////
	pl.loadGraph(graph);
	this->shortestPath =  pl.getShortestPath(graph->user, targetUser);
	this->strongestPath = pl.getStrongestPath(graph->user, targetUser);

	highlightPath = 0;
	////

	ALuint buffer, source;
	buffer = alutCreateBufferFromFile("./sounds/start.wav");
	alGenSources(1, &source);
	alSourcei(source, AL_BUFFER, buffer); 
	alSourcePlay(source);
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

	GLfloat colors[4][4] = {
		{ 1.0, 1.0, 0.0, 0.7 },
		{ 0.0, 0.0, 1.0, 0.7 },
		{ 0.0, 1.0, 0.0, 0.7 },
		{ 1.0, 1.0, 1.0, 0.1 },
	};

	unsigned char textIndications[4][30] = { 
		"You", 
		"Current position", 
		"Mission Target",
		"'S' to toggle paths."};
	drawPositionIndications(4, colors, textIndications);
}

void NormalModeGraphScene::Key(unsigned char key, int x, int y) {
	if (gameOn) return game->Key(key, x, y);
	if (key == 27) {
		selectedObject = NULL;
		isFinished = true;
		returningMessage = "Mission canceled";
		return;
	}
	
	if (key == 's' || key == 'S') {
		togglePath();
	}

	//to manually attempt minigame:
	if (key == '1') {
		this->selectedObject = NULL;
		this->highlightPath = 0;
		this->nextUser = graph->user;
		game = new HangmanScene(GraphScene::apiClient, GraphScene::email);
		gameOn = true;
	}
	if (key == '2') {
		this->selectedObject = NULL;
		this->highlightPath = 0;
		this->nextUser = graph->user;
		game = new TicTacToeScene(GraphScene::apiClient, GraphScene::email);
		gameOn = true;
	}
	if (key == '3') {
		this->selectedObject = NULL;
		this->highlightPath = 0;
		this->nextUser = graph->user;
		game = new MinigamesMaze::MazeScene(GraphScene::apiClient, GraphScene::email,3);
		gameOn = true;
	}		

	GraphScene::Key(key, x, y);
}

void NormalModeGraphScene::SpecialKey(int key, int x, int y)
{
	if (gameOn) return game->SpecialKey(key, x, y);

	GraphScene::SpecialKey(key, x, y);
}

void NormalModeGraphScene::SpecialKeyUp(int key, int x, int y)
{
	if (gameOn) return game->SpecialKeyUp(key, x, y);
	GraphScene::SpecialKeyUp(key,x,y);

}

void NormalModeGraphScene::Timer(int value){
	glTime = value;
	/*Testar o interface IMinigame com o maze*/
	if (gameOn)
	{
		IMinigame* teste = dynamic_cast<IMinigame*>(game);
		if (teste != NULL)
		{
			if (bool over = teste->isOver()){
				gameOn = false;
				if (teste->isWinner()){
					float points = (int) teste->getPoints();
					createMessage("You won the mini-game and got \n" + to_string((int) points) + " points");
					userPoints += points;
					apiClient->setUserPoints(userPoints);
					advanceToNextVertice();
				}
				else{
					createMessage("oh... you lost the mini-game");					
				}
			}
			else {
				game->Timer(value);
			}
		}
	}

	 
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

void NormalModeGraphScene::verticeClicked(User * previousUser, User * nextUser){
	this->previousUser = previousUser;
	this->nextUser = nextUser;

	Relationship * relationship = graph->getRelationship(previousUser, nextUser);

	if (relationship == NULL)
	{
		createMessage("Cant go diretly do that user");
		return;
	}

	if (relationship->walked){
		//User has already accepted to introduce
		graph->movetoVertice(nextUser);
		return;
	}

	//generate random user response
	srand(time(0));
	int userDecision = rand() % 3;
	//userDecision = 2;
	int randomGame;
	switch (userDecision){
	case 0:
		//User rejects introduction
		createMessage("User " + nextUser->email + "\nhas rejected to introduce you");
		break;

	case 1:
		//User asks for game to be played in order to accept introduction

		this->selectedObject = NULL;
		this->highlightPath = 0;

		//Random Game
		createMessage("User " + nextUser->email + "\nasked you to play a game");
		
		randomGame = rand() % 3;
		/*DEBUG:*/
		//randomGame = 2;
		switch (randomGame){
		case 0:
			game = new HangmanScene(GraphScene::apiClient, GraphScene::email);
			break;
		case 1:
			game = new TicTacToeScene(GraphScene::apiClient, GraphScene::email);
			break;
		case 2:
			game = new MinigamesMaze::MazeScene(GraphScene::apiClient, GraphScene::email, (rand() % 3 + 1));
			break;
		}
		gameOn = true;
		break;

	case 2:
		//User accepts introduction
		advanceToNextVertice();
		break;
	}
}


void NormalModeGraphScene::advanceToNextVertice(){
	if (nextUser == targetUser)
	{	//Update user Level
		userLevel++;
		apiClient->setUserLevel(userLevel);
		//Return to adnvance mode with congratulations message
		selectedObject = NULL;
		isFinished = true;
		returningMessage = "Congratulations you achieved your mission";
	}
	else{
		createMessage("User " + nextUser->email + "\nhas accepted to introduce you");
		graph->movetoVertice(nextUser);
	}
}

void NormalModeGraphScene::togglePath() {
	highlightPath++;
	if (highlightPath > 2) highlightPath = 0;

	switch (highlightPath) {
	default:
	case 0:
		for each (Relationship * relationship in strongestPath) {
			relationship->highlightStrongest = false;
			createMessage(" ");
		}
		break;
	case 1:
		for each (Relationship * relationship in shortestPath) {
			relationship->highlightShortest = true;
		}
		for each (Relationship * relationship in strongestPath) {
			relationship->highlightStrongest = false;
		}
		createMessage("Shortest path highlighted.");
		break;
	case 2:
		for each (Relationship * relationship in shortestPath) {
			relationship->highlightShortest = false;
		}
		for each (Relationship * relationship in strongestPath) {
			relationship->highlightStrongest = true;
		}
		createMessage("Strongest path highlighted.");
		break;
	}
}
