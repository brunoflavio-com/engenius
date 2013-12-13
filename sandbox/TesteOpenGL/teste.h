
#ifndef M_PI
#define M_PI 3.1415926535897932384626433832795
#endif

#define rtd(x)   (180*(x)/M_PI)
#define dtr(x)   (M_PI*(x)/180)

#define DEBUG 1

/* VARIÁVEIS GLOBAIS */

typedef struct {
	GLboolean   doubleBuffer;
	GLint       delay;
}Estado1;

typedef struct {
	GLint       hor,min,seg;
}Horas;

typedef struct {
	GLint       numLados;
	GLfloat     raio;
	GLfloat     tamLado;
	Horas       hora;
}Modelo1;


Estado1 estado1;
Modelo1 modelo1;

class Teste : public InterfaceGL{
public:
	Teste(){}
	void static change(int programa){
		glutMouseFunc(NULL);
		glDisable(GL_DEPTH_TEST);
		glutTimerFunc(estado1.delay,NULL,0);
		jogoAtual[programa]->Run();	}
	virtual void Init(void)
	{
		
		struct tm *current_time;
		time_t timer = time(0);

		//delay para o timer
		estado1.delay=1000;

		modelo1.tamLado=1;
		modelo1.numLados=40;
		modelo1.raio=0.75;


		// Lê hora do Sistema
		current_time = localtime(&timer);
		modelo1.hora.hor = current_time->tm_hour;
		modelo1.hora.min = current_time->tm_min;
		modelo1.hora.seg = current_time->tm_sec;

		glClearColor(0.3, 0.3, 0.3, 0.0);

		glEnable(GL_POINT_SMOOTH);
		glEnable(GL_LINE_SMOOTH);
		glEnable(GL_POLYGON_SMOOTH);
		glDisable(GL_DEPTH_TEST);

	}

	/**************************************
	***  callbacks de janela/desenho    ***
	**************************************/

	// CALLBACK PARA REDIMENSIONAR JANELA

	void static Reshape(int width, int height)
	{
		GLint size;
		GLfloat ratio=(GLfloat) width/height;
		GLfloat ratio1=(GLfloat) height/width;

		if (width < height)
			size = width;
		else
			size = height;

		// glViewport(botom, left, width, height)
		// define parte da janela a ser utilizada pelo OpenGL

		//glViewport(0, 0, (GLint) size, (GLint) size);
		glViewport(0, 0, width, height);


		// Matriz Projecção
		// Matriz onde se define como o mundo e apresentado na janela
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();

		// gluOrtho2D(left,right,bottom,top); 
		// projeccao ortogonal 2D, com profundidade (Z) entre -1 e 1
		if(width < height)
			gluOrtho2D(-1, 1, -1*ratio1, 1*ratio1);
		else
			gluOrtho2D(-1*ratio, 1*ratio, -1, 1);

		// Matriz Modelview
		// Matriz onde são realizadas as tranformações dos modelos desenhados
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
	}

	void static poligono(GLint n, GLfloat x0, GLfloat y0, GLfloat r){
		float x, y;
		glBegin(GL_POLYGON);
		for(int i = 0; i<n; i++){
			x=r*cos(0+((2*M_PI/n)*i))+x0;
			y=r*sin(0+((2*M_PI/n)*i))+y0;
			glVertex2f(x,y);

		}
		glEnd();
	}

	void static mostrador(GLfloat x0, GLfloat y0, GLfloat r){
		float x, y, x1, y1;
		int n=60;
		glBegin(GL_LINES);
		for(int i = 0; i<n; i++){
			x=r*cos(((2*M_PI/n)*i))+x0;
			y=r*sin(((2*M_PI/n)*i))+y0;

			if(i%15==0){
				x1=r*0.7*cos(((2*M_PI/n)*i))+x0;
				y1=r*0.7*sin(((2*M_PI/n)*i))+y0;
				glColor3f(0.0f, 0.0f, 1.0f);
				glVertex2f(x1,y1);
			}
			else if(i%5==0){
				x1=r*0.8*cos(((2*M_PI/n)*i))+x0;
				y1=r*0.8*sin(((2*M_PI/n)*i))+y0;
				glColor3f(0.0f, 0.0f, 0.0f);
				glVertex2f(x1,y1);
			}
			else{
				x1=r*0.9*cos(((2*M_PI/n)*i))+x0;
				y1=r*0.9*sin(((2*M_PI/n)*i))+y0;
				glColor3f(0.0f, 0.0f, 0.0f);
				glVertex2f(x1,y1);
			}		
			glVertex2f(x,y);

		}
		glEnd();
	}

	void static ponteiros(GLfloat x0, GLfloat y0, GLfloat r){
		float x, y;
		glBegin(GL_LINES);
		//segundos
		glColor3f(0.0f, 1.0f, 1.0f);
		x=r*0.7*cos(((-2*M_PI/60)*modelo1.hora.seg)+(M_PI/2))+x0;
		y=r*0.7*sin(((-2*M_PI/60)*modelo1.hora.seg)+(M_PI/2))+y0;
		glVertex2f(x,y);
		glVertex2f(x0,y0);

		//minutos
		glColor3f(0.0f, 0.0f, 0.5f);
		x=r*0.6*cos(((-2*M_PI/60)*modelo1.hora.min)+(M_PI/2))+x0;
		y=r*0.6*sin(((-2*M_PI/60)*modelo1.hora.min)+(M_PI/2))+y0;
		glVertex2f(x,y);
		glVertex2f(x0,y0);

		//horas
		glColor3f(0.5f, 0.0f, 0.5f);
		x=r*0.3*cos(((-2*M_PI/12)*modelo1.hora.hor)+(M_PI/2))+x0;
		y=r*0.4*sin(((-2*M_PI/12)*modelo1.hora.hor)+(M_PI/2))+y0;
		glVertex2f(x,y);
		glVertex2f(x0,y0);
		glEnd();
	}

	// ... definição das rotinas auxiliares de desenho ...

	// Callback de desenho

	void static Draw(void)
	{
		glClear(GL_COLOR_BUFFER_BIT);
		// ... chamada das rotinas auxiliares de desenho ...

		/*  glBegin(GL_POLYGON);
		glColor3f(1.0f, 0.0f, 0.0f);
		glVertex2f(modelo.tamLado/2,modelo.tamLado/2);
		glColor3f(0.0f, 0.0f, 1.0f);
		glVertex2f(-modelo.tamLado/2,modelo.tamLado/2);
		glColor3f(0.0f, 1.0f, 0.0f);
		glVertex2f(-modelo.tamLado/2,-modelo.tamLado/2);
		glColor3f(1.0f, 0.0f, 1.0f);
		glVertex2f(modelo.tamLado/2,-modelo.tamLado/2);
		glEnd();*/

		poligono(modelo1.numLados, 0.0, 0.0, modelo1.raio);
		mostrador(0.0, 0.0, modelo1.raio);
		ponteiros(0.0, 0.0, modelo1.raio);

		glBegin(GL_LINE_LOOP);
		glColor3f(1.0,1.0,1.0);
		glVertex2f(-1.0,-1.0);	
		glVertex2f(1.0,-1.0);	
		glVertex2f(1.0,1.0);	
		glVertex2f(-1.0,1.0);
		glEnd();

		glFlush();
		if (estado1.doubleBuffer)
			glutSwapBuffers();
	}

	/*******************************
	***   callbacks timer/idle   ***
	*******************************/

	// Callback Idle

	void Idle(void)
	{

		// accoes a tomar quando o glut estÃ¡ idle 

		// redesenhar o ecra 
		// glutPostRedisplay();
	}

	// Callback de temporizador (não colocar instruções de desenho aqui...)

	void static Timer(int value)
	{
		glutTimerFunc(estado1.delay, Timer, 0);
		// ... acções do temporizador ... 
		modelo1.hora.seg++;
		if(modelo1.hora.seg==60){
			modelo1.hora.seg=0;
			modelo1.hora.min++;
		}
		if(modelo1.hora.min==60){
			modelo1.hora.min=0;
			modelo1.hora.hor++;
		}
		if(modelo1.hora.hor==12){
			modelo1.hora.hor=0;
		}
		// redesenhar o ecrã (invoca o callback de desenho)
		glutPostRedisplay();
	}


	void imprime_ajuda(void)
	{
		printf("\n\nDesenho de um quadrado\n");
		printf("h,H - Ajuda \n");
		printf("+   - Aumentar tamanho do Lado\n");
		printf("-   - Diminuir tamanho do Lado\n");
		printf("ESC - Sair\n");
	}

	/*******************************
	***  callbacks de teclado    ***
	*******************************/

	// Callback para interacção via teclado (carregar na tecla)

	void static Key(unsigned char key, int x, int y)
	{
		switch (key) {
		case 27:  // Tecla Escape
			exit(1);
			// ... acções sobre outras teclas ... 

			//case 'h' :
			//case 'H' :
			//           imprime_ajuda();
			//      break;
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
		case '+' :
			if(modelo1.numLados<40)
			{
				modelo1.numLados++;
				glutPostRedisplay(); // redesenhar o ecrã
			}
			break;
		case '-' :
			if(modelo1.numLados>3)
			{
				modelo1.numLados--;
				glutPostRedisplay(); // redesenhar o ecrã
			}
			break;

		}

		if(DEBUG)
			printf("Carregou na tecla %c\n",key);

	}

	// Callback para interacção via teclado (largar a tecla)

	virtual void KeyUp(unsigned char key, int x, int y)
	{

		if(DEBUG)
			printf("Largou a tecla %c\n",key);
	}

	// Callback para interacção via teclas especiais  (carregar na tecla)

	virtual void SpecialKey(int key, int x, int y)
	{
		// ... accoes sobre outras teclas especiais ... 
		//    GLUT_KEY_F1 ... GLUT_KEY_F12
		//    GLUT_KEY_UP
		//    GLUT_KEY_DOWN
		//    GLUT_KEY_LEFT
		//    GLUT_KEY_RIGHT
		//    GLUT_KEY_PAGE_UP
		//    GLUT_KEY_PAGE_DOWN
		//    GLUT_KEY_HOME
		//    GLUT_KEY_END
		//    GLUT_KEY_INSERT 

		switch (key) {

			// redesenhar o ecra 
			//glutPostRedisplay();
		}


		if(DEBUG)
			printf("Carregou na tecla especial %d\n",key);
	}

	// Callback para interacção via teclas especiais (largar a tecla)

	virtual void SpecialKeyUp(int key, int x, int y)
	{

		if(DEBUG)
			printf("Largou a tecla especial %d\n",key);

	}

	void Run(){
		// colocar a GL_TRUE para ligar o Double Buffer
		estado1.doubleBuffer=GL_TRUE;
		/*glutInit(&argc, argv);
		glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
		glutCreateWindow("OpenGL");*/
		Init();
		glutReshapeFunc(Reshape);
		glutDisplayFunc(Draw);
		glutKeyboardFunc(Key);
		glutTimerFunc(estado1.delay, Timer, 0);
	}
};