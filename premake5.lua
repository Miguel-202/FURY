workspace "FURY"
    architecture "x64"

    configurations
    {
        "Debug",
        "Release",
        "Dist"
    }

    
    startproject "Sandbox"

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

-- Include directories relative to root folder (solution directory)
IncludeDir = {}
IncludeDir["GLFW"] = "FURY/vendor/GLFW/include"
IncludeDir["Glad"] = "FURY/vendor/Glad/include"
IncludeDir["ImGui"] = "FURY/vendor/imgui"
IncludeDir["glm"] = "FURY/vendor/glm"
--TODO: consider wind32 to support DirectX
--IncludeDir["stb_image"] = "FURY/vendor/stb_image"

group "Dependencies"
    include "FURY/vendor/GLFW"
    include "FURY/vendor/Glad"
    include "FURY/vendor/imgui"
group ""


project "FURY"
    location "FURY"
    kind "SharedLib"
    language "C++"

    targetdir ("bin/" ..outputdir.. "/%{prj.name}")
    objdir ("bin-int/" ..outputdir.. "/%{prj.name}")

    pchheader "FURYpch.h"
    pchsource "FURY/src/FURYpch.cpp"

    files
    {
        "%{prj.name}/src/**.h",
        "%{prj.name}/src/**.cpp"
    }

    includedirs
    {
        "%{prj.name}/src", --Easy includes for the project #include "FURY/Example.h" instead of #include "../FURY/src/Example.h"
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
		"opengl32.lib",
	    "dwmapi.lib"
	}

    filter "system:windows"
        cppdialect "C++17"
        staticruntime "Off"
        systemversion "latest"

        defines
        {
            "FURY_PLATFORM_WINDOWS",
            "FURY_BUILD_DLL",   
            "GLFW_INCLUDE_NONE"
        }

        postbuildcommands
        {
            --COPY "$(TargetDir)/FURY.dll" "$(SolutionDir)bin/Debug-windows-x86_64/Sandbox"

            --("{COPY}%{cfg.buildtarget.relpath} ../bin/" ..outputdir.. "/Sandbox")

            --("copy /B /Y ..\\bin\\" .. outputdir .. "\\FURY\\FURY.dll ..\\bin\\" .. outputdir .. "\\Sandbox\\ > nul")
            ("{COPY} %{cfg.buildtarget.relpath} \"../bin/" ..outputdir.. "/Sandbox/\"")
            --"{mkdir} ../bin/" ..outputdir.. "/Sandbox",
            --"copy %{cfg.buildtarget.relpath} ../bin/" ..outputdir.. "/Sandbox"
        }

    filter "configurations:Debug"
        defines "FURY_DEBUG"
        symbols "On"

    filter "configurations:Release"
        defines "FURY_RELEASE"
        optimize "On"

    filter "configurations:Dist"
        defines "FURY_DIST"
        optimize "On"



project "Sandbox"
    location "Sandbox"
    kind "ConsoleApp"
    language "C++"

    targetdir ("bin/" ..outputdir.. "/%{prj.name}")
    objdir ("bin-int/" ..outputdir.. "/%{prj.name}")

    files
    {
        "%{prj.name}/src/**.h",
        "%{prj.name}/src/**.cpp"
    }

    includedirs
    {
        "FURY/vendor/spdlog/include",
        "FURY/src",
        "FURY/vendor",
        "%{IncludeDir.glm}"
    }

    links
    {
        "FURY"
    }

    filter "system:windows"
        cppdialect "C++17"
        staticruntime "Off"
        systemversion "latest"

        defines
        {
            "FURY_PLATFORM_WINDOWS"
        }

    filter "configurations:Debug"
        defines "FURY_DEBUG"
        runtime "Debug"
        staticruntime "Off"
        symbols "On"

    filter "configurations:Release"
        defines "FURY_RELEASE"
        staticruntime "Off"
        runtime "Release"
        optimize "On"

    filter "configurations:Dist"
        defines "FURY_DIST"
        staticruntime "Off"
		runtime "Release"
        optimize "On"

        