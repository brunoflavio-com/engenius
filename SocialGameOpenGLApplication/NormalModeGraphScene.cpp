#include "NormalModeGraphScene.h"
#include <gl\glut.h>
#include <gl\freeglut.h>

#include "HangmanScene.h"
#include "TicTacToeScene.h"

NormalModeGraphScene::NormalModeGraphScene(SocialGamePublicAPIClient *client, std::string loginEmail):GraphScene(client, loginEmail)
{
	gameOn = false;
}


NormalModeGraphScene::~NormalModeGraphScene()
{
}


void NormalModeGraphScene::Draw3dObjects(void){
	if (gameOn) return game->Draw3dObjects();
	graph->draw();
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
}

void NormalModeGraphScene::Timer(int value){
	if (gameOn) return game->Timer(value);
	
	GraphScene::Timer(value);		
	
}