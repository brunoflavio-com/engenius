#include "AdvanceModeGraphScene.h"
#include <gl\glut.h>
#include <gl\freeglut.h>


AdvanceModeGraphScene::AdvanceModeGraphScene(SocialGamePublicAPIClient *client, std::string loginEmail):GraphScene(client, loginEmail)
{
	
}


AdvanceModeGraphScene::~AdvanceModeGraphScene()
{
}

void AdvanceModeGraphScene::Draw3dObjects(void){
	graph->draw(true);
}

void AdvanceModeGraphScene::DrawOverlay(void){
	glPushMatrix();

	glColor3ub(200, 0, 0);
	glRasterPos2d(0.5, 0.9);

	unsigned char s[100];

	strcpy((char*)s, "Advance Mode");

	glutBitmapString(GLUT_BITMAP_HELVETICA_18, s);
	glEnable(GL_LIGHTING);

	glPopMatrix();

}