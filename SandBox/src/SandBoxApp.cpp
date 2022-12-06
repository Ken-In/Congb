#include "Congb.h"

class SandBox : public Congb::Application
{
public:
	SandBox()
	{

	}

	~SandBox()
	{

	}

	void Run()
	{
		while (true);
	}
};

Congb::Application* Congb::CreateApplication()
{
	return new SandBox();
}