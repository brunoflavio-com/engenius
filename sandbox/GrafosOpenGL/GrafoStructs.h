#ifndef M_PI
		#define M_PI 3.1415926535897932384626433832795
#endif

#define RAD(x)          (M_PI*(x)/180)
#define GRAUS(x)        (180*(x)/M_PI)

typedef	GLdouble Vertice[3];

typedef struct Camera{
	GLfloat fov;
	GLdouble dir_lat;
	GLdouble dir_long;
	GLfloat dist;
	Vertice center;

}Camera;

typedef struct special_Key{
  GLboolean   up,down,left,right;
}special_Key;