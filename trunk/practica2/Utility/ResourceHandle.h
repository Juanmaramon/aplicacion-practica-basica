// This class is the handle to interact with the resource manager

#ifndef RESOURCE_HANDLE_H
#define RESOURCE_HANDLE_H
#include <stdlib.h>

class cResourceManager;
class cResource;

static const unsigned kuiInvalidKey = 0;
class cResourceHandle
{
	public:
		cResourceHandle() { mpManager = NULL; muiKey = kuiInvalidKey; }
		cResource * GetResource();
		inline bool IsValidHandle() { return muiKey != kuiInvalidKey; }
		inline void Invalidate() { muiKey = kuiInvalidKey; }
		inline unsigned GetID() { return muiID; }
		inline unsigned GetKey() { return muiKey; }
	protected:
		friend class cResourceManager;
		void Init( cResourceManager * lpManager, unsigned luiID, unsigned luiKey );
		cResourceManager * mpManager;
		unsigned int muiID;
		unsigned int muiKey;
};
#endif