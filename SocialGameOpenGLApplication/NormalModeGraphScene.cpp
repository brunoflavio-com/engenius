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

	glPushMatrix();

	glColor3ub(200, 0, 0);
	glRasterPos2d(0.5, 0.9);

	unsigned char s[100];

	strcpy((char*)s, "Normal Mode");

	glutBitmapString(GLUT_BITMAP_HELVETICA_18, s);
	glEnable(GL_LIGHTING);

	glPopMatrix();

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
	
}

void NormalModeGraphScene::PassiveMotion(int x, int y) {
	if (gameOn) return game->PassiveMotion(x, y);
	GraphScene::PassiveMotion(x, y);
}

void NormalModeGraphScene::moveGraphToNewUser(User * user){
	graph->changeUser(user->email);
}