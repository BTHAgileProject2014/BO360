#ifndef BOSUBSCRIBER_H_
#define BOSUBSCRIBER_H_
#include "BOComponent.h"
#include "BOUtility.h"
class BOSubscriber
{
public:
	BOSubscriber();
	~BOSubscriber();
	virtual void Handle(InputMessages p_inputMessages) = 0;
};
#endif