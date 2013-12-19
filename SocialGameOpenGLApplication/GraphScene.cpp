#include "GraphScene.h"
#include "graphCoordWalker.h"
#include "GraphWalkerDraw.h"

GraphScene::GraphScene(SocialGamePublicAPIClient * client, string loginEmail)
{
	apiClient = client;
	email = loginEmail;
	graph =	apiClient->getGraph(email,2);
	graphCoordWalker walker;
	walker.walk(graph);
}


GraphScene::~GraphScene()
{
}


void GraphScene::Draw(void){
	
	GraphWalkerDraw drawWalker;
	drawWalker.walk(graph);
}

void GraphScene::Key(unsigned char key, int x, int y){
}

void GraphScene::KeyUp(unsigned char key, int x, int y){

}