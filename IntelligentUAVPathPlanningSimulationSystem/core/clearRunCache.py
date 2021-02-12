# -*- coding:utf-8 -*-

import os
import shutil


def clearRunCache(app_dir):
    for script_folder in os.listdir(app_dir):
        script_dir = os.path.join(app_dir, script_folder)
        if os.path.isdir(script_dir):
            for file in os.listdir(script_dir):
                if file == "__pycache__":
                    cache_dir = os.path.join(script_dir, file)       
                    shutil.rmtree(cache_dir)

def main():
    working_dir = os.path.join(os.getcwd(), "core")
    clearRunCache(working_dir)

if __name__ == "__main__":
    #
    main()
