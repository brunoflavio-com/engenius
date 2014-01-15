#include "MazeScene.h"
#include <gl\freeglut.h>
#include <ctime>

using namespace MinigamesMaze;

MazeScene::MazeScene(SocialGamePublicAPIClient* client, string loginEmail, int level)
{
	string mapString = client->getMazeMap(level);
	this->map = new MazeMap(mapString);
	this->xPosition = map->getStartColumn() + this->cubeAndSphereSize / 2;
	this->zPosition = map->getStartLine() + this->cubeAndSphereSize / 2;
	this->yPosition = this->cubeAndSphereSize / 2;
	
	this->level = level;
	this->over = false;
	this->winner = false;
	this->points = this->MAX_POINTS;
	this->timePoints = time(0);

	this->giveUp = false;

	arrowKeys.up = false;
	arrowKeys.down = false;
	arrowKeys.left = false;
	arrowKeys.right = false;
	hintPressed = false;

	hintStart = -1;
}

MazeScene::~MazeScene()
{
	delete map;
	delete client;
}

void MazeScene::Init(void)
{

}

void MazeScene::Timer(int value)
{
	int newLine;
	int newColumn;
	float step = 0.2;

	if (arrowKeys.up && !colision()){
		zPosition -= step;
		newLine = (int)(zPosition - (cubeAndSphereSize / 2));
		newColumn = (int)xPosition;
		map->setCurrentPosition(newLine, newColumn);
	}
	if (arrowKeys.down && !colision()){
		zPosition += step;
		newLine = (int)(zPosition + (cubeAndSphereSize / 2));
		newColumn = (int)xPosition;
		map->setCurrentPosition(newLine, newColumn);
	}
	if (arrowKeys.left && !colision()){
		xPosition -= step;
		newLine = (int)zPosition;
		newColumn = (int)(xPosition + (cubeAndSphereSize / 2));
		map->setCurrentPosition(newLine, newColumn);
	}
	if (arrowKeys.right && !colision()){
		xPosition += step;
		newLine = (int)zPosition;
		newColumn = (int)(xPosition - (cubeAndSphereSize / 2));
		map->setCurrentPosition(newLine, newColumn);
	}

	
	currTime = time(0);
	if (hintPressed){	
		hintStart = currTime;
		hintPressed = false;
	}

	if (map->isFinalPosition())
	{
		over = true;
		winner = true;
	}
	
	calculatePoints();

	if (giveUp)
	{
		points = 0.0f;
		over = true;
		winner = false;
	}
}

void MazeScene::Draw(void)
{

}

void MazeScene::Draw3dObjects(void)
{
	//Clear Screnn and Depth Buffer
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();


	glPushMatrix();
		glScalef(0.1, 0.1, 0.1);
		gluLookAt(map->getWidth() / 2.0, 50, map->getHeight() / 2.0, map->getWidth() / 2.0, 0, map->getHeight() / 2.0, 0,0,-1);
		
		this->drawMap();
		
		if (hintStart != -1 && ((currTime - hintStart) < maxHintSeconds)){
			drawHint();
		}
		else{
			hintStart = -1;
		}
		glPushMatrix();
			GLfloat red[4] = { 1.0, 0.0, 0.0, 1.0 };
			glPushAttrib(GL_LIGHTING_BIT | GL_CURRENT_BIT);
			glMaterialfv(GL_FRONT, GL_DIFFUSE, red);
			this->drawSphere(xPosition, yPosition, zPosition, cubeAndSphereSize / 2);
			glPopAttrib();
		glPopMatrix();
	glPopMatrix();

}

void MazeScene::DrawOverlay(void)
{

}

void MazeScene::Key(unsigned char key, int x, int y)
{
	switch (key){
		/*Give Up*/	
	case 27:
		giveUp = true;
		/*Hint*/
	case 'h':
	case 'H':
		hintPressed = true;
		hintStart = 0;
		break;
	}
}

void MazeScene::SpecialKey(int key, int x, int y)
{
	switch (key){
	case GLUT_KEY_UP: arrowKeys.up = true;
		break;
	case GLUT_KEY_DOWN: arrowKeys.down = true;
		break;
	case GLUT_KEY_LEFT: arrowKeys.left = true;
		break;
	case GLUT_KEY_RIGHT: arrowKeys.right = true;
		break;
	}
}

void MazeScene::SpecialKeyUp(int key, int x, int y)
{
	switch (key){
	case GLUT_KEY_UP: arrowKeys.up = false;
		break;
	case GLUT_KEY_DOWN: arrowKeys.down = false;
		break;
	case GLUT_KEY_LEFT: arrowKeys.left = false;
		break;
	case GLUT_KEY_RIGHT: arrowKeys.right = false;
		break;
	}
}

void MazeScene::Mouse(int btn, int state, int x, int y)
{

}

void MazeScene::MotionMouse(int x, int y)
{

}

bool MazeScene::isOver()
{
	return over;
}

bool MazeScene::isWinner()
{
	return winner;
}

float MazeScene::getPoints()
{
	return points;
}

//Private
void MazeScene::drawMap(void)
{
	int height = this->map->getHeight();
	int width = this->map->getWidth();

	int x = 0;
	int y = 0;
	int z = 0;
	for (int line = 0; line < height; line++)
	{
		for (int column = 0; column < width; column++)
		{
			if (this->map->isWall(line, column))
			{
				this->drawCube(x, y, z, this->cubeAndSphereSize);
			}
			x++;
		}
		z++;
		x = 0;
	}
}


void MazeScene::drawCube(float x, float y, float z, float side)
{
	GLfloat grey[4] = { 0.7, 0.7, 0.7, 1.0 };
	glPushAttrib(GL_LIGHTING_BIT | GL_CURRENT_BIT);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, grey);
	//d
	glBegin(GL_POLYGON);
	glNormal3f(0, -1, 0);
	glVertex3f(x, y, z);
	glVertex3f(x + side, y, z);
	glVertex3f(x + side, y, z + side);
	glVertex3f(x, y, z + side);
	glEnd();
	//b
	glBegin(GL_POLYGON);
	glNormal3f(0, 0, -1);
	glVertex3f(x, y, z);
	glVertex3f(x, y + side, z);
	glVertex3f(x + side, y + side, z );
	glVertex3f(x + side, y, z);
	glEnd();
	//t
	glBegin(GL_POLYGON);
	glNormal3f(0, 1, 0);
	glVertex3f(x, y + side, z);
	glVertex3f(x, y + side, z + side);
	glVertex3f(x + side, y + side, z + side);
	glVertex3f(x + side, y + side, z);
	glEnd();
	//f
	glBegin(GL_POLYGON);
	glNormal3f(0, 0, 1);
	glVertex3f(x, y, z + side);
	glVertex3f(x + side, y, z + side);
	glVertex3f(x + side, y + side, z + side);
	glVertex3f(x, y + side, z + side);
	glEnd();
	//r
	glBegin(GL_POLYGON);
	glNormal3f(-1, 0, 0);
	glVertex3f(x, y, z);
	glVertex3f(x, y, z + side);
	glVertex3f(x, y + side, z + side);
	glVertex3f(x, y + side, z);
	glEnd();
	//l
	glBegin(GL_POLYGON);
	glNormal3f(1, 0, 0);
	glVertex3f(x + side, y, z);
	glVertex3f(x + side, y + side, z);
	glVertex3f(x + side, y + side, z + side);
	glVertex3f(x + side, y, z + side);
	glEnd();
	glPopAttrib();
}

void MazeScene::drawSphere(float x, float y, float z, float radius)
{
	glTranslatef(x, y, z);
	glutSolidSphere(radius, 20, 20);
}

void MazeScene::drawSquare(float x, float y, float z, float side)
{
	glBegin(GL_POLYGON);
	glNormal3f(0, 1, 0);
	glVertex3f(x, y, z);
	glVertex3f(x, y + side, z + side);
	glVertex3f(x + side, y + side, z + side);
	glVertex3f(x + side, y + side, z);
	glEnd();
}

void MazeScene::drawHint()
{
	int line;
	int column;
	map->getSuggestion(line, column);
	drawSquare(column, 0, line, cubeAndSphereSize);
}

bool MazeScene::colision()
{
	int lineToCheck;
	int columnToCheck;
	if (arrowKeys.up)
	{
		lineToCheck = (int)(zPosition - (cubeAndSphereSize / 2));
		columnToCheck = (int)xPosition;
	}
	else if (arrowKeys.down)
	{
		lineToCheck = (int)(zPosition + (cubeAndSphereSize / 2));
		columnToCheck = (int)xPosition;
	}
	else if (arrowKeys.right)
	{
		lineToCheck = (int)zPosition;
		columnToCheck = (int)(xPosition + (cubeAndSphereSize / 2));
	}
	else if (arrowKeys.left)
	{
		lineToCheck = (int)zPosition;
		columnToCheck = (int)(xPosition - (cubeAndSphereSize / 2));
	}
	return map->isWall(lineToCheck, columnToCheck);
}

void MazeScene::calculatePoints()
{
	int timeNow = time(0);
	int dif = timeNow - timePoints;

	if (dif > 1)
	{
		timePoints = timeNow;
		points /= 1.1;
	}
}
