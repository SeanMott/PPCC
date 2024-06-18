"""
Defines various functions used by installers, project gens, and build systems
For Validating Bytes The Dust common project dependicies
"""

import inquirer
import colorama
import os
import glob
from colorama import Fore, Back, Style

from IOUtils import *

SDK_PATH_DEFAULT_NO_PATH_FOUND = "No Dep Found"

#prints to the screen if the SDK/Dep was found
def BTDDep_PrintIfDepWasFound(depPath, depName):
    if depPath == SDK_PATH_DEFAULT_NO_PATH_FOUND: #if it wasn't found
        print(Fore.RED + depName + " was not found!")
        return False

    #if it was
    print(depName + " was found at \"" + Fore.CYAN + depPath + Fore.WHITE + "\"")
    return True

#validates Vulkan is on the system
def BTDDep_Validate_Vulkan(vulkanSDK):
    #checks for Dep
    depPath = SDK_PATH_DEFAULT_NO_PATH_FOUND
    
    #check for any version at minimum 1.3
    SDKs = glob.glob(vulkanSDK + '/1.3.*', recursive=False)
    for SDK in SDKs:
        depPath = SDK

    #correct any back slashes
    depPath = BTDIO_FixBackSlashes(depPath)

    #if failed prompt user to install
    if(BTDDep_PrintIfDepWasFound(depPath, "Vulkan SDK") == False):
        print("\tVulkan SDK is not on your system. The minimum version required is " +
        Fore.YELLOW + "1.3" + Fore.WHITE + ".")
        print("\tPlease go to " + Fore.CYAN + "https://vulkan.lunarg.com/sdk/home" + Fore.WHITE + " to get the latest SDK.")
        print("\tOnce the SDK is installed, run this again.")
        return ""

    return depPath

#validates OpenXR is on the system
def BTDDep_Validate_OpenXR():
    #checks for Dep
    depPath = SDK_PATH_DEFAULT_NO_PATH_FOUND
    
    #if failed prompt user to install
    wasFound = BTDDep_PrintIfDepWasFound(depPath, "OpenXR SDK")
    if(wasFound == False):
       pass

    return wasFound

#validates Steam dev libs is on the system
def BTDDep_Validate_SteamWorks():
   #checks for Dep
    depPath = SDK_PATH_DEFAULT_NO_PATH_FOUND
    
    #if failed prompt user to install
    wasFound = BTDDep_PrintIfDepWasFound(depPath, "Steam Works SDK")
    if(wasFound == False):
       pass

    return wasFound

#checks for a specific BTDSTD dep
def BTDDep_Validate(dir, libFolderName, depName):
     #checks for Dep
    depPath = SDK_PATH_DEFAULT_NO_PATH_FOUND
    if(os.path.exists(dir + "/" + libFolderName)):
        depPath = dir + "/" + libFolderName

    #if failed prompt user to install
    wasFound = BTDDep_PrintIfDepWasFound(depPath, depName)
    if(wasFound == False):
       pass

    return depPath