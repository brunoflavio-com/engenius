#ifndef M_PI
		#define M_PI 3.1415926535897932384626433832795
#endif

#define RAD(x)          (M_PI*(x)/180)
#define GRAUS(x)        (180*(x)/M_PI)
#define GAP		25
typedef	GLdouble Vertice[3];

typedef struct Camera{
	GLfloat height;
	GLdouble dir_lat;
	GLdouble dir_long;
	GLfloat dist;
	Vertice eye;
	Vertice center;
}Camera;

typedef struct special_Key{
  GLboolean   up,down,left,right;
}special_Key;

typedef struct Mouse_State{
	GLint        xMouse;
    GLint        yMouse;
}Mouse_State;

typedef struct Windows{
	GLint        Main;
    GLint        Top;
}Windows;