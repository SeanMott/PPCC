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
    print(depName + " was found at \"" + Fore.GREEN + depPath + Fore.WHITE + "\"")
    return True

#tells the user how to get Vulkan
def BTDDep_Vulkan_HowToGet():
    print("\nBTD projects require a minimum Vulkan version of " + Fore.YELLOW + "1.3" + Fore.WHITE + ".")
    print("The specific version numbers after the " + Fore.YELLOW + "1.3" + Fore.WHITE + " DOES NOT matter.")
    print("BTDSTD's Vulkan implemntation is designed to work on many systems. So long as it supports " + Fore.YELLOW + "1.3" + Fore.WHITE + " it will work.")
    print("Please go to " + Fore.CYAN + "https://vulkan.lunarg.com/sdk/home" + Fore.WHITE + " to get the latest SDK.")
    print("Once the SDK is installed, run this again.")

#prompts the user for Vulkan
def BTDDep_Vulkan_PromptForVulkan():

    print("\n" + Fore.RED + "Vulkan " + Fore.WHITE + "is required for BTD projects on " + Fore.CYAN + "Windows" + Fore.WHITE + " and " + Fore.CYAN + "Linux" + Fore.WHITE + ".", end="\n\n")

    vulkanPrompt_Options = ["I have the Vulkan SDK Installed", "I do not, how do I get it?", "Nevermind Ray"]
    vulkanPrompt_Answer = inquirer.list_input("Do you have the Vulkan SDK Installed?",
    choices=vulkanPrompt_Options)
    
    if(vulkanPrompt_Answer == vulkanPrompt_Options[2]): #if they wish to leave
        print("\nUnderstood, have a nice day :3")
        return "Nevermind Ray"

    if(vulkanPrompt_Answer == vulkanPrompt_Options[1]): #if they don't have Vulkan
        BTDDep_Vulkan_HowToGet()
        return "Nevermind Ray"

    #if they have Vulkan
    print("\nWhen installing Vulkan, it would have installed in a path like \"" + Fore.CYAN + "C:/VulkanSDK/1.3.275.0" + Fore.WHITE + "\"")
    print("The specific version numbers after the " + Fore.YELLOW + "1.3" + Fore.WHITE + " DOES NOT matter.")
    print("BTDSTD's Vulkan implemntation is designed to work on many systems. So long as it supports " + Fore.YELLOW + "1.3" + Fore.WHITE + " it will work.")
    print("The installer only needs the \"" + Fore.CYAN + "C:/VulkanSDK/" + Fore.WHITE + "\" part of the path.")
    print("This is the common place all Vulkan SDK versions will be installed into. The installer will take care of getting a specific useable version.\n")

    #prompt for path
    return inquirer.prompt([inquirer.Path('VulkanSDK',
                 message="Where is the Vulkan SDK located? (a / must be at the end of your path)",
                 path_type=inquirer.Path.DIRECTORY)])['VulkanSDK']

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
        BTDDep_Vulkan_HowToGet()
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