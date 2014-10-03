#ifndef BOPUSUBSCRIBER_H_
#define BOPUSUBSCRIBER_H_

#include "BOUtility.h"

class BOPUSubscriber
{
public:
	BOPUSubscriber();
	~BOPUSubscriber();

	virtual void Handle(PowerUpTypes p_type, bool p_activated) = 0;
};
#endif