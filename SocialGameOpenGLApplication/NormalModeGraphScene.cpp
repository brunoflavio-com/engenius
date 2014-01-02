#include "NormalModeGraphScene.h"
#include <gl\glut.h>
#include <gl\freeglut.h>

NormalModeGraphScene::NormalModeGraphScene(SocialGamePublicAPIClient *client, std::string loginEmail):GraphScene(client, loginEmail)
{
}


NormalModeGraphScene::~NormalModeGraphScene()
{
}


void NormalModeGraphScene::Draw3dObjects(void){
	graph->draw();
}

void NormalModeGraphScene::DrawOverlay(void){
	glPushMatrix();

	glColor3ub(200, 0, 0);
	glRasterPos2d(0.5, 0.9);

	unsigned char s[100];

	strcpy((char*)s, "Normal Mode");

	glutBitmapString(GLUT_BITMAP_HELVETICA_18, s);
	glEnable(GL_LIGHTING);

	glPopMatrix();

}