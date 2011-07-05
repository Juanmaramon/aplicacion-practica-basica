//Clase que encapsular� en la medida de lo posible todas las operaciones 
// relacionadas con OpenGL.

#ifndef GraphicManager_H
#define GraphicManager_H

#include "..\Utility\Singleton.h"
#include "GLHeaders.h"
#include "..\Window\Window.h"
#include "..\MathLib\MathLib.h"
#include "cCamera.h"

class cWindow;
class cGraphicManager : public cSingleton<cGraphicManager>
{
   public:
	  //Funci�n que se encarga de la inicializaci�n de OpenGL.
	  //Recibe la ventana sobre la que OpenGL har� el render.
      bool Init( cWindow * lpWindow );

	  //Funci�n que se encarga de la liberaci�n de OpenGL. 
      bool Deinit();

	  //Point render function
	  void DrawPoint( const cVec3 &lvPosition, const cVec3 &lvColor );

	  //Line render function
	  void DrawLine( const cVec3 &lvPosition1, const cVec3 &lvPosition2, const cVec3 &lvColor );

	  //Grid render function
	  void DrawGrid();

	  //Axis render function
	  void DrawAxis();

	  //Funci�n que se encarga de intercambiar el backbuffer con el frontbuffer.
      void SwapBuffer();

	  friend class cSingleton<cGraphicManager>;

	  //Sets current camera
	  void ActivateCamera( cCamera * lpCamera );

	   //Set world matrix
	   void SetWorldMatrix( const cMatrix &lMatrix );

   protected:
      cGraphicManager() { ; } // Protected constructor.

	  cWindow*    mpWindow; // Puntero a la ventana en la que se debe renderizar.
	  GLuint      mPixelFormat; // Formato de pixel.
      HGLRC       mHRC; // Handle  al contexto de renderizado de OpenGL.

   private:
	   //Funci�n que crea el contexto de renderizado.
	   bool CreateContext( cWindow * lpWindow );

	   //Funci�n que inicializa el estado de OpenGL.
	   void InitializeGLState();

	   //Current camera pointer
	   cCamera * mpActiveCamera;
	   //World matrix
	   cMatrix mWorldMatrix;

	   //Updates Model-view matrix
	   void RefreshWorldView();

};

#endif