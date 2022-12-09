#include "cbpch.h"
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
		printf("SandBoxRun");
		while (true);
	}
};

Congb::Application* Congb::CreateApplication()
{
	return new SandBox();
}