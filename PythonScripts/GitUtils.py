"""
Defines various functions for handling git operations in Python
"""

from git import Repo

import colorama
from colorama import Fore, Back, Style

from IOUtils import *

#git clones a repo, deletes a folder if it matches the desired name
def BTDGit_DeleteFolderAndGitClone(dirToCloneInto, desiredGitCloneFolderName, gitURL):

    #checks if the folder already exists, if so, we delete it
    dir = dirToCloneInto + "/" + desiredGitCloneFolderName
    if(os.path.exists(dir)):
        print(Fore.YELLOW + "deleting previous repo at " + Fore.WHITE + "\"" + 
        Fore.CYAN + dir + Fore.WHITE + "\"")
        #deletes the folder via command line
        os.system("rm -rf " + dir)

    #clones the repo
    repo = Repo.clone_from(gitURL, dir)
    print("repo pulled down at \"" + Fore.GREEN + dir + Fore.WHITE + "\"")