#ifndef BOSUBSCRIBER_H_
#define BOSUBSCRIBER_H_
#include "BOComponent.h"
#include "BOUtility.h"
class BOSubscriber : public BOComponent
{
public:
	BOSubscriber();
	~BOSubscriber();

	virtual bool Initialize();
	virtual void Shutdown();

	virtual void Handle(InputMessages p_inputMessages);
};
#endif