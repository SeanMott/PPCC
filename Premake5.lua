workspace "PowerPCToC"
architecture "x64"
startproject "PCASMToCpp"

configurations
    {
        "Debug",
        "Release",
        "Dist" --,

        --"Desktop_Debug",
        --"Desktop_Release",
        --"Desktop_Dist",

        --"Android_Debug",
        --"Android_Release",
        --"Android_Dist",

        --"IOS_Debug",
        --"IOS_Release",
        --"IOS_Dist",
    }

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}-%{cfg.startproject}"

include "C:/GameDev/BTDSTD//ProjectDeps.lua"

project "PowerPCOperandDecoder"

location "PowerPCOperandDecoder"
kind "StaticLib"
language "C++"
files 
    {
        "PowerPCOperandDecoder/includes/**.h",
        "PowerPCOperandDecoder/src/**.c",
        "PowerPCOperandDecoder/includes/**.hpp",
        "PowerPCOperandDecoder/src/**.cpp",
    }

    includedirs
    {
        "PowerPCOperandDecoder/includes",
        BTDSTD_INCLUDE_DIR_PATH
    }
    
    links
    {
       "BTDSTD"
    }
    
    defines
    {
        "GLFW_INCLUDE_NONE",
        "GLM_FORCE_RADIANS",
        "GLM_FORCE_DEPTH_ZERO_TO_ONE",
        "GLM_ENABLE_EXPERIMENTAL"
    }
    
    flags
    {
        "NoRuntimeChecks",
        "MultiProcessorCompile"
    }
    
    --platforms
    filter "system:windows"
        cppdialect "C++20"
        staticruntime "On"
        systemversion "latest"
    
        defines
        {
            "Window_Build",
            "Desktop_Build"
        }
    
    --configs
    filter "configurations:Debug"
        defines "BTD_DEBUG"
        symbols "On"
    
    filter "configurations:Release"
        defines "BTD_RELEASE"
        optimize "On"
    
    filter "configurations:Dist"
        defines "BTD_DIST"
        optimize "On"
    
        defines
        {
            "NDEBUG"
        }

--common library for parsing Power PC assembly and DTK output
project "PowerPCParser"
    location "PowerPCParser"
    kind "StaticLib"
    language "C++"
    
    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("bin-obj/" .. outputdir .. "/%{prj.name}")
    
    
    files 
    {
        "PowerPCParser/includes/**.h",
        "PowerPCParser/src/**.c",
        "PowerPCParser/includes/**.hpp",
        "PowerPCParser/src/**.cpp",
    }

    includedirs
    {
        "PowerPCParser/includes",
        "PowerPCOperandDecoder/includes",
        BTDSTD_INCLUDE_DIR_PATH 
    }
    
    links
    {
       "PowerPCOperandDecoder",
       "BTDSTD"
    }
    
    defines
    {
        "GLFW_INCLUDE_NONE",
        "GLM_FORCE_RADIANS",
        "GLM_FORCE_DEPTH_ZERO_TO_ONE",
        "GLM_ENABLE_EXPERIMENTAL"
    }
    
    flags
    {
        "NoRuntimeChecks",
        "MultiProcessorCompile"
    }
    
    --platforms
    filter "system:windows"
        cppdialect "C++20"
        staticruntime "On"
        systemversion "latest"
    
        defines
        {
            "Window_Build",
            "Desktop_Build"
        }
    
    --configs
    filter "configurations:Debug"
        defines "BTD_DEBUG"
        symbols "On"
    
    filter "configurations:Release"
        defines "BTD_RELEASE"
        optimize "On"
    
    filter "configurations:Dist"
        defines "BTD_DIST"
        optimize "On"
    
        defines
        {
            "NDEBUG"
        }

--converts Power PC Assembly outputed by DTK to C++
    project "PCASMToCpp"
    location "PCC"
    kind "ConsoleApp"
    language "C++"
    
    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("bin-obj/" .. outputdir .. "/%{prj.name}")
    
    
    files 
    {
        "PCC/includes/**.h",
        "PCC/src/**.c",
        "PCC/includes/**.hpp",
        "PCC/src/**.cpp",
    }

    includedirs
    {
        "PCC/includes",

        "PowerPCOperandDecoder/includes",
        "PowerPCParser/includes",
        BTDSTD_INCLUDE_DIR_PATH
    }
    
    links
    {

       "PowerPCParser"
    }
    
    defines
    {
        "GLFW_INCLUDE_NONE",
        "GLM_FORCE_RADIANS",
        "GLM_FORCE_DEPTH_ZERO_TO_ONE",
        "GLM_ENABLE_EXPERIMENTAL"
    }
    
    flags
    {
        "NoRuntimeChecks",
        "MultiProcessorCompile"
    }
    
    --platforms
    filter "system:windows"
        cppdialect "C++20"
        staticruntime "On"
        systemversion "latest"
    
        defines
        {
            "Window_Build",
            "Desktop_Build"
        }
    
    --configs
    filter "configurations:Debug"
        defines "BTD_DEBUG"
        symbols "On"
    
    filter "configurations:Release"
        defines "BTD_RELEASE"
        optimize "On"

    filter "configurations:Dist"
        defines "BTD_DIST"
        optimize "On"
    
        defines
        {
            "NDEBUG"
        }

--library for compiling the outputted C++ code
project "PPC_StaticRecompLayer"
    location "PPC_StaticRecompLayer"
    kind "StaticLib"
    language "C++"
    
    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("bin-obj/" .. outputdir .. "/%{prj.name}")
    
    
    files 
    {
        "PPC_StaticRecompLayer/includes/**.h",
        "PPC_StaticRecompLayer/src/**.c",
        "PPC_StaticRecompLayer/includes/**.hpp",
        "PPC_StaticRecompLayer/src/**.cpp",
    }

    includedirs
    {
        "PPC_StaticRecompLayer/includes",
        "PowerPCOperandDecoder/includes",
        BTDSTD_INCLUDE_DIR_PATH
    }
    
    links
    {
       "PowerPCOperandDecoder",
       "BTDSTD"
    }
    
    defines
    {
        "GLFW_INCLUDE_NONE",
        "GLM_FORCE_RADIANS",
        "GLM_FORCE_DEPTH_ZERO_TO_ONE",
        "GLM_ENABLE_EXPERIMENTAL"
    }
    
    flags
    {
        "NoRuntimeChecks",
        "MultiProcessorCompile"
    }
    
    --platforms
    filter "system:windows"
        cppdialect "C++20"
        staticruntime "On"
        systemversion "latest"
    
        defines
        {
            "Window_Build",
            "Desktop_Build"
        }
    
    --configs
    filter "configurations:Debug"
        defines "BTD_DEBUG"
        symbols "On"
    
    filter "configurations:Release"
        defines "BTD_RELEASE"
        optimize "On"
    
    filter "configurations:Dist"
        defines "BTD_DIST"
        optimize "On"
    
        defines
        {
            "NDEBUG"
        }

--renames all structs in DTK outputed ASM to make their veriables
project "PCASM_StructRename"
location "PCASM_StructRename"
kind "ConsoleApp"
language "C++"

targetdir ("bin/" .. outputdir .. "/%{prj.name}")
objdir ("bin-obj/" .. outputdir .. "/%{prj.name}")


files 
{
    "PCASM_StructRename/includes/**.h",
    "PCASM_StructRename/src/**.c",
    "PCASM_StructRename/includes/**.hpp",
    "PCASM_StructRename/src/**.cpp",
}

includedirs
{
    "PCASM_StructRename/includes",

    "PowerPCOperandDecoder/includes",
    "PowerPCParser/includes",
    BTDSTD_INCLUDE_DIR_PATH
}

links
{
   "PowerPCParser"
}

defines
{
    "GLFW_INCLUDE_NONE",
    "GLM_FORCE_RADIANS",
    "GLM_FORCE_DEPTH_ZERO_TO_ONE",
    "GLM_ENABLE_EXPERIMENTAL"
}

flags
{
    "NoRuntimeChecks",
    "MultiProcessorCompile"
}

--platforms
filter "system:windows"
    cppdialect "C++20"
    staticruntime "On"
    systemversion "latest"

    defines
    {
        "Window_Build",
        "Desktop_Build"
    }

--configs
filter "configurations:Debug"
    defines "BTD_DEBUG"
    symbols "On"

filter "configurations:Release"
    defines "BTD_RELEASE"
    optimize "On"

filter "configurations:Dist"
    defines "BTD_DIST"
    optimize "On"

    defines
    {
        "NDEBUG"
    }

    