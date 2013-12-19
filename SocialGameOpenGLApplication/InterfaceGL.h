#pragma once
#include "SceneInterface.h"
#ifndef M_PI
#define M_PI 3.1415926535897932384626433832795
#endif

#define RAD(x)          (M_PI*(x)/180)
#define GRAUS(x)        (180*(x)/M_PI)

class InterfaceGL{
public:
	// Inicializa��o do ambiente OPENGL
	virtual void Init(void){}

	// Callback de temporizador
	virtual void Timer(int value){}

	// Callback para redimensionar a janela
	virtual void Reshape(int width, int height){}

	// Callback de desenho
	virtual void Draw(void){}

	// Substitui o que definimos na main
	virtual void Run(int argc, char **argv, InterfaceScene *){}

	// Callback para interac��o via teclado (carregar na tecla)
	virtual void Key(unsigned char key, int x, int y){}

	// Callback para interac��o via teclado (largar a tecla)
	virtual void KeyUp(unsigned char key, int x, int y){}

	// Callback para interac��o via teclas especiais  (carregar na tecla)
	virtual void SpecialKey(int key, int x, int y){}

	// Callback para interac��o via teclas especiais (largar a tecla)
	virtual void SpecialKeyUp(int key, int x, int y){}

	// Callback para interac��o do rato
	virtual void Mouse(int btn, int state, int x, int y){}
};