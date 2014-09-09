#pragma once
class BOComponent
{
public:
	BOComponent();
	~BOComponent();

public:
	virtual bool Initialize();
	virtual void Shutdown();
};

