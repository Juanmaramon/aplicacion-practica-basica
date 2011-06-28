#include "Game.h"
#include "..\Window\Window.h"
#include "..\DebugClass\Debug.h"
#include "..\Graphics\GraphicManager.h"
#include "InputConfiguration.h"
#include "../Input/InputManager.h"

extern tActionMapping kaActionMapping[];

//Función para inicializar el juego.
bool cGame::Init()
{
	mbFinish = false;
	//	LoadResources();
	//Se rellena la estructura de tipo cApplicationProperties: 
	mProperties.macApplicationName = "Practica Basica 1";
	mProperties.mbFullscreen = false;
	mProperties.muiBits = 16;
	mProperties.muiWidth = 640;
	mProperties.muiHeight = 480;
  
	//Se inicializa el objeto ventana con la propiedades establecidas:
    bool lbResult = cWindow::Get().Init( mProperties );
	
	//Se inicializa la clase que encapsula las operaciones de OpenGL:
	if ( lbResult )
	{
		lbResult = cGraphicManager::Get().Init( &cWindow::Get() );

		if ( lbResult )
		{
			// Init Camera 3D	
			m3DCamera.Init();
			float lfAspect = (float)mProperties.muiWidth/(float)mProperties.muiHeight;
			m3DCamera.SetPerspective(45.0f, lfAspect,0.1f,100.0f);
			m3DCamera.SetLookAt( cVec3(5.0f, 5.f, 5.f), cVec3(0.0f, 0.f, 0.f), cVec3(0.0f, 1.f, 0.f));	
			// Init Input Manager
			cInputManager::Get().Init( kaActionMapping, eIA_Count );
		}
		//Si algo falla se libera la ventana:
		else
		{
			cWindow::Get().Deinit();
		}
	}

    	return lbResult;	
}

//Función para actualizar el juego.
void cGame::Update( float lfTimestep )
{
	//Se actualiza la ventana:
	cWindow::Get().Update();

	// Update of input 
	cInputManager::Get().Update(lfTimestep);

	//Se comprueba si hay que cerrar la aplicación, por ejemplo a causa de 
	// que el usuario haya cerrado la ventana. Si es así, se cambia el booleano
	// que controla el cierre de la aplicación:
	mbFinish = mbFinish || cWindow::Get().GetCloseApplication() || IsPressed(eIA_CloseApplication);
	if ( mbFinish )
	{
		return;
	}
}

//Función para renderizar el juego:
void cGame::Render()
{
	//Se limpian los búferes de color:
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);           
    glLoadIdentity();
    
	//Se utiliza la clase cDebug para mostrar el mensaje:
	cDebug lDebug;
	lDebug.Init("\n-Render\n");
	//El operador de flujo << está sobrecargado en cDebug.cpp.
	cout<<lDebug;	

	// Activate the 3D Camera
	cGraphicManager::Get().ActivateCamera( &m3DCamera );
	// Set the world matrix
	cMatrix lWorld;
	lWorld.LoadIdentity();
	cGraphicManager::Get().SetWorldMatrix(lWorld);
	// Render the debug lines
	cGraphicManager::Get().DrawGrid();
	cGraphicManager::Get().DrawAxis();
	// Render primitives
	cGraphicManager::Get().DrawPoint( cVec3(1.5f, 0.0f, 1.5f), cVec3(1.0f, 0.0f, 1.0f) );
	cGraphicManager::Get().DrawLine( cVec3(-1.5f, 0.0f, -1.5f), cVec3(-1.5f, 0.0f, 1.5f), cVec3(1.0f, 1.0f, 0.0f) );

	lWorld.LoadTranslation(cVec3(1,0,-1.5));
	cMatrix lRot;
	lRot.LoadRotation(cVec3(0.0f,1.0f,0.0f), 3.14f / 2.0f );
	cGraphicManager::Get().SetWorldMatrix(lRot * lWorld);
	// Render the debug lines
	cGraphicManager::Get().DrawAxis();

    cGraphicManager::Get().SwapBuffer();	
}

//Función para cargar los recursos necesarios para el juego.
bool cGame::LoadResources( void )
{
   return true;
}

//Función para finalizar el juego.
bool cGame::Deinit()
{
	//Se deinicializa en el orden inverso a la inicialización:

	// Free of input controls
	cInputManager::Get().Deinit();
	//Se libera OpenGL (clase cGraphicManager):
	bool lbResult = cGraphicManager::Get().Deinit();
	//Se libera la ventana:
	lbResult = lbResult && cWindow::Get().Deinit();
	return lbResult;	
}
