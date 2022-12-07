#pragma once

#ifdef CB_PLATFORM_WINDOWS

extern Congb::Application* Congb::CreateApplication();

int main(int argc, char** argv)
{
	Congb::Log::Init();
	CB_CORE_WARN("Initialized!");
	int a = 5;
	CB_INFO("Hello! Var = {0}", a);


	auto app = Congb::CreateApplication();
	app->Run();
	delete app;
}
#endif