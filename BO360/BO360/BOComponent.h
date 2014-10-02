#ifndef BOCOMPONENT_H_
#define BOCOMPONENT_H_

class BOComponent
{
public:
	BOComponent();
	~BOComponent();

public:
	virtual bool Initialize();
	virtual void Shutdown();
};
#endif