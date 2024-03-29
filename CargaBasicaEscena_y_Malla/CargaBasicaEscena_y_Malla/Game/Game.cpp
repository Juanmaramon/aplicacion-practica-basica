#include "Game.h"
#include "..\Window\Window.h"
#include "..\DebugClass\Debug.h"
#include "..\Graphics\GraphicManager.h"
#include "..\Input\InputConfiguration.h"
#include "..\Input\InputManager.h"
#include "..\Graphics\Textures\TextureManager.h" 
#include "..\Graphics\Meshes\MeshManager.h"
#include "..\Gameplay\Scene\Scene.h"
#include "..\Gameplay\Scene\SceneManager.h"


//Para configurar el InputManager hay que llamar a su Init (en cGame::Init)
//pas�ndole la tabla kaActionMapping (de InputConfiguration.cpp).
extern tActionMapping kaActionMapping[];


//Funci�n para inicializar el juego.
bool cGame::Init()
{	
	mbFinish = false;
	//	LoadResources();
	//Se rellena la estructura de tipo cApplicationProperties: 
	mProperties.macApplicationName = "Pr�ctica 3: Carga B�sica de Escena y Malla";
	mProperties.mbFullscreen = false;
	mProperties.muiBits = 16;
	mProperties.muiWidth = 640;
	mProperties.muiHeight = 480;	
	
	//Se inicializa el objeto ventana con la propiedades establecidas:
    bool lbResult = cWindow::Get().Init( mProperties );
		
	if ( lbResult )
	{
		//Se inicializa la clase que encapsula las operaciones de OpenGL:
		lbResult = cGraphicManager::Get().Init( &cWindow::Get() );   
		if (lbResult)
		{
			// Init Camera 3D
			m3DCamera.Init();  
			float lfAspect = (float)mProperties.muiWidth/(float)mProperties.muiHeight;
			m3DCamera.SetPerspective(45.0f, lfAspect,0.1f,100.0f);
			//Se pone la c�mara en la posici�n (5,5,5) de nuestro mundo,
			// apuntando al origen del mismo, e indicando que el vector UP de la c�mara apunta hacia arriba.
			//m3DCamera.SetLookAt( cVec3(5.0f, 5.f, 5.f), cVec3(0.0f, 0.f, 0.f), cVec3(0.0f, 1.f, 0.f) );		

			//Se aleja la c�mara para ver bien la escena que vamos a cargar posteriormente.
			m3DCamera.SetLookAt( cVec3(20.0f, 15.f, 15.f),cVec3(0.0f, 0.f, 0.f), cVec3(0.0f, 1.f, 0.f) );

			//Se inicializa la clase cInputManager que representa el gestor de entrada (keyboard, gamepad, mouse, ...).
			//Se le pasa la tabla "kaActionMapping" (de InputConfiguration.cpp) que indica la relaci�n entre las acciones y los dispositivos.
			//Tambi�n se pasa "eIA_Count" (de InputConfiguration.h) que indica cuantas acciones de entrada hay.
			cInputManager::Get().Init( kaActionMapping, eIA_Count );

			//Se inicializa la clase que gestiona la texturas indicando que habr� 1, por ejemplo.
			cTextureManager::Get().Init(1);

			//Init Camera 2D, para las cadenas de texto.
			//Se inicializa la c�mara 2D con una perspectiva ortogonal.
			//El (0,0) est� situado en el centro de la pantalla y las dimensiones est�n 
			// establecidas en p�xeles.
			float lfRight = (float)mProperties.muiWidth / 2.0f;
			float lfLeft = -lfRight;
			float lfTop = (float)mProperties.muiHeight / 2.0f;
			float lfBottom = -lfTop;
			m2DCamera.Init();
			m2DCamera.SetOrtho(lfLeft, lfRight, lfBottom, lfTop, 0.1f, 100.0f);
			//Se pone la c�mara2D en la posici�n (0,0) de nuestro mundo,
			// apuntando al origen del mismo, e indicando que el vector UP de la c�mara apunta hacia arriba.
			m2DCamera.SetLookAt( cVec3(0.0f, 0.0f, 1.f), cVec3(0.0f, 0.f, 0.f), cVec3(0.0f, 1.f, 0.f) );

			// Init the Font.
			mFont.Init("./Data/Fonts/Test1.fnt");

			//Se inicializa el gestor de mallas: habr� 4 mallas en la escena (mirar ./Data/Scene/).
			cMeshManager::Get().Init(4);

			//Se inicializa el gestor de escenas.
			cSceneManager::Get().Init(1);         

			//Se carga la escena.
			mScene = cSceneManager::Get().LoadResource( "TestLevel", "./Data/Scene/dragonsmall.DAE" ); 			
		}		
		else
		{
			//Si algo falla se libera la ventana.
			cWindow::Get().Deinit();
		}
	}
    return lbResult;	
}

//Funci�n para actualizar el juego.
void cGame::Update( float lfTimestep )
{
	//Se actualiza la ventana:
	cWindow::Get().Update();

	//Se actualiza el InputManager.
	cInputManager::Get().Update(lfTimestep);		
	
	//Se comprueba si hay que cerrar la aplicaci�n, por ejemplo a causa de 
	// que el usuario haya cerrado la ventana. 
	mbFinish = mbFinish || cWindow::Get().GetCloseApplication()
		         //Tambi�n se verifica si se ha producido la acci�n de entrada que cierra la aplicaci�n:
				 // Pulsar la tecla ESC del teclado, el bot�n 1 del JoyStick o el bot�n central del rat�n.
	             || IsPressed(eIA_CloseApplication);
	//Si es as�, se cambia el booleano
	// que controla el cierre de la aplicaci�n.

	if ( mbFinish )
	{
		return;
	}	
}

//Funci�n para renderizar el juego:
void cGame::Render()
{
	/* Orden de las instrucciones
	�    Limpiado de Buffers
	�    Activaci�n de C�mara 3D
	�    Renderizado de Geometr�a 3D s�lida
	�    Renderizado de Geometr�a 3D con transparencia
	�    Activaci�n de C�mara 2D
	�    Renderizado de C�mara 2D
	�    Effectos de postprocesado
	�    Intercambio de los bufferes
	*/

	// 1) Limpiado de Buffers
	// -------------------------------------------------------------
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);        
	 
	// 2) Activaci�n de C�mara 3D
	// -------------------------------------------------------------
	cGraphicManager::Get().ActivateCamera( &m3DCamera );
	 
	// 3) Renderizado de Geometr�a 3D s�lida
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
	cGraphicManager::Get().DrawLine( cVec3(-1.5f, 0.0f, -1.5f), cVec3(-1.5f, 0.0f, 1.5f), cVec3(1.0f, 1.0f, 0.0f) );

	//Desactivamos la textura porque a�n no tenemos materiales asignados a las mallas de la escena.
	glDisable(GL_TEXTURE_2D);
	//Para renderizar la escena llamaremos al render de la escena a trav�s de mScene (manejador de la escena, de tipo cResourceHandle).
	((cScene *)mScene.GetResource())->Render();
	glEnable(GL_TEXTURE_2D);
	 
	// 4) Renderizado de Geometr�a 3D con transparencia
	// -------------------------------------------------------------
	 
	// 5) Activaci�n de C�mara 2D  
	// -------------------------------------------------------------
	cGraphicManager::Get().ActivateCamera( &m2DCamera );
	 
	// 6) Renderizado de C�mara 2D
	// -------------------------------------------------------------
	//Se dibujan algunas cadenas de texto.
	mFont.SetColour( 1.0f, 0.0f, 0.0f );
	mFont.Write(0,200,0, "A�o Tot� ping�ino() �!�?", 0, FONT_ALIGN_CENTER);
	 
	mFont.SetColour( 0.0f, 1.0f, 1.0f );
	mFont.WriteBox(100,100,0,100, "Esto es un test \nmultilinea", 0, FONT_ALIGN_CENTER);	


	 
	// 7) Efectos de postprocesado
	// -------------------------------------------------------------
	 
	// 8) Intercambio de los bufferes
	// -------------------------------------------------------------
	cGraphicManager::Get().SwapBuffer();
	
	
			
	/*
  
    C�digo que se ejecutaba anteriormente:   

	//Se limpian los b�feres de color:
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);           
    glLoadIdentity();
    
	//Se utiliza la clase cDebug para mostrar el mensaje:
	cDebug lDebug;
	lDebug.Init("\n-Render\n");
	//El operador de flujo << est� sobrecargado en cDebug.cpp.
	cout<<lDebug;	

	//La c�mara por defecto est� en el 0,0,0 del mundo 
	// mirando hacia el eje negativo de Z. 

	// Activate the 3D Camera
	cGraphicManager::Get().ActivateCamera( &m3DCamera );
 
	// Set the world matrix
	cMatrix lWorld;
	lWorld.LoadIdentity();
	cGraphicManager::Get().SetWorldMatrix(lWorld);
 
	// Render the debug lines
	cGraphicManager::Get().DrawGrid();
	cGraphicManager::Get().DrawAxis();
   
	//Creamos un punto en el (1.5,0,1.5). El segundo vector es para el color:
	cGraphicManager::Get().DrawPoint( cVec3(1.5f, 0.0f, 1.5f), cVec3(1.0f, 0.0f, 1.0f) );
	//Creamos una l�nea que una los puntos (-1.5, 0, -1.5) y (-1.5, 0, 1.5). El tercer vector es para el color:
	cGraphicManager::Get().DrawLine(  cVec3(-1.5f, 0.0f, -1.5f), cVec3(-1.5f, 0.0f, 1.5f), cVec3(1.0f, 1.0f, 0.0f) ); 
    
    //Se aplica una matriz de mundo distinta: se realiza una rotaci�n y una translaci�n
	// componiendo dos matrices de transformaci�n y multiplic�ndolas. Se a�ande otro eje
	// de coordenadas (a) para que se vean esos cambios:

	lWorld.LoadTranslation(cVec3(1,0,-1.5));
	cMatrix lRot;
	lRot.LoadRotation(cVec3(0.0f,1.0f,0.0f), 3.14f / 2.0f );
	cGraphicManager::Get().SetWorldMatrix(lRot * lWorld);    
 
	// Render the debug lines
	cGraphicManager::Get().DrawGrid();
	cGraphicManager::Get().DrawAxis(); //(a)

    cGraphicManager::Get().SwapBuffer();

	*/




}

//Funci�n para cargar los recursos necesarios para el juego.
bool cGame::LoadResources( void )
{
   return true;
}

//Funci�n para finalizar el juego.
bool cGame::Deinit()
{
	//Se deinicializa en el orden inverso a la inicializaci�n:

	//Se libera el manejador de escenas.
	cSceneManager::Get().Deinit();

	//Se libera el manejador de mallas.
	cMeshManager::Get().Deinit();

	//Se libera la clase fuente.
	mFont.Deinit();
    //Se libera el gestor de texturas.
	cTextureManager::Get().Deinit();    
	//Se libera el InputManager:
	cInputManager::Get().Deinit();
	//Se libera OpenGL (clase cGraphicManager):
	bool lbResult = cGraphicManager::Get().Deinit();
	//Se libera la ventana:
	lbResult = lbResult && cWindow::Get().Deinit();
	return lbResult;	
}