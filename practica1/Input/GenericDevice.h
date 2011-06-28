#ifndef GENERIC_DEVICE_H
#define GENERIC_DEVICE_H

class cGenericDevice
{
	public:
		virtual void Init() = 0;
		virtual void Deinit(void) = 0;
		virtual void Update(void) = 0;
		virtual float Check(unsigned luiEntry) = 0;
		virtual bool IsValid(void) = 0;
};
#endif