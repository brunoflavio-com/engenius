#include "AdvanceModeGraphScene.h"
#include "GraphFactory.h"
#include <gl\glut.h>
#include <gl\freeglut.h>


#define REMOTE_GRAPH_LEVEL 3

AdvanceModeGraphScene::AdvanceModeGraphScene(SocialGamePublicAPIClient *client, std::string loginEmail):GraphScene(client, loginEmail)
{
	getUserPointsAndLevel();
	graph = getGraph(loginEmail, REMOTE_GRAPH_LEVEL);
	graph->user->isCurrentRealUser = true;
	returningMessage = "Advanced Mode";
}

void AdvanceModeGraphScene::Draw3dObjects(void){
	graph->draw(true);
}

void AdvanceModeGraphScene::DrawOverlay(void){
	GLfloat colors[2][4] = {
		{ 1.0, 1.0, 0.0, 0.7 },
		{ 0.0, 0.0, 1.0, 0.7 }
	};
	unsigned char textIndications[2][20] = { "You", "Current position"};
	drawPositionIndications(2, colors, textIndications);
}

Graph * AdvanceModeGraphScene::getGraph(std::string loginEmail ,int level){
	ns5__Graph * ns5_graph = apiClient->getGraph(email, level);
	Graph * tempGraph = GraphFactory::convertGraph(ns5_graph, loginEmail);
	return tempGraph;
}

void AdvanceModeGraphScene::verticeClicked(User * previousUser, User * nextUser){
	Relationship * relationship = graph->getRelationship(previousUser, nextUser);
	if (relationship == NULL)
	{
		createMessage("Cant go diretly do that user");
		return;
	}

	//Get new graph from remote api
	Graph * tempGraph = graph;
	graph = getGraph(nextUser->email,REMOTE_GRAPH_LEVEL);
	User * u = graph->getUser(email);
	u->isCurrentRealUser = true;
}

void AdvanceModeGraphScene::Timer(int value){
	glTime = value;
	GraphScene::Timer(value);
	if (returningToGame)
	{
		createMessage(returningMessage);
		returningToGame = false;
	}
}