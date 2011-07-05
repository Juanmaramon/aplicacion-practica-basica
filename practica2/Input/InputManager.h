#ifndef INPUT_MANAGER
#define INPUT_MANAGER

#include <vector>
#include "InputAction.h"
#include "InputEntry.h"
#include "Keyboard.h"
#include "..\Utility\Singleton.h"

#define IsPressed( ACTION ) cInputManager::Get().GetAction( ACTION ).GetIsPressed()

class OIS::InputManager;

enum eDevices
{
	eKeyboard = 0
};

struct tActionMapping
{
	int miAction;
	int miDevice;
	int miChannel;
};

class cInputManager : public cSingleton<cInputManager>
{
	public:
		void Init( const tActionMapping laActionMapping[],
		unsigned luiActionCount );
		void Update(const float &lfTimestep);
		void Deinit();
		inline cInputAction &GetAction(const int &lActionId){ return mActions[lActionId]; }
		friend class cSingleton<cInputManager>;
	protected:
		cInputManager() { ; } // Protected constructor
		private:
		float Check(int liDevice, int liChannel);
		std::vector <cInputAction> mActions;
		std::vector <cGenericDevice *> mDevices;
		std::vector < std::vector < cInputEntry > > mMapped;

		// Specific OIS vars
		friend class cKeyboard;
		OIS::InputManager * mpOISInputManager;
};
#endif