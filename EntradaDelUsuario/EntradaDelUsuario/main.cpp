//MASTER DE CREACI�N DE VIDEOJUEGOS UOC-ULL
// Asignatura: Aplicaci�n Pr�ctica B�sica de Videojuegos.
// Junio, 2011.
//  Juan Manuel Ram�n Vigo.
//  Alberto Alfonso G�mez.

//    Pr�ctica 1: Entrada del Usuario
//-----------------------------------------
//En l�neas generales, se implementa un gestor de entrada (InputManager) que se encarga
// de actualizar y leer los dispositivos de entrada. Se implementan 3 clases (cKeyBoard, cPad y
// cMouse) que representan el teclado el gamepad y el rat�n y se encargan de encapsular los
// eventos producidos por dichos dispositivos.
//Para probar la aplicaci�n, se ha programado que �sta debe cerrarse con la tecla Escape del teclado,
// el bot�n central del mouse o el bot�n 1 del gamepad.

#include <stdio.h>
#include <Windows.h>
#include <stdlib.h>
#include "Game\Game.h"

//Al tratarse de un proyecto win 32 el protipo de la funci�n main es espec�fico.
//La funci�n "WinMain" es el m�todo de entrada de un programa Windows, en lugar de la conocida "main", 
// y tiene cuatro par�metros de entrada: 
//    hInstance, es un manipulador para la instancia del programa que estamos ejecutando. Cada vez que se ejecuta una aplicaci�n, Windows crea una Instancia para ella, y le pasa un manipulador de dicha instancia a la aplicaci�n.
//    hPrevInstance, es un manipulador a instancias previas de la misma aplicaci�n. Como Windows es multitarea, pueden existir varias versiones de la misma aplicaci�n ejecut�ndose, varias instancias. En Windows 3.1, este par�metro nos serv�a para saber si nuestra aplicaci�n ya se estaba ejecutando, y de ese modo se pod�an compartir los datos comunes a todas las instancias. Pero eso era antes, ya que en Win32 usa un segmento distinto para cada instancia y este par�metro es siempre NULL, s�lo se conserva por motivos de compatibilidad.
//    lpszCmdParam, esta cadena contiene los argumentos de entrada del comando de l�nea.
//    nCmdShow, este par�metro especifica c�mo se mostrar� la ventana. Para ver sus posibles valores consultar valores de ncmdshow. Se recomienda no usar este par�metro en la funci�n ShowWindow la primera vez que se �sta es llamada. En su lugar debe usarse el valor SW_SHOWDEFAULT.

int WINAPI WinMain(
	HINSTANCE hInstance,    // Instance
	HINSTANCE hPrevInstance,      // Previous Instance
	LPSTR     lpCmdLine,      // Command Line Parameters
	int       nCmdShow)// Window Show State
{
   //Inicializamos el juego
   if ( cGame::Get().Init() )
   {
	   //Se obtiene el tiempo en milisegundos desde que arranc� el Sistema (Windows)
	   unsigned long luiLastTime = timeGetTime();
	   //Mientras no se finalice, se actualiza y renderiza
	   while (!cGame::Get().HasFinished())
	   {
		  //Se calcula el tiempo transcurrido (pas�ndolo a segundos) desde la iteraci�n anterior
		  unsigned long luiActualTime = timeGetTime();
		  float lfTimestep = ((float)(luiActualTime - luiLastTime) 
							 / 1000.0f);
		  luiLastTime = luiActualTime;
		  //Se llama a la funci�n Update pas�ndole el tiempo transcurrido, para que act�e igual en m�quinas r�pidas como lentas, 
		  // ya la m�quina r�pida ejecutar� m�s iteraciones pero el tiempo ser� 
		  // peque�o, mientras que la m�quina lenta ejecuta menos iteraciones con
		  // un tiempo mayor
		  cGame::Get().Update( lfTimestep );
		  // Render
		  cGame::Get().Render();
	   }
	   //Se finaliza el juego.
	   cGame::Get().Deinit();  
   }
}