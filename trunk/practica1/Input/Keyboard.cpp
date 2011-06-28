#include "Keyboard.h"
#include "InputManager.h"
#include <assert.h>

void cKeyboard::Init()
{
	// Clear the input buffer
	memset(mabInputBuffer, 0, kuiInputChanelSize);

	assert(cInputManager::Get().mpOISInputManager);
	
	// Creates keyboard object
	OIS::InputManager * lpOISInputManager =cInputManager::Get().mpOISInputManager;
	mpOISKeyboard = (OIS::Keyboard*)lpOISInputManager->createInputObject( OIS::OISKeyboard, true );
	
	// Set callbacks
	mpOISKeyboard->setEventCallback( this );
	mbIsValid = true;
}

// Cleanup
void cKeyboard::Deinit(void)
{
	assert(cInputManager::Get().mpOISInputManager);
	cInputManager::Get().mpOISInputManager->destroyInputObject(mpOISKeyboard);
	mpOISKeyboard = 0;
	mbIsValid = false;
}

bool cKeyboard::keyPressed( const OIS::KeyEvent &lArg )
{
	mabInputBuffer[lArg.key] = true;
	return true;
}

bool cKeyboard::keyReleased( const OIS::KeyEvent &lArg )
{
	mabInputBuffer[lArg.key] = false;
	return true;
}

// Checks whether the current key is pressed or not
float cKeyboard::Check(unsigned luiEntry)
{
	if (mabInputBuffer[luiEntry]){
		return 1.0f;
	}

	return 0.0f;
}

void cKeyboard::Update(void)
{
	//This fires off buffered events for keyboards
	assert(mpOISKeyboard);
	mpOISKeyboard->capture();
}