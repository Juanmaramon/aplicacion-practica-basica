
#include "GraphicManager.h"
#include <assert.h>

//Funci�n que se encarga de la inicializaci�n de OpenGL.
//Recibe la ventana sobre la que OpenGL har� el render.
bool cGraphicManager::Init( cWindow * lpWindow )
{
   //Se crear el contexto de renderizado:
   bool lbRet = CreateContext( lpWindow );
   if ( lbRet )
   {
      //Se establece el estado de OpenGL:
      InitializeGLState();
   }

   return lbRet;
}

//Funci�n que crea el contexto de renderizado.
//Cada vez que se produce un error, se llama a la funci�n Deinit 
// para liberar aquellos recursos que se hayan solicitado previamente.
bool cGraphicManager::CreateContext( cWindow * lpWindow )
{   
   assert(lpWindow);
   //Se rellena en una estructura las caracter�sticas que tendr�n los buffers de 
   // v�deo:
   static   PIXELFORMATDESCRIPTOR lPfp=                    
   {
      sizeof(PIXELFORMATDESCRIPTOR),
      1,
      PFD_DRAW_TO_WINDOW |
      PFD_SUPPORT_OPENGL |
      PFD_DOUBLEBUFFER, 
      PFD_TYPE_RGBA,
      lpWindow->GetBpp(),
	  0, 0, 0, 0, 0, 0,
      0,
      0, 0, 0, 0, 0, 0,
      32, 0, 0,
      PFD_MAIN_PLANE,
      0, 0, 0, 0
   };
   HDC &lDC = lpWindow->GetHDC();
   if (!lDC)                                
   {
      Deinit();                                
      MessageBox(NULL,"Can't Create A GL Device Context.","ERROR",MB_OK|MB_ICONEXCLAMATION);
      return false;                                  
   }
   //Se intenta encontrar un formato de p�xel que sea compatible con la configuraci�n
   // anterior:
   mPixelFormat = ChoosePixelFormat(lDC,&lPfp);
   if (!mPixelFormat)   
   {
      Deinit(); 
      MessageBox(NULL,"Can't Find A Suitable PixelFormat.","ERROR",MB_OK|MB_ICONEXCLAMATION);
      return false;
   }
   //Se establece el formato de p�xel:
   if(!SetPixelFormat(lDC,mPixelFormat,&lPfp))       
   {
      Deinit();
      MessageBox(NULL,"Can't Set The PixelFormat.","ERROR",MB_OK|MB_ICONEXCLAMATION);
      return false;
   }
   //Se crea un contexto de renderizado de OpenGL, por lo que se llama a la funci�n wglCreateContext:
   mHRC = wglCreateContext(lDC);
   if (!mHRC)
   {
      Deinit();
      MessageBox(NULL,"Can't Create A GL Rendering Context.","ERROR",MB_OK|MB_ICONEXCLAMATION);
      return false;
   }
   //Se establece el contexto de renderizado creado como el contexto de renderizado actual:
   if(!wglMakeCurrent(lDC,mHRC))
   {
      Deinit();
      MessageBox(NULL,"Can't Activate The GL Rendering Context.","ERROR",MB_OK|MB_ICONEXCLAMATION);
      return false;
   }

   mpWindow = lpWindow;
   return true;
}

//Funci�n que inicializa el estado de OpenGL. 
void cGraphicManager::InitializeGLState()
{
   //Se inicializa el ShadeModel:
   glShadeModel(GL_SMOOTH);   
   //Se establecen los valores con los que se limpiar� el backbuffer y el ZBuffer:
   glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
   glClearDepth(1.0f);
   //Configurar el Z test:
   glEnable(GL_DEPTH_TEST);
   glDepthFunc(GL_LEQUAL); 
   glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
   unsigned muiWidth = mpWindow->GetWidth();
   unsigned muiHeight = mpWindow->GetHeight();
   //Se configura el Viewport:
   glViewport(0, 0, muiWidth, muiHeight);
   //Se activa el uso de Texturas:
   glEnable(GL_TEXTURE_2D);
   glEnable(GL_BLEND);
   glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
   //Se establece la matriz de Projection:
   glMatrixMode(GL_PROJECTION);                             
   glLoadIdentity();
   float lfAspectRatio = (float)muiWidth/(float)muiHeight;
   gluPerspective(45.0f, lfAspectRatio, 0.1f, 100.0f);
   //Se establece la matriz de ModelView:
   glMatrixMode(GL_MODELVIEW);                        
   glLoadIdentity();          
}

//Funci�n que se encarga de la liberaci�n de OpenGL. 
bool cGraphicManager::Deinit()
{
   //Se comprueba si se ha llegado a crear el contexto de renderizado y 
   // de ser as�, se establece el contexto de renderizado por defecto y se elimina el que se cre�
   // en la funci�n CreateContext.
   if (mHRC)
   {
      if (!wglMakeCurrent(NULL,NULL))
      {
         MessageBox(NULL,"Release Of DC And RC Failed.","SHUTDOWN ERROR",MB_OK | MB_ICONINFORMATION);
      }
      if (!wglDeleteContext(mHRC)) 
      {
         MessageBox(NULL,"Release Rendering Context Failed.","SHUTDOWN ERROR",MB_OK | MB_ICONINFORMATION);
      }
      mHRC = NULL;
   }
   //Se limpia la ventana poni�ndola a NULL.
   mpWindow = NULL;
   return true;
}

//Funci�n que se encarga de intercambiar el backbuffer con el frontbuffer.
void cGraphicManager::SwapBuffer()
{
	if ( mpWindow )
	{
		//Se invoca a una funci�n de OpenGL.
		SwapBuffers(mpWindow->GetHDC());
	}
}

//Point render function
void cGraphicManager::DrawPoint( const cVec3 &lvPosition, const cVec3 &lvColor ){
	glDisable(GL_TEXTURE_2D);
	// POINT
	glPointSize(10);
	glColor3f (lvColor.x, lvColor.y, lvColor.z);
	glBegin(GL_POINTS);
		glVertex3f(lvPosition.x, lvPosition.y, lvPosition.z);
	glEnd ();
	glEnable(GL_TEXTURE_2D);
}

//Line render function
void cGraphicManager::DrawLine( const cVec3 &lvPosition1, const cVec3 &lvPosition2, const cVec3 &lvColor ){
	glDisable(GL_TEXTURE_2D);
	// LINE
	glLineWidth (1);
	glColor3f (lvColor.x, lvColor.y, lvColor.z);
	glBegin(GL_LINES);
		for (float xtmp = -10.0; xtmp <= 10.0; xtmp += 1.0){
			glVertex3f(lvPosition1.x, lvPosition1.y, lvPosition1.z);
			glVertex3f(lvPosition2.x, lvPosition2.y, lvPosition2.z);
		};
	glEnd ();
	glEnable(GL_TEXTURE_2D);
}

//Grid render function
void cGraphicManager::DrawGrid()
{
	glDisable(GL_TEXTURE_2D);
	// GRID
	glLineWidth (1);
	glColor3f (1.0f, 1.0f, 1.0f);
	glBegin(GL_LINES);
		for (float lfxtmp = -10.0; lfxtmp <= 10.0; lfxtmp += 1.0)
		{
			glVertex3f (lfxtmp, 0.0f,-10.0);
			glVertex3f (lfxtmp, 0.0f, 10.0);
			glVertex3f (-10.0, 0.0f, lfxtmp);
			glVertex3f ( 10.0, 0.0f, lfxtmp);
		};
	glEnd ();
	glEnable(GL_TEXTURE_2D);
}

//Axis render function
void cGraphicManager::DrawAxis()
{
	glDisable(GL_TEXTURE_2D);
	// AXIS
	glLineWidth (2);
	glBegin(GL_LINES);
		glColor3f(1.0f, 0.0f, 0.0f); // X Axis
		glVertex3f(0.0f, 0.0f, 0.0f);
		glColor3f(1.0f, 0.0f, 0.0f);
		glVertex3f(1.0f, 0.0f, 0.0f);
		glColor3f(0.0f, 1.0f, 0.0f); // Y Axis
		glVertex3f(0.0f, 0.0f, 0.0f);
		glColor3f(0.0f, 1.0f, 0.0f);
		glVertex3f(0.0f, 1.0f, 0.0f);
		glColor3f(0.0f, 0.0f, 1.0f); // Z Axis
		glVertex3f(0.0f, 0.0f, 0.0f);
		glColor3f(0.0f, 0.0f, 1.0f);
		glVertex3f(0.0f, 0.0f, 1.0f);
	glEnd();
	glEnable(GL_TEXTURE_2D);
}

//Set world matrix
void cGraphicManager::SetWorldMatrix( const cMatrix &lMatrix )
{
	mWorldMatrix = lMatrix;
	RefreshWorldView();
}

//Updates Model-view matrix
void cGraphicManager::RefreshWorldView()
{
	// Select The Modelview Matrix
	glMatrixMode(GL_MODELVIEW);
	// Calculate the ModelView Matrix
	cMatrix lWorldView = mpActiveCamera->GetView();
	lWorldView = mWorldMatrix * lWorldView;
	// Set The View Matrix
	glLoadMatrixf( lWorldView.AsFloatPointer() );
}

//Sets current camera
void cGraphicManager::ActivateCamera( cCamera * lpCamera )
{
	assert(lpCamera);
	mpActiveCamera = lpCamera;
	// Select The Projection Matrix
	glMatrixMode(GL_PROJECTION);
	// Set The Projection Matrix
	glLoadMatrixf( mpActiveCamera->GetProj().AsFloatPointer() );
	// Refresh the worl view matrix
	RefreshWorldView();
}