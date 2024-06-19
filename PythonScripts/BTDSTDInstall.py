"""
A Python installer script for the Bytes The Dust C++ Standard Library
"""

#from yaspin import yaspin
import pyfiglet

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

#the repo github url
BTDSTD_GIT_REPO_URL = "https://github.com/SeanMott/BTDSTD-Neo"
BTDSTD_DEPS_GIT_REPO_URL = "https://github.com/SeanMott/BTDSTD_Deps"

#defines the Host OS options
HOST_OS_OPTIONS = ["Windows"] #, "Mac (Intel)", "Mac (M series)", "Linux"]

#defines the build target platform options
TARGET_PLATFORM_OPTIONS = ["Windows", "Mac (Intel)", "Mac (M series)", "Linux", "Android", "ISO", "Web", "VR", "AR"]

#generates a premake file for BTDSTD
def BTDInstaller_Util_GenerateBTDSTDPremakeFile(installDir, YamlCppDir, GLFWDir, GLMDir, ImGUIDir, vulkanSDK, AssimpDir):
    print("\n\n" + Fore.CYAN + "Ajusting BTDSTD to use the found dependices...")
    BTDSTDPremakeFileStr = ""
    BTDSTDPremakeFileStr = PremakeGen_ConfigureOptions_Default(BTDSTDPremakeFileStr)
    BTDSTDPremakeFileStr = PremakeGen_OutputDirFormat_Default(BTDSTDPremakeFileStr)

    BTDSTDPremakeFileStr = PremakeGen_AddPremakeInclude(BTDSTDPremakeFileStr, YamlCppDir)
    BTDSTDPremakeFileStr = PremakeGen_AddPremakeInclude(BTDSTDPremakeFileStr, GLFWDir)
    
    BTDSTDPremakeFileStr = PremakeGen_ProjectStart(BTDSTDPremakeFileStr,
     "BTDSTD", ProjectKind.StaticLib)

    BTDSTDPremakeFileStr = PremakeGen_ObjectAndTargetDirFormat_Default(BTDSTDPremakeFileStr)

    #adds files to include
    BTDSTDPremakeFileStr = PremakeGen_SourceFiles_Start(BTDSTDPremakeFileStr)

    BTDSTDPremakeFileStr = PremakeGen_SourceFiles_ImGuiDefault(BTDSTDPremakeFileStr, ImGUIDir)

    BTDSTDPremakeFileStr = PremakeGen_SourceFiles_End(BTDSTDPremakeFileStr)

    #adds include directories
    BTDSTDPremakeFileStr = PremakeGen_IncludeDir_Start(BTDSTDPremakeFileStr)

    BTDSTDPremakeFileStr = PremakeGen_IncludeDir_AddIncludeDir(BTDSTDPremakeFileStr, GLFWDir)
    BTDSTDPremakeFileStr = PremakeGen_IncludeDir_AddIncludeDir(BTDSTDPremakeFileStr, YamlCppDir)
    BTDSTDPremakeFileStr = PremakeGen_IncludeDir_AddIncludeDir(BTDSTDPremakeFileStr, vulkanSDK)
    BTDSTDPremakeFileStr = PremakeGen_IncludeDir_AddDir(BTDSTDPremakeFileStr, GLMDir)
    BTDSTDPremakeFileStr = PremakeGen_IncludeDir_AddDir(BTDSTDPremakeFileStr, ImGUIDir)
    BTDSTDPremakeFileStr = PremakeGen_IncludeDir_AddDir(BTDSTDPremakeFileStr, ImGUIDir + "/backends")

    BTDSTDPremakeFileStr = PremakeGen_IncludeDir_End(BTDSTDPremakeFileStr)

    #adds link directories
    BTDSTDPremakeFileStr = PremakeGen_Links(BTDSTDPremakeFileStr, ["yaml-cpp", 
    "GLFW", vulkanSDK + "/Lib/vulkan-1.lib"])

    #add defines
    BTDSTDPremakeFileStr = PremakeGen_DefineMacros(BTDSTDPremakeFileStr, ["GLFW_INCLUDE_NONE",
        "GLM_FORCE_RADIANS",
        "GLM_FORCE_DEPTH_ZERO_TO_ONE",
        "GLM_ENABLE_EXPERIMENTAL"])

    #add flags
    BTDSTDPremakeFileStr = PremakeGen_Flags_Default(BTDSTDPremakeFileStr)

    #add windows platform
    BTDSTDPremakeFileStr = PremakeGen_WindowsPlatform_Default(BTDSTDPremakeFileStr)

    #add defines
    BTDSTDPremakeFileStr = PremakeGen_DefineMacros(BTDSTDPremakeFileStr, ["Window_Build",
            "Desktop_Build"])
    
    #add debug config
    BTDSTDPremakeFileStr = PremakeGen_FilterConfiguration_Debug_Default(BTDSTDPremakeFileStr)

    #add links
    BTDSTDPremakeFileStr = PremakeGen_Links(BTDSTDPremakeFileStr,
     [AssimpDir + "/lib/RelWithDebInfo/assimp-vc143-mt.lib",
     AssimpDir + "/lib/RelWithDebInfo/draco.lib"])

    #add release config
    BTDSTDPremakeFileStr = PremakeGen_FilterConfiguration_Release_Default(BTDSTDPremakeFileStr)

    #add links
    BTDSTDPremakeFileStr = PremakeGen_Links(BTDSTDPremakeFileStr, [AssimpDir + "/lib/RelWithDebInfo/assimp-vc143-mt.lib",
            AssimpDir + "/lib/RelWithDebInfo/draco.lib"])

    #add dist config
    BTDSTDPremakeFileStr = PremakeGen_FilterConfiguration_Dist_Default(BTDSTDPremakeFileStr)

    #add defines
    BTDSTDPremakeFileStr = PremakeGen_DefineMacros(BTDSTDPremakeFileStr, ["NDEBUG"])

    #add links
    BTDSTDPremakeFileStr = PremakeGen_Links(BTDSTDPremakeFileStr,
     [AssimpDir + "/lib/Release/assimp-vc143-mt.lib", AssimpDir + "/lib/Release/draco.lib"])

    f = open(installDir + "/BTDSTD/Premake5.lua", "w")
    f.write(BTDSTDPremakeFileStr)
    f.close()

#generates a deps lua file for BTDSTD projects
def BTDInstaller_Util_GenerateBTDSTD_ProjectDeps(installDir, BTDSTD_Dep_Dir, YamlCppDir, GLFWDir, GLMDir, ImGUIDir, vulkanSDK, AssimpDir):
    print("\n\n" + Fore.CYAN + "Generating Project Dependicy list for projects to use the found dependices...")

    projectDepStr = "BTDSTD_DIR_PATH = \"" + installDir + "/BTDSTD\"\n"
    projectDepStr = projectDepStr + "BTDSTD_INCLUDE_DIR_PATH = \"" + installDir + "/BTDSTD/includes\"\n"
    projectDepStr = projectDepStr + "BTDSTD_DEP_DIR_PATH = \"" + BTDSTD_Dep_Dir + "\"\n"
    projectDepStr = projectDepStr + "GLFW_DIR_PATH = \"" + GLFWDir + "\"\n"
    projectDepStr = projectDepStr + "GLM_DIR_PATH = \"" + GLMDir + "\"\n"
    projectDepStr = projectDepStr + "YAML_CPP_DIR_PATH = \"" + YamlCppDir + "\"\n"
    projectDepStr = projectDepStr + "ASSIMP_DIR_PATH = \"" + AssimpDir + "\"\n"
    projectDepStr = projectDepStr + "IMGUI_DIR_PATH = \"" + ImGUIDir + "\"\n"
    projectDepStr = projectDepStr + "VULKAN_DIR_PATH = \"" + vulkanSDK + "\"\n"
    projectDepStr = projectDepStr + "include \"" + installDir + "/BTDSTD\"\n"

    f = open(installDir + "/BTDSTD/ProjectDeps.lua", "w")
    f.write(projectDepStr)
    f.close()

#if the user wishes to make a new instalation of the BTDSTD
def BTDInstallerMode_NewInstall():
    print("Great, let me just just get some intel.")

    HostOS = inquirer.list_input("What OS is this machine?", choices=HOST_OS_OPTIONS)

    #targetOSes = inquirer.list_input("What platforms are you targeting?", choices=TARGET_PLATFORM_OPTIONS)

    #isPreferedDepDir = inquirer.list_input("Is there a directory you like to keep all your C++ libraries in?", choices=["yes", "no"])
    #get prfered directory

    #if no prefered directory, where would you like the BTDSTD directory
    installDir = inquirer.prompt([inquirer.Path('installDir',
                 message="Where would you like the BTDSTD installed? (a / must be at the end of your path)",
                 path_type=inquirer.Path.DIRECTORY)])['installDir']
    #correct any back slashes
    installDir = BTDIO_FixBackSlashes(installDir)

    #would you like the docs?

    #would you like samples using it?

    #start install and set up
    print(Fore.CYAN + "---STARTING BTDSTD INSTALL---")
    
    #prompts for Vulkan SDK
    vulkanSDK = BTDDep_Vulkan_PromptForVulkan()
    if(vulkanSDK == "Nevermind Ray"):
        return

    #validates Vulkan
    print(Fore.MAGENTA + "\nValidating Deps...")
    vulkanSDK = BTDDep_Validate_Vulkan(vulkanSDK)
    if(vulkanSDK == ""):
        print(Fore.RED + "Aborting due to missing Vulkan SDK!")
        return

    #gets BTDSTD, clears old one if exists
    print("\n\n" + Fore.MAGENTA + "Getting BTDSTD from Github....")
    BTDGit_DeleteFolderAndGitClone(installDir, "BTDSTD", BTDSTD_GIT_REPO_URL)
    
    print("\n\n" + Fore.MAGENTA + "Getting BTDSTD Deps from Github....")
    BTDGit_DeleteFolderAndGitClone(installDir, "BTDSTD-Deps", BTDSTD_DEPS_GIT_REPO_URL)
    BTDSTD_Dep_Dir = installDir + "/BTDSTD-Deps"
    GLFWDir = BTDDep_Validate(BTDSTD_Dep_Dir, "glfw", "GLFW")
    GLMDir = BTDDep_Validate(BTDSTD_Dep_Dir, "glm", "GLM")
    YamlCppDir = BTDDep_Validate(BTDSTD_Dep_Dir, "yaml-cpp", "YAML Cpp")
    AssimpDir = BTDDep_Validate(BTDSTD_Dep_Dir, "Assimp_DLLs_Libs", "Assimp")
    ImGUIDir = BTDDep_Validate(BTDSTD_Dep_Dir, "imgui", "ImGUI")
    
    #generates BTDSTD premake file
    BTDInstaller_Util_GenerateBTDSTDPremakeFile(installDir, YamlCppDir, GLFWDir, GLMDir, ImGUIDir, vulkanSDK, AssimpDir)
    
    print("\n\n" + Fore.GREEN + "BTDSTD is ready to go!")

    #generates a BTDSTD project dep lua file
    BTDInstaller_Util_GenerateBTDSTD_ProjectDeps(installDir, BTDSTD_Dep_Dir, YamlCppDir, GLFWDir, GLMDir, ImGUIDir, vulkanSDK, AssimpDir)

    print("\n\n" + Fore.GREEN + "Everything is ready, happy programming! :3")

#if the user wishes to modify their exisiting instalation of the BTDSTD
def BTDInstallerMode_Modify():
    pass

#if the user wishes to DELETE their exisiting instalation of the BTDSTD
def BTDInstallerMode_Delete():
    pass

#big fuck title for being dramatic
print(Fore.CYAN + pyfiglet.figlet_format("BTD Util Installer"))

#introduction to Ray and what we're doing
print("Howdy, welcome to the " + Fore.CYAN + "Bytes The Dust" + Fore.WHITE + " C++ Standard Library installer.")
print("I'm " + Fore.GREEN + "Ray" + Fore.WHITE + ", I'll be your guide through this installer.")
print("We're gonna check all your system dependicies and bring down anything we need.\nBefore finally pulling the BTDSTD down at your desired location.",
end="\n\n")

#warns them that installing requires git as a system path
print(Fore.RED + "WARNING: Git is required to be in the system PATH for some operations.")
print("If you can't run 'git' from anywhere in the command line. Please hit the Nevermind option.")
print("Make sure Git is in your system PATH, then run me again. I promise I'll still be here.",
end="\n\n")

#prompt them to continue with the install
continueWithInstall_options = ["New install", "Modify a existing install", "DELETE a existing install", "Nevermind Ray"]
continueWithInstall = inquirer.list_input("What are we doing today?",
 choices=continueWithInstall_options)
if(continueWithInstall == continueWithInstall_options[3]): #if they wish to leave
    print("Understood, have a nice day :3")

elif(continueWithInstall == continueWithInstall_options[0]): #new install
    BTDInstallerMode_NewInstall()
#elif(continueWithInstall == continueWithInstall_options[1]): #modify install
#    BTDInstallerMode_ModifyInstall()
#elif(continueWithInstall == continueWithInstall_options[2]): #delete install
#    BTDInstallerMode_DeleteInstall()
else: #option not aviable
    print("We're very sorry, that option is not supported at the moment.")
    print("Make sure you are using the latest version of the program. You are currently on " +
     Fore.CYAN + PROG_VERSION + Fore.WHITE + " (" + PROG_STATUS_COLOR + PROG_STATUS + Fore.WHITE + ")\n" +
     "Updates can found at the Bytes The Dust Website (" + Fore.BLUE + "https://bytesthedust.company/BTDSTD" + Fore.WHITE + ").\n" +
     "Or at the Bytes The Dust Github (" + Fore.BLUE + "https://github.com/SeanMott/BTDPythonScipts" + Fore.WHITE + ").")