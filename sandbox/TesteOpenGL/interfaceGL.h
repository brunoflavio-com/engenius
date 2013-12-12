class InterfaceGL{
public:
	// Inicialização do ambiente OPENGL
	virtual void Init(void){}

	// Callback de temporizador
	virtual void Timer(int value){}

	// Callback para redimensionar a janela
	virtual void Reshape(int width, int height){}

	// Callback de desenho
	virtual void Draw(void){}

	// Substitui o que definimos na main
	virtual void Run(int argc, char **argv){}

	// Callback para interacção via teclado (carregar na tecla)
	virtual void Key(unsigned char key, int x, int y){}

	// Callback para interacção via teclado (largar a tecla)
	virtual void KeyUp(unsigned char key, int x, int y){}

	// Callback para interacção via teclas especiais  (carregar na tecla)
	virtual void SpecialKey(int key, int x, int y){}

	// Callback para interacção via teclas especiais (largar a tecla)
	virtual void SpecialKeyUp(int key, int x, int y){}

	// Callback para interacção do rato
	virtual void Mouse(int btn, int state, int x, int y){} 
};