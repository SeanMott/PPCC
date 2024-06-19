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


--include "Libraries\\yaml-cpp"
--include "Libraries\\glfw"
include "C:\\GameDev\\BTDSTD"

--library for decoding Power PC assembly operands
project "PowerPCOperandDecoder"
    location "PowerPCOperandDecoder"
    kind "StaticLib"
    language "C++"
    
    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("bin-obj/" .. outputdir .. "/%{prj.name}")
    
    
    files 
    {
        "PowerPCOperandDecoder/includes/**.h",
        "PowerPCOperandDecoder/src/**.c",
        "PowerPCOperandDecoder/includes/**.hpp",
        "PowerPCOperandDecoder/src/**.cpp",

        --ImGUI file includes
       -- "Libraries\\imgui/imgui.h",
       -- "Libraries\\imgui/imgui.cpp",
       -- "Libraries\\imgui/imgui_demo.cpp",
       -- "Libraries\\imgui/imgui_draw.cpp",
       -- "Libraries\\imgui/imgui_widgets.cpp",
       -- "Libraries\\imgui/imgui_tables.cpp",
       -- "Libraries\\imgui/backends/imgui_impl_vulkan.h",
       -- "Libraries\\imgui/backends/imgui_impl_vulkan.cpp",
       -- "Libraries\\imgui/backends/imgui_impl_glfw.h",
       -- "Libraries\\imgui/backends/imgui_impl_glfw.cpp",
    }

    includedirs
    {
        "PowerPCOperandDecoder/includes",
        "C:\\GameDev\\BTDSTD\\includes"
        
      --  "Libraries\\yaml-cpp\\include",
       -- "Libraries\\glm",
      --  "Libraries\\glfw\\include",
       -- "Libraries\\Assimp\\include",
       -- "Libraries\\VulkanMemoryAllocator\\include",
       -- "Libraries\\imgui",
       -- "Libraries\\imgui/backends",

       -- "C:\\VulkanSDK\\1.3.275.0\\Include",

       -- "Libraries\\Steam-public"
    }
    
    links
    {
       -- "yaml-cpp",
      --  "GLFW",
      --  "C:\\VulkanSDK\\1.3.275.0\\Lib\\vulkan-1.lib",
        --"Libraries\\Assimp\\assimp-vc143-mt.lib"
       -- "Libraries\\redistributable_bin\\win64\\steam_api64.lib"
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
      --  cdialect "C99"
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
    
        links
        {
            
        }
    
    filter "configurations:Release"
        defines "BTD_RELEASE"
        optimize "On"
    
        flags
        {
            
        }

        links
        {
           
        }
    
    filter "configurations:Dist"
        defines "BTD_DIST"
        optimize "On"
    
        defines
        {
            "NDEBUG"
        }
    
        flags
        {
           
        }
    
        links
        {
           
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

        --ImGUI file includes
       -- "Libraries\\imgui/imgui.h",
       -- "Libraries\\imgui/imgui.cpp",
       -- "Libraries\\imgui/imgui_demo.cpp",
       -- "Libraries\\imgui/imgui_draw.cpp",
       -- "Libraries\\imgui/imgui_widgets.cpp",
       -- "Libraries\\imgui/imgui_tables.cpp",
       -- "Libraries\\imgui/backends/imgui_impl_vulkan.h",
       -- "Libraries\\imgui/backends/imgui_impl_vulkan.cpp",
       -- "Libraries\\imgui/backends/imgui_impl_glfw.h",
       -- "Libraries\\imgui/backends/imgui_impl_glfw.cpp",
    }

    includedirs
    {
        "PowerPCParser/includes",
        "PowerPCOperandDecoder/includes",
        "C:\\GameDev\\BTDSTD\\includes"
        
      --  "Libraries\\yaml-cpp\\include",
       -- "Libraries\\glm",
      --  "Libraries\\glfw\\include",
       -- "Libraries\\Assimp\\include",
       -- "Libraries\\VulkanMemoryAllocator\\include",
       -- "Libraries\\imgui",
       -- "Libraries\\imgui/backends",

       -- "C:\\VulkanSDK\\1.3.275.0\\Include",

       -- "Libraries\\Steam-public"
    }
    
    links
    {
       -- "yaml-cpp",
      --  "GLFW",
      --  "C:\\VulkanSDK\\1.3.275.0\\Lib\\vulkan-1.lib",
        --"Libraries\\Assimp\\assimp-vc143-mt.lib"
       -- "Libraries\\redistributable_bin\\win64\\steam_api64.lib"
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
      --  cdialect "C99"
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
    
        links
        {
            
        }
    
    filter "configurations:Release"
        defines "BTD_RELEASE"
        optimize "On"
    
        flags
        {
            
        }

        links
        {
           
        }
    
    filter "configurations:Dist"
        defines "BTD_DIST"
        optimize "On"
    
        defines
        {
            "NDEBUG"
        }
    
        flags
        {
           
        }
    
        links
        {
           
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

        --ImGUI file includes
       -- "Libraries\\imgui/imgui.h",
       -- "Libraries\\imgui/imgui.cpp",
       -- "Libraries\\imgui/imgui_demo.cpp",
       -- "Libraries\\imgui/imgui_draw.cpp",
       -- "Libraries\\imgui/imgui_widgets.cpp",
       -- "Libraries\\imgui/imgui_tables.cpp",
       -- "Libraries\\imgui/backends/imgui_impl_vulkan.h",
       -- "Libraries\\imgui/backends/imgui_impl_vulkan.cpp",
       -- "Libraries\\imgui/backends/imgui_impl_glfw.h",
       -- "Libraries\\imgui/backends/imgui_impl_glfw.cpp",
    }

    includedirs
    {
        "PCC/includes",

        "PowerPCOperandDecoder/includes",
        "PowerPCParser/includes",
        "C:\\GameDev\\BTDSTD\\includes"
        
      --  "Libraries\\yaml-cpp\\include",
       -- "Libraries\\glm",
      --  "Libraries\\glfw\\include",
       -- "Libraries\\Assimp\\include",
       -- "Libraries\\VulkanMemoryAllocator\\include",
       -- "Libraries\\imgui",
       -- "Libraries\\imgui/backends",

       -- "C:\\VulkanSDK\\1.3.275.0\\Include",

       -- "Libraries\\Steam-public"
    }
    
    links
    {
       -- "yaml-cpp",
      --  "GLFW",
      --  "C:\\VulkanSDK\\1.3.275.0\\Lib\\vulkan-1.lib",
        --"Libraries\\Assimp\\assimp-vc143-mt.lib"
       -- "Libraries\\redistributable_bin\\win64\\steam_api64.lib"

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
      --  cdialect "C99"
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
    
        links
        {
            
        }
    
    filter "configurations:Release"
        defines "BTD_RELEASE"
        optimize "On"
    
        flags
        {
            
        }

        links
        {
           
        }
    
    filter "configurations:Dist"
        defines "BTD_DIST"
        optimize "On"
    
        defines
        {
            "NDEBUG"
        }
    
        flags
        {
           
        }
    
        links
        {
           
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

        --ImGUI file includes
       -- "Libraries\\imgui/imgui.h",
       -- "Libraries\\imgui/imgui.cpp",
       -- "Libraries\\imgui/imgui_demo.cpp",
       -- "Libraries\\imgui/imgui_draw.cpp",
       -- "Libraries\\imgui/imgui_widgets.cpp",
       -- "Libraries\\imgui/imgui_tables.cpp",
       -- "Libraries\\imgui/backends/imgui_impl_vulkan.h",
       -- "Libraries\\imgui/backends/imgui_impl_vulkan.cpp",
       -- "Libraries\\imgui/backends/imgui_impl_glfw.h",
       -- "Libraries\\imgui/backends/imgui_impl_glfw.cpp",
    }

    includedirs
    {
        "PPC_StaticRecompLayer/includes",
        "PowerPCOperandDecoder/includes",
        "C:\\GameDev\\BTDSTD\\includes"
        
      --  "Libraries\\yaml-cpp\\include",
       -- "Libraries\\glm",
      --  "Libraries\\glfw\\include",
       -- "Libraries\\Assimp\\include",
       -- "Libraries\\VulkanMemoryAllocator\\include",
       -- "Libraries\\imgui",
       -- "Libraries\\imgui/backends",

       -- "C:\\VulkanSDK\\1.3.275.0\\Include",

       -- "Libraries\\Steam-public"
    }
    
    links
    {
       -- "yaml-cpp",
      --  "GLFW",
      --  "C:\\VulkanSDK\\1.3.275.0\\Lib\\vulkan-1.lib",
        --"Libraries\\Assimp\\assimp-vc143-mt.lib"
       -- "Libraries\\redistributable_bin\\win64\\steam_api64.lib"
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
      --  cdialect "C99"
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
    
        links
        {
            
        }
    
    filter "configurations:Release"
        defines "BTD_RELEASE"
        optimize "On"
    
        flags
        {
            
        }

        links
        {
           
        }
    
    filter "configurations:Dist"
        defines "BTD_DIST"
        optimize "On"
    
        defines
        {
            "NDEBUG"
        }
    
        flags
        {
           
        }
    
        links
        {
           
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

    --ImGUI file includes
   -- "Libraries\\imgui/imgui.h",
   -- "Libraries\\imgui/imgui.cpp",
   -- "Libraries\\imgui/imgui_demo.cpp",
   -- "Libraries\\imgui/imgui_draw.cpp",
   -- "Libraries\\imgui/imgui_widgets.cpp",
   -- "Libraries\\imgui/imgui_tables.cpp",
   -- "Libraries\\imgui/backends/imgui_impl_vulkan.h",
   -- "Libraries\\imgui/backends/imgui_impl_vulkan.cpp",
   -- "Libraries\\imgui/backends/imgui_impl_glfw.h",
   -- "Libraries\\imgui/backends/imgui_impl_glfw.cpp",
}

includedirs
{
    "PCASM_StructRename/includes",

    "PowerPCOperandDecoder/includes",
    "PowerPCParser/includes",
    "C:\\GameDev\\BTDSTD\\includes"
    
  --  "Libraries\\yaml-cpp\\include",
   -- "Libraries\\glm",
  --  "Libraries\\glfw\\include",
   -- "Libraries\\Assimp\\include",
   -- "Libraries\\VulkanMemoryAllocator\\include",
   -- "Libraries\\imgui",
   -- "Libraries\\imgui/backends",

   -- "C:\\VulkanSDK\\1.3.275.0\\Include",

   -- "Libraries\\Steam-public"
}

links
{
   -- "yaml-cpp",
  --  "GLFW",
  --  "C:\\VulkanSDK\\1.3.275.0\\Lib\\vulkan-1.lib",
    --"Libraries\\Assimp\\assimp-vc143-mt.lib"
   -- "Libraries\\redistributable_bin\\win64\\steam_api64.lib"

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
  --  cdialect "C99"
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

    links
    {
        
    }

filter "configurations:Release"
    defines "BTD_RELEASE"
    optimize "On"

    flags
    {
        
    }

    links
    {
       
    }

filter "configurations:Dist"
    defines "BTD_DIST"
    optimize "On"

    defines
    {
        "NDEBUG"
    }

    flags
    {
       
    }

    links
    {
       
    }