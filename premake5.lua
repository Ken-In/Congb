workspace "Congb"
	architecture "x64"
	startproject "SandBox"

	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

-- Include directories relative to root folder (solition directory)
IncludeDir = {}
IncludeDir["GLFW"] = "Congb/vendor/GLFW/include"
IncludeDir["Glad"] = "Congb/vendor/Glad/include"
IncludeDir["ImGui"] = "Congb/vendor/imgui"
IncludeDir["glm"] = "Congb/vendor/glm"

include "Congb/vendor/GLFW"
include "Congb/vendor/Glad"
include "Congb/vendor/imgui"

project "Congb"
	location "Congb"
	kind "SharedLib"
	language "C++"
	staticruntime "off"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	pchheader "cbpch.h"
	pchsource "Congb/src/cbpch.cpp"

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp",
		"%{prj.name}/vendor/glm/glm/**.hpp",
		"%{prj.name}/vendor/glm/glm/**.inl",
	}

	includedirs
	{
		"%{prj.name}/src",
		"%{prj.name}/vendor/spdlog/include",
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.Glad}",
		"%{IncludeDir.ImGui}",
		"%{IncludeDir.glm}"
	}

	links
	{
		"GLFW",
		"Glad",
		"ImGui",
		"opengl32.lib"
	}

	filter "system:windows"
		cppdialect "C++17"
		systemversion "latest"
		
		defines
		{
			"CB_PLATFORM_WINDOWS",
			"CB_BUILD_DLL",
			"GLFW_INCLUDE_NONE"
		}

		postbuildcommands
		{
			("{COPY} %{cfg.buildtarget.relpath} \"../bin/".. outputdir .."/SandBox/\"")
		}

	filter "configurations:Debug"
		defines "CB_DEBUG"
		runtime "Debug"
		symbols "On"

	filter "configurations:Release"
		defines "CB_RELEASE"
		runtime "Release"
		optimize "On"

	filter "configurations:Dist"
		defines "CB_DIST"
		runtime "Release"
		optimize "On"



project "SandBox"
	location "SandBox"
	kind "ConsoleApp"
	language "C++"
	staticruntime "off"

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
		"Congb/src",
		"%{IncludeDir.glm}"
	}

	links
	{
		"Congb"
	}

	filter "system:windows"
		cppdialect "C++17"
		systemversion "latest"

		defines
		{
			"CB_PLATFORM_WINDOWS"
		}

	filter "configurations:Debug"
		defines "CB_DEBUG"
		runtime "Debug"
		symbols "On"

	filter "configurations:Release"
		defines "CB_RELEASE"
		runtime "Release"
		optimize "On"

	filter "configurations:Dist"
		defines "CB_DIST"
		runtime "Release"
		optimize "On"