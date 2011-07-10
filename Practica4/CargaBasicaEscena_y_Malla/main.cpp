//MASTER DE CREACIÓN DE VIDEOJUEGOS UOC-ULL
// Asignatura: Aplicación Práctica Básica de Videojuegos.
// Julio, 2011.
//  Juan Manuel Ramón Vigo.
//  Alberto Alfonso Gómez.

//    Práctica 4: Gestión básica de materiales
//--------------------------------------------
/*
La librería Assimp nos permite cargar la información de la escena, lo cual incluye también materiales. 
El sistema de materiales de esta librería no es muy potente, por lo que sólo extraeremos las texturas asociadas a 
cada maya y las renderizaremos. Lo que crearemos en este capítulo es un sistema simple de materiales.
El sistema de materiales de Assimp no es muy potente, pero expone muchísima 
información que podemos usar para renderizar la escena. La estructura de escena de 
Assimp cuenta con un array llamado mMaterials que contiene los materiales que usa la 
escena. El tamaño de este array no tiene porqué coincidir con el número de mallas, ya 
que más de una malla puede usar el mismo material. Por sencillez, asumiremos que las 
texturas asociadas a una escena se encuentran en el mismo directorio que el fichero de 
la propia escena.
*/

#include <stdio.h>
#include <Windows.h>
#include <stdlib.h>
#include "Game\Game.h"

//Al tratarse de un proyecto win 32 el protipo de la función main es específico.
//La función "WinMain" es el método de entrada de un programa Windows, en lugar de la conocida "main", 
// y tiene cuatro parámetros de entrada: 
//    hInstance, es un manipulador para la instancia del programa que estamos ejecutando. Cada vez que se ejecuta una aplicación, Windows crea una Instancia para ella, y le pasa un manipulador de dicha instancia a la aplicación.
//    hPrevInstance, es un manipulador a instancias previas de la misma aplicación. Como Windows es multitarea, pueden existir varias versiones de la misma aplicación ejecutándose, varias instancias. En Windows 3.1, este parámetro nos servía para saber si nuestra aplicación ya se estaba ejecutando, y de ese modo se podían compartir los datos comunes a todas las instancias. Pero eso era antes, ya que en Win32 usa un segmento distinto para cada instancia y este parámetro es siempre NULL, sólo se conserva por motivos de compatibilidad.
//    lpszCmdParam, esta cadena contiene los argumentos de entrada del comando de línea.
//    nCmdShow, este parámetro especifica cómo se mostrará la ventana. Para ver sus posibles valores consultar valores de ncmdshow. Se recomienda no usar este parámetro en la función ShowWindow la primera vez que se ésta es llamada. En su lugar debe usarse el valor SW_SHOWDEFAULT.

int WINAPI WinMain(
	HINSTANCE hInstance,    // Instance
	HINSTANCE hPrevInstance,      // Previous Instance
	LPSTR     lpCmdLine,      // Command Line Parameters
	int       nCmdShow)// Window Show State
{
   //Inicializamos el juego
   if ( cGame::Get().Init() )
   {
	   //Se obtiene el tiempo en milisegundos desde que arrancó el Sistema (Windows)
	   unsigned long luiLastTime = timeGetTime();
	   //Mientras no se finalice, se actualiza y renderiza
	   while (!cGame::Get().HasFinished())
	   {
		  //Se calcula el tiempo transcurrido (pasándolo a segundos) desde la iteración anterior
		  unsigned long luiActualTime = timeGetTime();
		  float lfTimestep = ((float)(luiActualTime - luiLastTime) 
							 / 1000.0f);
		  luiLastTime = luiActualTime;
		  //Se llama a la función Update pasándole el tiempo transcurrido, para que actúe igual en máquinas rápidas como lentas, 
		  // ya la máquina rápida ejecutará más iteraciones pero el tiempo será 
		  // pequeño, mientras que la máquina lenta ejecuta menos iteraciones con
		  // un tiempo mayor
		  cGame::Get().Update( lfTimestep );
		  // Render
		  cGame::Get().Render();
	   }
	   //Se finaliza el juego.
	   cGame::Get().Deinit();  
   }
}