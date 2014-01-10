#include "AdvanceModeGraphScene.h"
#include "GraphFactory.h"
#include <gl\glut.h>
#include <gl\freeglut.h>


#define REMOTE_GRAPH_LEVEL 3

AdvanceModeGraphScene::AdvanceModeGraphScene(SocialGamePublicAPIClient *client, std::string loginEmail):GraphScene(client, loginEmail)
{
	getUserPointsAndLevel();
	graph = getGraph(loginEmail, REMOTE_GRAPH_LEVEL);
	createMessage("Advance Mode");
}

void AdvanceModeGraphScene::Draw3dObjects(void){
	graph->draw(true);
}

void AdvanceModeGraphScene::DrawOverlay(void){
	
}

Graph * AdvanceModeGraphScene::getGraph(std::string loginEmail ,int level){
	ns5__Graph * ns5_graph = apiClient->getGraph(email, level);
	Graph * tempGraph = GraphFactory::convertGraph(ns5_graph, loginEmail);
	return tempGraph;
}

void AdvanceModeGraphScene::verticeClicked(User * previousUser, User * nextUser){
	//Get new graph from remote api
	Graph * tempGraph = graph;
	graph = getGraph(nextUser->email,REMOTE_GRAPH_LEVEL);
}

void AdvanceModeGraphScene::Timer(int value){
	GraphScene::Timer(value);
	if (returningToGame)
	{
		createMessage("Avanced Mode");
		returningToGame = false;
	}
}