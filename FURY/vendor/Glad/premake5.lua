project "Glad"
    kind "StaticLib"
    language "C"
    staticruntime "On"
    
	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files
	{
        "include/glad/glad.h",
        "include/khr/khrplatform.h",
        "src/glad.c"
    }

    includedirs
    {
        "include"
    }
    
	filter "system:windows"
        systemversion "latest"

    filter "configurations:Debug"
        buildoptions "/MTd"
        runtime "Debug"
        symbols "On"

	filter "configurations:Release"
        runtime "Release"
        optimize "On"