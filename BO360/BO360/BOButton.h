#ifndef BOBUTTON_H_
#define BOBUTTON_H_

#include "BOObject.h"
#include "BOSubscriber.h"

class BOButton : public BOObject, public BOSubscriber 
{
public:
	BOButton();
	~BOButton();

private:

};
#endif