"""
Defines various IO based utils for Python in BTD scripts
"""

import glob
import shutil
import os

#deletes a list of files given a list of paths
def BTDIO_Recursive_DeleteFileList(filePaths):
    for f in filePaths: #first pass unlink everything
        if(os.path.isfile(f) and os.path.islink(f)):
            os.unlink(f)

    for f in filePaths: #second pass, delete them
        if(os.path.isfile(f)):
            os.remove(f)

#deletes a list of folders given a list of paths
def BTDIO_Recursive_DeleteFolderList(folderPaths):
    for f in folderPaths:
        if(os.path.isdir(f)):
            shutil.rmtree(f)

#goes through the contents of a folder and deletes every file recusively

#goes through the contents of a folder and deletes every folder recusively

#deletes a folder and all it's contents
def BTDIO_Recursive_DeleteFolder(dir):
    shutil.rmtree(dir)
    
    #files = glob.glob(dir + '/**/*', recursive=True, include_hidden=True)
    #BTDIO_Recursive_DeleteFileList(files)
    #BTDIO_Recursive_DeleteFolderList(files)

    #double check all hideen and dot files are gone too
    #files = glob.glob(dir + '/**/.*', recursive=True)
    #BTDIO_Recursive_DeleteFileList(files)
    #BTDIO_Recursive_DeleteFolderList(files)
    
#converts a path to not use any back slashes
def BTDIO_FixBackSlashes(path):
    correctedPath = ""
    for c in range(len(path)):
        if(path[c] == '\\'):
            correctedPath = correctedPath + '/'
        else:
            correctedPath = correctedPath + path[c]

    return correctedPath