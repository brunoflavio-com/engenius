
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
}Estado;


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
}Modelo;

Estado estado;
Modelo modelo;

class Cubo : public InterfaceGL{
public:
	Cubo(){}
	void static change(){
		InterfaceGL * change;
		//glutReshapeFunc(NULL);
		//glutDisplayFunc(NULL);
		//glutTimerFunc(1, NULL, 0);
		change = new Teste2();
		change->Reshape(300,300);
		glutPostRedisplay();
		change->Run();
		glutPostRedisplay();
		glutMainLoop();
	}
/* Inicialização do ambiente OPENGL */
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

/**************************************
***  callbacks de janela/desenho    ***
**************************************/

/* CALLBACK PARA REDIMENSIONAR JANELA */
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


/* ... definicao das rotinas auxiliares de desenho ... */

void static desenhaPoligono(GLfloat a[], GLfloat b[], GLfloat c[], GLfloat  d[], GLfloat cor[])
{

  /* draw a polygon via list of vertices */

  glBegin(GL_POLYGON);
    glColor3fv(cor);
    glVertex3fv(a);
    glVertex3fv(b);
    glVertex3fv(c);
    glVertex3fv(d);
  glEnd();
}

void static eixos(){
	glBegin(GL_LINES);
	glColor3f(1.0f, 0.0f, 0.0f);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glVertex3f(4.0f, 0.0f, 0.0f);

	glColor3f(0.0f, 1.0f, 0.0f);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glVertex3f(0.0f, 4.0f, 0.0f);

	glColor3f(0.0f, 0.0f, 1.0f);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glVertex3f(0.0f, 0.0f, 4.0f);
	glEnd();
}

void static cubol(){
	GLfloat vertices[][3] = {{-0.5,-0.5,-0.5}, 
                          {0.5,-0.5,-0.5}, 
                          {0.5,0.5,-0.5}, 
						  {-0.5,0.5,-0.5}};

	GLfloat cores[][3] = {{0.0,1.0,1.0},
                        {1.0,0.0,0.0},
                        {1.0,1.0,0.0}, 
                        {0.0,1.0,0.0}, 
                        {1.0,0.0,1.0}, 
                        {0.0,0.0,1.0}, 
                        {1.0,1.0,1.0}};

	desenhaPoligono(vertices[1],vertices[0],vertices[3],vertices[2],cores[0]);
	glRotatef(90.0f,0,1,0);
	desenhaPoligono(vertices[1],vertices[0],vertices[3],vertices[2],cores[1]);
	glRotatef(90.0f,0,1,0);
	desenhaPoligono(vertices[1],vertices[0],vertices[3],vertices[2],cores[2]);
	glRotatef(90.0f,0,1,0);
	desenhaPoligono(vertices[1],vertices[0],vertices[3],vertices[2],cores[3]);
	glRotatef(90.0f,1,0,0);
	desenhaPoligono(vertices[1],vertices[0],vertices[3],vertices[2],cores[4]);
	glRotatef(180.0f,1,0,0);
	desenhaPoligono(vertices[1],vertices[0],vertices[3],vertices[2],cores[5]);
}

void static cubo()
{
 GLfloat vertices[][3] = {{-0.5,-0.5,-0.5}, 
                          {0.5,-0.5,-0.5}, 
                          {0.5,0.5,-0.5}, 
                          {-0.5,0.5,-0.5},
						  {-0.5,-0.5,0.5}, 
                          {0.5,-0.5,0.5}, 
                          {0.5,0.5,0.5}, 
                          {-0.5,0.5,0.5}};

  GLfloat cores[][3] = {{0.0,1.0,1.0},
                        {1.0,0.0,0.0},
                        {1.0,1.0,0.0}, 
                        {0.0,1.0,0.0}, 
                        {1.0,0.0,1.0}, 
                        {0.0,0.0,1.0}, 
                        {1.0,1.0,1.0}};

  desenhaPoligono(vertices[1],vertices[0],vertices[3],vertices[2],cores[0]);
  desenhaPoligono(vertices[4],vertices[5],vertices[6],vertices[7],cores[1]);
  desenhaPoligono(vertices[1],vertices[2],vertices[6],vertices[5],cores[2]);
  desenhaPoligono(vertices[0],vertices[4],vertices[7],vertices[3],cores[3]);
  desenhaPoligono(vertices[2],vertices[3],vertices[7],vertices[6],cores[4]);
  desenhaPoligono(vertices[0],vertices[1],vertices[5],vertices[4],cores[5]);
  
}


/* Callback de desenho */
void static Draw(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
/* ... chamada das rotinas auxiliares de desenho ... */

  glPushMatrix();
    glRotatef(modelo.theta[0],1,0,0);
    glRotatef(modelo.theta[1],0,1,0);
    glRotatef(modelo.theta[2],0,0,1);
    glScalef(modelo.ladoCubo,modelo.ladoCubo,modelo.ladoCubo);
    cubo();
	//eixos principais
	eixos();
	glPushMatrix();

	//cubos pequenos
	glTranslatef(0.0f, 0.0f, modelo.translacaoCubo);
	glRotatef(modelo.thetaCubo,0,0,1);
	glScalef(0.3f, 0.3f, 0.3f);
	cubo();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.0f, modelo.translacaoCubo, 0.0f);
	glScalef(0.3f, 0.3f, 0.3f);
	glRotatef(modelo.thetaCubo,0,1,0);
	cubo();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(modelo.translacaoCubo, 0.0f, 0.0f);
	glScalef(0.3f, 0.3f, 0.3f);
	glRotatef(modelo.thetaCubo,1,0,0);
	cubo();
	glPopMatrix();

	//uso do cubol
  glPushMatrix();
  glTranslatef(4.0f, 4.0f, 0.0f);
  cubol();
  glPopMatrix();
	
  glPopMatrix();

  //eixos pequenos
  glPushMatrix();
  glTranslatef(-4.0f, -4.0f, 0.0f);
  glRotatef(modelo.theta[0],1,0,0);
  glRotatef(modelo.theta[1],0,1,0);
  glRotatef(modelo.theta[2],0,0,1);
  glScalef(0.2f, 0.2f, 0.2f);
  eixos();
  glPopMatrix();

  

  if (estado.doubleBuffer)
    glutSwapBuffers();
  else
    glFlush();
  
}

/*******************************
***   callbacks timer   ***
*******************************/
/* Callback de temporizador */
void static Timer(int value)
{

  glutTimerFunc(estado.delayMovimento, Timer, 0);
  /* ... accoes do temporizador não colocar aqui transformações, alterar
     somente os valores das variáveis ... */
  if(estado.movimentoTranslacao==true){
	  if(modelo.translacaoCubo >= 4.0 && modelo.sentidoTranslacao){
		  modelo.sentidoTranslacao=false;
		  
	  }
	  else if(modelo.translacaoCubo <= 0.7 && !modelo.sentidoTranslacao){
		modelo.sentidoTranslacao=true;
	  }
	  if(modelo.sentidoTranslacao){
		  modelo.translacaoCubo+=0.1;
	  }
	  else{
		  modelo.translacaoCubo-=0.1;
		  modelo.thetaCubo+=4;
	  }
  }
  // alterar o modelo.theta[] usando a variável modelo.eixoRodar como indice
  if(modelo.eixoRodar!=-1){
	modelo.theta[modelo.eixoRodar]+=10;
  }
  /* redesenhar o ecrã */
  glutPostRedisplay();
}


/*******************************
***  callbacks de teclado    ***
*******************************/

void static imprime_ajuda(void)
{
  printf("\n\nDesenho de um quadrado\n");
  printf("h,H - Ajuda \n");
  printf("F1  - Reiniciar \n");
  printf("F2  - Poligono Fill \n");
  printf("F3  - Poligono Line \n");
  printf("F4  - Poligono Point \n");
  printf("+   - Aumentar tamanho dos Cubos\n");
  printf("-   - Diminuir tamanho dos Cubos\n");
  printf("i,I - Reiniciar Variáveis\n");
  printf("p,p - Iniciar/Parar movimento dos cubinhos\n");
  printf("ESC - Sair\n");
  printf("teclas do rato para iniciar/parar rotação e alternar eixos\n");

}


/* Callback para interaccao via teclado (carregar na tecla) */
void static Key(unsigned char key, int x, int y)
{
  switch (key) {
    case 27:
      exit(1);
    /* ... accoes sobre outras teclas ... */

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

		  case 'q' :
    case 'Q' :
		change();
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
            //estado.movimentoTranslacao=!estado.movimentoTranslacao;
          break;

  }
  
  if(DEBUG)
    printf("Carregou na tecla %c\n",key);

}

/* Callback para interaccao via teclado (largar a tecla) */
void KeyUp(unsigned char key, int x, int y)
{

  if(DEBUG)
    printf("Largou a tecla %c\n",key);
}

/* Callback para interaccao via teclas especiais  (carregar na tecla) */
void static SpecialKey(int key, int x, int y)
{
  /* ... accoes sobre outras teclas especiais ... 
     GLUT_KEY_F1 ... GLUT_KEY_F12
     GLUT_KEY_UP
     GLUT_KEY_DOWN
     GLUT_KEY_LEFT
     GLUT_KEY_RIGHT
     GLUT_KEY_PAGE_UP
     GLUT_KEY_PAGE_DOWN
     GLUT_KEY_HOME
     GLUT_KEY_END
     GLUT_KEY_INSERT 
  */

  switch (key) {

  /* redesenhar o ecra */
  //glutPostRedisplay();
      case GLUT_KEY_F1 :
            inicia_modelo();
            glutPostRedisplay();
        break;

  }


  if(DEBUG)
    printf("Carregou na tecla especial %d\n",key);
}

/* Callback para interaccao via teclas especiais (largar na tecla) */
void static SpecialKeyUp(int key, int x, int y)
{

  if(DEBUG)
    printf("Largou a tecla especial %d\n",key);

}

/*******************************
***  callbacks do rato       ***
*******************************/

void MouseMotion(int x, int y)
{
    /* x,y    => coordenadas do ponteiro quando se move no rato
                 a carregar em teclas
    */

  if(DEBUG)
    printf("Mouse Motion %d %d\n",x,y);

}

void MousePassiveMotion(int x, int y)
{
    /* x,y    => coordenadas do ponteiro quando se move no rato
                 sem estar a carregar em teclas
    */

  if(DEBUG)
    printf("Mouse Passive Motion %d %d\n",x,y);

}

void static Mouse(int button, int state, int x, int y)
{
  /* button => GLUT_LEFT_BUTTON, GLUT_MIDDLE_BUTTON, GLUT_RIGHT_BUTTON
     state  => GLUT_UP, GLUT_DOWN
     x,y    => coordenadas do ponteiro quando se carrega numa tecla do rato
  */

  // alterar o eixo que roda (variável modelo.eixoRodar)

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
  //char str[]=" makefile MAKEFILE Makefile ";

  estado.doubleBuffer=1;
  Init();
  imprime_ajuda();
/* Registar callbacks do GLUT */
  
  /* callbacks de janelas/desenho */
  glutReshapeFunc(Reshape);
  glutDisplayFunc(Draw);

  /* Callbacks de teclado */
  glutKeyboardFunc(Key);
  //glutKeyboardUpFunc(KeyUp);
  glutSpecialFunc(SpecialKey);
  //glutSpecialUpFunc(SpecialKeyUp);

  /* callbacks rato */
  //glutPassiveMotionFunc(MousePassiveMotion);
  //glutMotionFunc(MouseMotion);
  glutMouseFunc(Mouse);

  /* callbacks timer/idle */
  glutTimerFunc(estado.delayMovimento, Timer, 0);
  //glutIdleFunc(Idle);

  
  /* COMECAR... */
  //glutMainLoop();
}
};