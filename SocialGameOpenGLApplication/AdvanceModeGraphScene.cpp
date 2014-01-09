#include "AdvanceModeGraphScene.h"
#include "GraphFactory.h"
#include <gl\glut.h>
#include <gl\freeglut.h>


#define REMOTE_GRAPH_LEVEL 3

AdvanceModeGraphScene::AdvanceModeGraphScene(SocialGamePublicAPIClient *client, std::string loginEmail):GraphScene(client, loginEmail)
{
	graph = getGraph(loginEmail, REMOTE_GRAPH_LEVEL);
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

Graph * AdvanceModeGraphScene::getGraph(std::string loginEmail ,int level){
	ns5__Graph * ns5_graph = apiClient->getGraph(email, level);
	Graph * tempGraph = GraphFactory::convertGraph(ns5_graph, loginEmail);
	return tempGraph;
}

void AdvanceModeGraphScene::moveGraphToNewUser(User * user){
	Graph * tempGraph = graph;
	graph = getGraph(user->email,REMOTE_GRAPH_LEVEL);
}