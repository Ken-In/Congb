#pragma once

#ifdef CB_PLATFORM_WINDOWS

extern Congb::Application* Congb::CreateApplication();

int main(int argc, char** argv)
{
	auto app = Congb::CreateApplication();
	app->Run();
	delete app;
}
#endif