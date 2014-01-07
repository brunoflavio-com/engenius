#include "MazeScene.h"
#include <gl\freeglut.h>

using namespace MinigamesMaze;

MazeScene::MazeScene()
{

}

MazeScene::MazeScene(SocialGamePublicAPIClient* client, string loginEmail)
{
	this->map = new MazeMap("Map1.txt");
	this->xPosition = map->getStartColumn() + this->cubeAndSphereSize / 2;
	this->zPosition = map->getStartLine() + this->cubeAndSphereSize / 2;
	this->yPosition = this->cubeAndSphereSize / 2;
	int Line, Column;
	this->map->getSuggestion(Line, Column);
	std::cout << "Line: " << Line << "Column: " << Column << std::endl;
}

MazeScene::~MazeScene()
{
	delete map;
}

void MazeScene::Init(void)
{

}

void MazeScene::Timer(int value)
{
	g_rotation += 0.1;
}

void MazeScene::Draw(void)
{

}

void MazeScene::Draw3dObjects(void)
{
	//Clear Screnn and Depth Buffer
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();

	//Define a viewing transformation
	gluLookAt(4, 2, 0, 0, 0, 0, 0, 1, 0);

	glPushMatrix();
		glRotatef(g_rotation, 0, 1, 0);
		glScalef(0.1, 0.1, 0.1);
		this->drawMap();
		glPushMatrix();
			this->drawSphere(xPosition, yPosition, zPosition, cubeAndSphereSize / 2);
		glPopMatrix();
	glPopMatrix();
}

void MazeScene::DrawOverlay(void)
{

}

void MazeScene::Key(unsigned char key, int x, int y)
{

}

void MazeScene::SpecialKey(int key, int x, int y)
{

}

void MazeScene::SpecialKeyUp(int key, int x, int y)
{

}

void MazeScene::Mouse(int btn, int state, int x, int y)
{

}

void MazeScene::MotionMouse(int x, int y)
{

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
}

void MazeScene::drawSphere(float x, float y, float z, float radius)
{
	glTranslatef(x, y, z);
	glutSolidSphere(radius, 20, 20);
}

