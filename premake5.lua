workspace "FURY"
    architecture "x64"

    configurations
    {
        "Debug",
        "Release",
        "Dist"
    }


outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

project "FURY"
    location "FURY"
    kind "SharedLib"
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
        "%{prj.name}/vendor/spdlog/include"
    }

    filter "system:windows"
        cppdialect "C++17"
        staticruntime "On"
        systemversion "latest"

        defines
        {
            "FURY_PLATFORM_WINDOWS",
            "FURY_BUILD_DLL"
        }

        postbuildcommands
        {
            --COPY "$(TargetDir)/FURY.dll" "$(SolutionDir)bin/Debug-windows-x86_64/Sandbox"

            --("{COPY}%{cfg.buildtarget.relpath} ../bin/" ..outputdir.. "/Sandbox")

            ("copy /B /Y ..\\bin\\" .. outputdir .. "\\FURY\\FURY.dll ..\\bin\\" .. outputdir .. "\\Sandbox\\ > nul")

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
        "FURY/src"
    }

    links
    {
        "FURY"
    }

    filter "system:windows"
        cppdialect "C++17"
        staticruntime "On"
        systemversion "latest"

        defines
        {
            "FURY_PLATFORM_WINDOWS"
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