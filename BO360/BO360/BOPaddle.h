#ifndef BOPADDLE_H_
#define BOPADDLE_H_
#include "BOObject.h"
#include "BOSubscriber.h"
class BOPaddle : public BOObject, public BOSubscriber
{
public:
	BOPaddle();
	~BOPaddle();
	void Handle(InputMessages p_inputMessages);
};
#endif
