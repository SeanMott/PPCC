"""
Bytes The Dust Shader compiling toolchain
"""

import glob
import subprocess
import os
import colorama
from colorama import Fore, Back, Style

#gets the shader compiler
shaderCompiler = "C:\\VulkanSDK\\1.3.275.0\\Bin\\glslc.exe" #glslangValidator.exe"

#inits color text
colorama.init(autoreset=True)

#goes through the source shaders and compiles them
print(Fore.CYAN + "Compiling Shaders......\n")
files = glob.glob("Code\\*")
for file in files:
    name = os.path.basename(file)
    print(Fore.MAGENTA + "-Compiling Shader: " + name)
    subprocess.call([shaderCompiler, file, "-o", "Compiled\\" + name + ".SPRV"])

print(Fore.GREEN + "\nFinished compiling Shaders")