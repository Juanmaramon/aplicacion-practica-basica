// This class contains a validation resource key and the resource itself 

#ifndef INTERNAL_RESOURCE_H
#define INTERNAL_RESOURCE_H

class cResource;

struct cInternalResource
{
	unsigned int muiKey;
	cResource * mpResource;
};
#endif