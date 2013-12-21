#pragma once

class InterfaceScene
{
public:

	// Initiate scene
	virtual void Init(void) = 0;

	// Callback de temporizador
	virtual void Timer(int value) = 0;

	// Callback de desenho
	virtual void Draw(void) = 0;

	// Callback para interacção via teclado (carregar na tecla)
	virtual void Key(unsigned char key, int x, int y) = 0;

	// Callback para interacção via teclas especiais  (carregar na tecla)
	virtual void SpecialKey(int key, int x, int y) = 0;

	// Callback para interacção via teclas especiais (largar a tecla)
	virtual void SpecialKeyUp(int key, int x, int y) = 0;

	// Callback para interacção do rato
	virtual void Mouse(int btn, int state, int x, int y) = 0;
	virtual	void MotionMouse(int x, int y) = 0;
	


};
