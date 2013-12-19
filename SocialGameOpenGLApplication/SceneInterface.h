#pragma once

class InterfaceScene
{
public:
	virtual void Draw(void) = 0;

	virtual void Key(unsigned char key, int x, int y) {}

	// Callback para interac��o via teclado (largar a tecla)
	virtual void KeyUp(unsigned char key, int x, int y){}

	// Callback para interac��o via teclas especiais  (carregar na tecla)
	virtual void SpecialKey(int key, int x, int y) {}

	// Callback para interac��o via teclas especiais (largar a tecla)
	virtual void SpecialKeyUp(int key, int x, int y) {}

	// Callback para interac��o do rato
	virtual void Mouse(int btn, int state, int x, int y) {}


};
