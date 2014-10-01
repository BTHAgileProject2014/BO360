#ifndef BOKEY_H_
#define BOKEY_H_

#include "BOObject.h"

class BOKey : public BOObject
{
public:
	BOKey();
	~BOKey();

	bool Initialize(float2 p_position, int2 p_size, std::string p_fileName);
	void Shutdown();
	void Update(double p_deltaTime);
	void Draw();
};

#endif