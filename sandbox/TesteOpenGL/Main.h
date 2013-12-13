
#ifndef M_PI
#define M_PI 3.1415926535897932384626433832795
#endif

#define RAD(x)          (M_PI*(x)/180)
#define GRAUS(x)        (180*(x)/M_PI)

#define DEBUG 1
#define LADO_MAXIMO     2
#define LADO_MINIMO     0.3
#define DELTA_LADO      0.1


/* VARIAVEIS GLOBAIS */

typedef struct {
	GLboolean   doubleBuffer;
	GLint       delayMovimento;
	GLboolean   debug;
	GLboolean    movimentoTranslacao;      // se os cubinhos se movem
	GLboolean   movimentoRotacao;         // se o cubo grande roda;
}Estado2;


typedef struct {
	GLfloat   theta[3];     // 0-Rotação em X; 1-Rotação em Y; 2-Rotação em Z

	GLint     eixoRodar;    // eixo que está a rodar (mudar com o rato)
	GLfloat   ladoCubo;     // comprimento do lado do cubo
	GLfloat   deltaRotacao; // incremento a fazer ao angulo quando roda
	GLboolean  sentidoTranslacao; //sentido da translação dos cubos pequenos
	GLfloat    translacaoCubo; //
	GLfloat   deltaTranslacao; // incremento a fazer na translacao
	GLboolean sentidoRotacao;  //sentido da rotação dos cubos pequenos
	GLfloat   thetaCubo;     // Rotação dos cubinhos
}Modelo2;

class Main : public InterfaceGL{
public:
	Main(){}

	void static change(int programa){
		glutMouseFunc(NULL);
		glDisable(GL_DEPTH_TEST);
		glutTimerFunc(estado.delayMovimento,NULL,0);
		jogoAtual[programa]->Run();	}

	void static inicia_modelo()
	{
		estado.delayMovimento=50;
		estado.movimentoTranslacao=GL_FALSE;
		estado.movimentoRotacao=GL_FALSE;

		modelo.theta[0]=0;
		modelo.theta[1]=0;
		modelo.theta[2]=0;
		modelo.eixoRodar=-1;  // eixo de X;
		modelo.ladoCubo=1;
		modelo.translacaoCubo=4.0;
		modelo.sentidoTranslacao=false;
		modelo.thetaCubo=1;
	}

	void Init(void)
	{
		inicia_modelo();
		glClearColor(0.0, 0.0, 0.0, 0.0);
		glEnable(GL_POINT_SMOOTH);
		glEnable(GL_LINE_SMOOTH);
		glEnable(GL_POLYGON_SMOOTH);
		glEnable(GL_DEPTH_TEST);

		glPolygonMode(GL_BACK, GL_LINE);
	}

	void static Reshape(int width, int height)
	{
		glViewport(0, 0, (GLint) width, (GLint) height);  
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		if (width < height)
			glOrtho(-5, 5, -5*(GLdouble)height/width, 5*(GLdouble)height/width,-10,10);
		else
			glOrtho(-5*(GLdouble)width/height, 5*(GLdouble)width/height,-5, 5, -10,10);
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
	}

	void static strokeCenterString(char *str,double x, double y, double z, double s)
{
	int i,n;
	
	n = strlen(str);
	glPushMatrix();
	  glTranslated(x-glutStrokeLength(GLUT_STROKE_ROMAN,(const unsigned char*)str)*0.5*s,y-119.05*0.5*s,z);
	  glScaled(s,s,s);
	  for(i=0;i<n;i++)
		  glutStrokeCharacter(GLUT_STROKE_ROMAN,(int)str[i]);
	glPopMatrix();

}

	void static Draw(void)
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glColor3f(1,0,0);
		glPushMatrix();
		strokeCenterString("ENGENIUS", 0, 0, 0 , 0.01); // string, x ,y ,z ,scale
		glPopMatrix();

		if (estado.doubleBuffer)
			glutSwapBuffers();
		else
			glFlush();

	}
	void static Timer(int value)
	{
		glutTimerFunc(estado.delayMovimento, Timer, 0);
		glutPostRedisplay();
	}

	void static imprime_ajuda(void)
	{
		printf("ESCOLHER MODO\n");

		printf("1 - Menu\n");
		printf("2 - Cubo\n");
		printf("3 - Relogio\n");
		printf("4\n");


	}

	void static Key(unsigned char key, int x, int y)
	{
		switch (key) {
		case 27:
			exit(1);
		case '1' :
			change(0);
			break;
		case '2' :
			change(1);
			break;
		case '3' :
			change(2);
			break;
		case '4' :
			printf("ola\n");
			break;
		case 'h' :
		case 'H' :
			imprime_ajuda();
			break;
		case '+':
			if(modelo.ladoCubo<LADO_MAXIMO)
			{
				modelo.ladoCubo+=DELTA_LADO;
				glutPostRedisplay();
			}
			break;

		case '-':
			if(modelo.ladoCubo>LADO_MINIMO)
			{
				modelo.ladoCubo-=DELTA_LADO;
				glutPostRedisplay();
			}
			break;
		case 'i' :
		case 'I' :
			inicia_modelo();
			glutPostRedisplay();
			break;
		case 'p' :
		case 'P' :
			if(estado.movimentoTranslacao){
				estado.movimentoTranslacao=false;
			}
			else{
				estado.movimentoTranslacao=true;
			}
			break;

		}

		if(DEBUG)
			printf("Carregou na tecla %c\n",key);

	}
	void KeyUp(unsigned char key, int x, int y)
	{

		if(DEBUG)
			printf("Largou a tecla %c\n",key);
	}
	void static SpecialKey(int key, int x, int y)
	{
		switch (key) {
		case GLUT_KEY_F1 :
			inicia_modelo();
			glutPostRedisplay();
			break;

		}


		if(DEBUG)
			printf("Carregou na tecla especial %d\n",key);
	}

	void static SpecialKeyUp(int key, int x, int y)
	{

		if(DEBUG)
			printf("Largou a tecla especial %d\n",key);

	}

	void MouseMotion(int x, int y)
	{
		if(DEBUG)
			printf("Mouse Motion %d %d\n",x,y);

	}

	void MousePassiveMotion(int x, int y)
	{
		if(DEBUG)
			printf("Mouse Passive Motion %d %d\n",x,y);

	}

	void static Mouse(int button, int state, int x, int y)
	{
		switch(button){
		case GLUT_LEFT_BUTTON :      
			if(state == GLUT_DOWN)
			{        
				if(modelo.eixoRodar!=0){
					modelo.eixoRodar=0;
				}
				else{
					modelo.eixoRodar=-1;
				}
			}
			break;
		case GLUT_MIDDLE_BUTTON :      
			if(state == GLUT_DOWN)
			{        
				if(modelo.eixoRodar!=1){
					modelo.eixoRodar=1;
				}
				else{
					modelo.eixoRodar=-1;
				}
			}
			break;
		case GLUT_RIGHT_BUTTON :
			if(state == GLUT_DOWN)
			{        
				if(modelo.eixoRodar!=2){
					modelo.eixoRodar=2;
				}
				else{
					modelo.eixoRodar=-1;
				}
			}
			break;
		}
		if(DEBUG)
			printf("Mouse button:%d state:%d coord:%d %d\n",button,state,x,y);
	}
	void Run()
	{
		estado.doubleBuffer=1;
		Init();
		imprime_ajuda();
		glutReshapeFunc(Reshape);
		glutDisplayFunc(Draw);
		glutKeyboardFunc(Key);
		glutSpecialFunc(SpecialKey);
		glutMouseFunc(Mouse);
		glutTimerFunc(estado.delayMovimento, Timer, 0);
	}
};