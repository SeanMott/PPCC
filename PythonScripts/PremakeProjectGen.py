"""
Various functions and objects for premake projects for BTD
"""

from enum import Enum

#adds configurations
def PremakeGen_ConfigureOptions_Default(projectStr):
   return projectStr + """configurations
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
    }\n\n"""

#adds normal output directory format string
def PremakeGen_OutputDirFormat_Default(projectStr):
    return projectStr + "outputdir = \"%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}-%{cfg.startproject}\"\n\n"

#adds a premake include
def PremakeGen_AddPremakeInclude(projectStr, path):
    return projectStr + "include \"" + path + "\"\n"

#defines the project kind via enum
class ProjectKind(Enum):
    StaticLib = 0
    DLL = 1
    EXE = 2

#sets the project name, type, and language
def PremakeGen_ProjectStart(projectStr, projectName, projectKind, language = "C++"):
    projectStr = projectStr + "\nproject \"" + projectName + "\"\n"

    if(projectKind == ProjectKind.StaticLib):
        projectStr = projectStr + "kind \"StaticLib\"\n"
    else:
        projectStr = projectStr + "kind \"KIND PASSED IN WAS NOT VALID\"\n"

    return projectStr + "language \"" + language + "\"\n"

#sets the project name, location type, and language
def PremakeGen_ProjectStart(projectStr, projectName, location, projectKind, language = "C++"):
    projectStr = projectStr + "\nproject \"" + projectName + "\"\n"
    projectStr = projectStr + "\nlocation \"" + location + "\"\n"

    if(projectKind == ProjectKind.StaticLib):
        projectStr = projectStr + "kind \"StaticLib\"\n"
    else:
        projectStr = projectStr + "kind \"KIND PASSED IN WAS NOT VALID\"\n"

    return projectStr + "language \"" + language + "\"\n"

#sets the directories for output and temp output
def PremakeGen_ObjectAndTargetDirFormat_Default(projectStr):
    return projectStr + "\ntargetdir (\"bin/\" .. outputdir .. \"/%{prj.name}\")\nobjdir (\"bin-obj/\" .. outputdir .. \"/%{prj.name}\")\n"

#starts the section for adding source files
def PremakeGen_SourceFiles_Start(projectStr):
    return projectStr + """\n\nfiles 
{
    "includes/**.h",
    "src/**.c",
    "includes/**.hpp",
    "src/**.cpp",\n"""

#ends the section for adding source files
def PremakeGen_SourceFiles_End(projectStr):
    return projectStr + "}"

#adds default Imgui source files includes
def PremakeGen_SourceFiles_ImGuiDefault(projectStr, imGUIDir):
    projectStr = projectStr + "\n\n\t--ImGUI file includes\n"
    projectStr = projectStr + "\t\"" + imGUIDir + "/imgui.h\",\n"
    projectStr = projectStr + "\t\"" + imGUIDir + "/imgui.cpp\",\n"
    projectStr = projectStr + "\t\"" + imGUIDir + "/imgui_demo.cpp\",\n"
    projectStr = projectStr + "\t\"" + imGUIDir + "/imgui_draw.cpp\",\n"
    projectStr = projectStr + "\t\"" + imGUIDir + "/imgui_widgets.cpp\",\n"
    projectStr = projectStr + "\t\"" + imGUIDir + "/imgui_tables.cpp\",\n"
    projectStr = projectStr + "\t\"" + imGUIDir + "/backends/imgui_impl_vulkan.h\",\n"
    projectStr = projectStr + "\t\"" + imGUIDir + "/backends/imgui_impl_vulkan.cpp\",\n"
    projectStr = projectStr + "\t\"" + imGUIDir + "/backends/imgui_impl_glfw.h\",\n"
    return projectStr + "\t\"" + imGUIDir + "/backends/imgui_impl_glfw.cpp\",\n\n"

#start section of includes
def PremakeGen_IncludeDir_Start(projectStr):
    return projectStr + """\n\nincludedirs
{
    "includes",\n\n
"""

#end section of includes
def PremakeGen_IncludeDir_End(projectStr):
    return projectStr + "}\n\n"

#adds include directory
def PremakeGen_IncludeDir_AddDir(projectStr, dir):
    return projectStr + "\t\"" + dir + "\",\n"

#adds include directory with /includes
def PremakeGen_IncludeDir_AddIncludeDir(projectStr, dir):
    return projectStr + "\t\"" + dir + "/include\",\n"

#defines the links section
def PremakeGen_Links(projectStr, linkPaths):
    projectStr = projectStr + "links \n{\n"

    for link in linkPaths:
        projectStr = projectStr + "\t\"" + link + "\",\n"

    return projectStr + "}\n\n"

#defines a define/macro section
def PremakeGen_DefineMacros(projectStr, defines):
    projectStr = projectStr + "defines \n{\n"

    for d in defines:
        projectStr = projectStr + "\t\"" + d + "\",\n"

    return projectStr + "}\n\n"

#adds a flags section
def PremakeGen_Flags_Default(projectStr):
    return projectStr + """flags
{
    "NoRuntimeChecks",
    "MultiProcessorCompile"
}\n\n"""

#adds default windows system filter
def PremakeGen_WindowsPlatform_Default(projectStr):
    return projectStr + """filter \"system:windows\"
    cppdialect \"C++20\"
    --cdialect \"C99\"
    staticruntime \"On\"
    systemversion \"latest\"\n\n"""

#default configure filter for debug
def PremakeGen_FilterConfiguration_Debug_Default(projectStr):
    return projectStr + """filter \"configurations:Debug\"
    defines \"BTD_DEBUG\"
    symbols \"On\"\n\n"""

#default configure filter for release
def PremakeGen_FilterConfiguration_Release_Default(projectStr):
    return projectStr + """filter \"configurations:Release\"
    defines \"BTD_RELEASE\"
    optimize \"On\"\n\n"""

#default configure filter for dist
def PremakeGen_FilterConfiguration_Dist_Default(projectStr):
    return projectStr + """filter \"configurations:Dist\"
    defines \"BTD_DIST\"
    optimize \"On\"\n\n"""