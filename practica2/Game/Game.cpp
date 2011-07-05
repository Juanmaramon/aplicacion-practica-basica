#include "Game.h"
#include "..\Window\Window.h"
#include "..\DebugClass\Debug.h"
#include "..\Graphics\GraphicManager.h"
#include "InputConfiguration.h"
#include "../Input/InputManager.h"
#include "../Graphics/Textures/TextureManager.h"

extern tActionMapping kaActionMapping[];

//Función para inicializar el juego.
bool cGame::Init()
{
	mbFinish = false;
	//	LoadResources();
	//Se rellena la estructura de tipo cApplicationProperties: 
	mProperties.macApplicationName = "Practica Basica 2";
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

			// Init Input Manager
			cInputManager::Get().Init( kaActionMapping, eIA_Count );
			// Init Texture Manager
			cTextureManager::Get().Init(1);
			// Init the Font
			mFont.Init("./Data/Fonts/Test1.fnt");
			// Init Camera 3D	
			m3DCamera.Init();
			float lfAspect = (float)mProperties.muiWidth/(float)mProperties.muiHeight;
			m3DCamera.SetPerspective(45.0f, lfAspect,0.1f,100.0f);
			m3DCamera.SetLookAt( cVec3(5.0f, 5.f, 5.f), cVec3(0.0f, 0.f, 0.f), cVec3(0.0f, 1.f, 0.f));	
			// Init Camera 2D
			float lfRight = (float)mProperties.muiWidth / 2.0f;
			float lfLeft = -lfRight;
			float lfTop = (float)mProperties.muiHeight / 2.0f;
			float lfBottom = -lfTop;
			m2DCamera.Init();
			m2DCamera.SetOrtho(lfLeft, lfRight, lfBottom, lfTop, 0.1f, 100.0f);
			m2DCamera.SetLookAt( cVec3(0.0f, 0.0f, 1.f), cVec3(0.0f, 0.f, 0.f), cVec3(0.f, 1.f, 0.f) );
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
	// 1) Clean Buffers
	// -------------------------------------------------------------
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	// 2) Activate the 3D Camera
	// -------------------------------------------------------------
	cGraphicManager::Get().ActivateCamera( &m3DCamera );
	// 3) Render Solid 3D
	// -------------------------------------------------------------
	// Set the world matrix
	cMatrix lWorld;
	lWorld.LoadIdentity();
	cGraphicManager::Get().SetWorldMatrix(lWorld);
	// Render the debug lines
	cGraphicManager::Get().DrawGrid();
	cGraphicManager::Get().DrawAxis();
	cGraphicManager::Get().DrawPoint( cVec3(1.5f, 0.0f, 1.5f),
	cVec3(1.0f, 0.0f, 1.0f) );
	cGraphicManager::Get().DrawLine( cVec3(-1.5f, 0.0f, -1.5f),
	cVec3(-1.5f, 0.0f, 1.5f),
	cVec3(1.0f, 1.0f, 0.0f) );
	// 4) Render 3D with transparency
	// -------------------------------------------------------------
	// 5) Activate 2D Camera
	// -------------------------------------------------------------
	cGraphicManager::Get().ActivateCamera( &m2DCamera );
	// 6) Render 2D Elements
	// -------------------------------------------------------------
	//Draw some strings
	mFont.SetColour( 1.0f, 0.0f, 0.0f );
	mFont.Write(0,200,0, "Año Totó pingüino() ¡!¿?", 0,
	FONT_ALIGN_CENTER);
	mFont.SetColour( 0.0f, 1.0f, 1.0f );
	mFont.WriteBox(100,100,0,100, "Esto es un test \nmultilinea", 0,
	FONT_ALIGN_CENTER);
	// 7) Postprocessing
	// -------------------------------------------------------------
	// 8) Swap Buffers
	// -------------------------------------------------------------
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

	// Font Deinit
	mFont.Deinit();
	// Free texture manager
	cTextureManager::Get().Deinit();
	// Free of input controls
	cInputManager::Get().Deinit();
	//Se libera OpenGL (clase cGraphicManager):
	bool lbResult = cGraphicManager::Get().Deinit();
	//Se libera la ventana:
	lbResult = lbResult && cWindow::Get().Deinit();
	return lbResult;	
}
