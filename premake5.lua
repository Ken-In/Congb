workspace "Congb"
	architecture "x86_64"

	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

project "Congb"
	location "Congb"
	kind "SharedLib"
	language "C++"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	pchheader "cbpch.h"
	pchsource "Congb/src/cbpch.cpp"

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs
	{
		"%{prj.name}/src",
		"%{prj.name}/vendor/spdlog/include"
	}

	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "latest"
		
		defines
		{
			"CB_PLATFORM_WINDOWS",
			"CB_BUILD_DLL"
		}

		postbuildcommands
		{
			("{COPY} %{cfg.buildtarget.relpath} ../bin/".. outputdir .."/SandBox")
		}

	filter "configurations:Debug"
		defines "CB_DEBUG"
		symbols "On"

	filter "configurations:Release"
		defines "CB_RELEASE"
		optimize "On"

	filter "configurations:Dist"
		defines "CB_DIST"
		optimize "On"



project "SandBox"
	location "SandBox"
	kind "ConsoleApp"
	language "C++"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs
	{
		"Congb/vendor/spdlog/include",
		"Congb/src"
	}

	links
	{
		"Congb"
	}

	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "latest"

		defines
		{
			"CB_PLATFORM_WINDOWS"
		}

	filter "configurations:Debug"
		defines "CB_DEBUG"
		symbols "On"

	filter "configurations:Release"
		defines "CB_RELEASE"
		optimize "On"

	filter "configurations:Dist"
		defines "CB_DIST"
		optimize "On"