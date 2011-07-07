#include "InputConfiguration.h"
#include "InputManager.h"
 

//Tabla (array) cuyos elementos son del tipo "tActionMapping" de InputManager.h.
//Esta tabla indica la relaci�n entre las acciones y los dispositivos.
//El primer par�metro de cada terna es del enumerado "eInputActions" del fichero InputConfiguration.h,
// y el segundo par�metro es del enumerado "eDevices" de InputManager.h.
tActionMapping kaActionMapping[] = {
	{ eIA_CloseApplication, eKeyboard, OIS::KC_ESCAPE }, //Esta fila indica que la acci�n salir con el teclado est� asociada a la tecla escape.	                                                     	
	{ eIA_CloseApplication, ePad, ePad_Button1 }, //Esta fila indica que la acci�n salir con el JoyStick/GamePad est� asociada al bot�n 1.	                                                     	 
	{ eIA_CloseApplication, eMouse, eMouse_ButtonMiddle }, //Esta fila indica que la acci�n salir con el mouse est� asociada al bot�n central.	                                                     	 
    { -1, -1, -1}  // End of the table (Marca el final de la tabla)
};