#ifndef BOBLOCKIRON_H_
#define BOBLOCKIRON_H_

#include "BOBlock.h"
class BOBlockIron : public BOBlock
{
public:
	BOBlockIron();
	~BOBlockIron();

	bool Hit(int p_damage);
};
#endif