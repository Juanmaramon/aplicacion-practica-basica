#ifndef Game_H
#define Game_H

#include "..\Utility\Singleton.h"
#include "..\Window\ApplicationProperties.h"
#include "..\Graphics\cCamera.h"
#include "..\Graphics\Fonts\acgfx_font.h"

//Clase que hace uso del Patrón Singleton definido en Singleton.h, para iniciar, actualizar, dibujar
// y finalizar el juego
class cGame : public cSingleton<cGame>
{
	friend class cSingleton<cGame>;
	protected:
		cGame() { ; } // Protected constructor	
		//Variable privada para gestionar si tenemos que salir de la aplicación.
		bool mbFinish;
		//Clase para los atributos de la ventana (cWindow) que se creará en el método Init.
		cApplicationProperties mProperties;
		//Scene 3D camera 
		cCamera m3DCamera;
		//Scene 2D camera 
		cCamera m2DCamera;
		//Font support
		cFont mFont;

	public:
	
	//Función para inicializar el juego	
	bool Init();

	//Función para actualizar el juego
	void Update( float lfTimestep );

	//Función para renderizar el juego
	void Render();

	//Función para finalizar el juego
	bool Deinit();

	//Función que devuelve el valor de mbFinish, para chequear el final del juego.
	inline bool HasFinished() { return mbFinish; }

	//Función para cargar los recursos necesarios para el juego.
	bool LoadResources( void );
};

#endif