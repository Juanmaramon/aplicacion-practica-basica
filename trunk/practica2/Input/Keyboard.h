#ifndef KEYBOARD_H
#define KEYBOARD_H

#include <Windows.h>
#include "GenericDevice.h"
#include "OISInputManager.h"
#include "OISException.h"
#include "OISKeyboard.h"
#include "OISEvents.h"

class cKeyboard : public cGenericDevice, public OIS::KeyListener
{
public:
		cKeyboard() : mbIsValid(false) { ; }
		void Init();
		void Deinit(void);
		void Update(void);
		float Check(unsigned luiEntry);
		inline bool IsValid(void) { return mbIsValid; }
		// Listeners for the keyboard
		bool keyPressed( const OIS::KeyEvent &lArg );
		bool keyReleased( const OIS::KeyEvent &lArg );
	private:
		OIS::Keyboard* mpOISKeyboard;
		static const unsigned kuiInputChanelSize = 256;
		bool mabInputBuffer[kuiInputChanelSize];
		bool mbIsValid;
};
#endif