"""
sets up the PPCC project, remaping any deps
"""

#from yaspin import yaspin
import pyfiglet
import os

#custom BTD Python code
from IOUtils import *
from GitUtils import *
from ValidateDeps import *
from PremakeProjectGen import *

#inits color text
colorama.init(autoreset=True)

#defines the program version and bleeding status
PROG_VERSION = "0.1.0"
PROG_IS_BLEEDING = True
PROG_STATUS = "Bleeding" if PROG_IS_BLEEDING == True else "Stable"
PROG_STATUS_COLOR = Fore.RED if PROG_IS_BLEEDING == True else Fore.GREEN

#defines the Host OS options
HOST_OS_OPTIONS = ["Windows"] #, "Mac (Intel)", "Mac (M series)", "Linux"]

#defines the build target platform options
TARGET_PLATFORM_OPTIONS = ["Windows", "Mac (Intel)", "Mac (M series)", "Linux", "Android", "ISO", "Web", "VR", "AR"]

#if the user doesn't have BTDSTD installed
def NoBTDSTD():
    print("BTDSTD is required in order to build from source.\nWe bundle the BTDSTD installer script with PPCC.")

    isBTDInstalled_options = ["Yes", "No", "Nevermind Ray, I don't want to build from source"]
    continueWithInstall = inquirer.list_input("Would you like me to run the installer?",
    choices=isBTDInstalled_options)
    if(continueWithInstall == isBTDInstalled_options[2]): #if they wish to leave
        print("Understood, have a nice day :3")
        return
    
    if(continueWithInstall == isBTDInstalled_options[1]): #if no
        print("Alright then, if you wish to handle it yourself, it is located in the same folder as this script.")
        return

    isBTDInstalled_options = ["Understood\n\n"]
    inquirer.list_input("When the installer finishes just run this script again, and go to the Build From Source option.",
    choices=isBTDInstalled_options)

    #gets directory and run BTDSTD installer
    d = os.path.dirname(os.path.realpath(__file__))
    os.system("python " + d + "/BTDSTDInstall.py")

#if the user wishes to build PPCC from source
def OptionMode_BuildFromSource():
    print("Great, let me just just get some intel.")

    HostOS = inquirer.list_input("What OS is this machine?", choices=HOST_OS_OPTIONS)

    isBTDInstalled_options = ["Yes", "No", "Nevermind Ray, I don't want to build from source"]
    continueWithInstall = inquirer.list_input("Do you have the Bytes The Dust Standard Library (BTDSTD) installed?",
    choices=isBTDInstalled_options)
    if(continueWithInstall == isBTDInstalled_options[2]): #if they wish to leave
        print("Understood, have a nice day :3")
        return

    if(continueWithInstall == isBTDInstalled_options[1]): #if they don't have it installed
        NoBTDSTD()
        return

    #if they do have it installed
    BTDSTDDir = inquirer.prompt([inquirer.Path('BTDSTD',
                 message="Where is the BTDSTD located? (a / must be at the end of your path)",
                 path_type=inquirer.Path.DIRECTORY)])['BTDSTD']
    BTDSTDDir = BTDIO_FixBackSlashes(BTDSTDDir)
    print(Fore.GREEN + "BTDSTD found at \"" + BTDSTDDir + "\"")

    print("\n\n" + Fore.CYAN + "Ajusting PPCC to use the found dependices...")

    premakeStr = """workspace "PowerPCToC"
architecture "x64"
startproject "PCASMToCpp\"\n\n"""

    premakeStr = PremakeGen_ConfigureOptions_Default(premakeStr)
    premakeStr = PremakeGen_OutputDirFormat_Default(premakeStr)
    premakeStr = PremakeGen_AddPremakeInclude(premakeStr, BTDSTDDir + "/ProjectDeps.lua")
    premakeStr = PremakeGen_ProjectStart(premakeStr, "PowerPCOperandDecoder", "PowerPCOperandDecoder", ProjectKind.StaticLib)
    PremakeGen_ObjectAndTargetDirFormat_Default(premakeStr)

    premakeStr = premakeStr + """files 
    {
        "PowerPCOperandDecoder/includes/**.h",
        "PowerPCOperandDecoder/src/**.c",
        "PowerPCOperandDecoder/includes/**.hpp",
        "PowerPCOperandDecoder/src/**.cpp",
    }

    includedirs
    {
        "PowerPCOperandDecoder/includes",
        BTDSTD_DIR_INCLUDE_PATH
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
        BTDSTD_DIR_INCLUDE_PATH 
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
        BTDSTD_DIR_INCLUDE_PATH 
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
        BTDSTD_DIR_INCLUDE_PATH
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
    BTDSTD_DIR_INCLUDE_PATH
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

    """

    f = open("../Premake5.lua", "w")
    f.write(premakeStr)
    f.close()

    print("\n\n" + Fore.GREEN + "Everything is ready, happy transcompiling! :3")

#big fuck title for being dramatic
print(Fore.CYAN + pyfiglet.figlet_format("PPCC Setup"))

#introduction to Ray and what we're doing
print("Howdy, welcome to the " + Fore.CYAN + "Power PC C++ Compiler" + Fore.WHITE + " Set Up/How To Script")
print("I'm " + Fore.GREEN + "Ray" + Fore.WHITE + ", I'll be your guide through the set up.")
print("We're gonna make sure you got everything before starting the recompalations.",
end="\n\n")

#warns them that building requires git as a system path
print(Fore.RED + "WARNING: If you are planning to build from source, Git is required to be in the system PATH for some operations.")
print("If you can't run 'git' from anywhere in the command line. Please hit the Nevermind option.")
print("Make sure Git is in your system PATH, then run me again. I promise I'll still be here.",
end="\n\n")

#prompt them to continue with the install
continueWithInstall_options = ["Run PPCC", "Build PPCC From Source", "Nevermind Ray"]
continueWithInstall = inquirer.list_input("What are we doing today?",
 choices=continueWithInstall_options)
if(continueWithInstall == continueWithInstall_options[2]): #if they wish to leave
    print("Understood, have a nice day :3")

#elif(continueWithInstall == continueWithInstall_options[0]): #how to run PPCC
#    BTDInstallerMode_NewInstall()
elif(continueWithInstall == continueWithInstall_options[1]): #build PPCC
    OptionMode_BuildFromSource()
#elif(continueWithInstall == continueWithInstall_options[2]): #delete install
#    BTDInstallerMode_DeleteInstall()
else: #option not aviable
    print("We're very sorry, that option is not supported at the moment.")
    print("Make sure you are using the latest version of the program. You are currently on " +
     Fore.CYAN + PROG_VERSION + Fore.WHITE + " (" + PROG_STATUS_COLOR + PROG_STATUS + Fore.WHITE + ")\n" +
     "Updates can found at Git repo (" + Fore.BLUE + "https://github.com/SeanMott/PPCC/tree/CppStaticRecompile" + Fore.WHITE + ").\n")