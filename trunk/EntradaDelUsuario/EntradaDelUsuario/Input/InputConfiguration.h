/*
En este fichero se define un enum donde se declaran las posibles acciones.
Esto sirve para indicar desde el juego (clase Game) al InputManager la relaci�n que
existe entre las acciones y los dispositivos. 
*/

#ifndef INPUT_CONFIGURATION_H
#define INPUT_CONFIGURATION_H

enum eInputActions {
    eIA_CloseApplication = 0, //Acci�n para cerrar la aplicaci�n. 
    eIA_Count   //Indica cuantas acciones de entrada hay.
}; 

#endif