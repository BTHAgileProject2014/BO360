#ifndef BOPADDLE_H_
#define BOPADDLE_H_
#include "BOObject.h"
#include "BOSubscriber.h"
class BOPaddle : public BOObject, public BOSubscriber
{
public:
	BOPaddle();
	~BOPaddle();

	void Update();

	// Overloaded functions
	bool Initialize(float2 p_position, int2 p_size, std::string p_fileName);
	void Handle(InputMessages p_inputMessages);
	void Draw();

private:
	double m_rotation;
};
#endif
