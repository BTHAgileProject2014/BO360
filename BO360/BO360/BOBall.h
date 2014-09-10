#ifndef BOBALL_H_
#define BOBALL_H_

#include "BOObject.h"

class BOBall: public BOObject
{
public:
	BOBall();
	~BOBall();

	void Update();
};
#endif