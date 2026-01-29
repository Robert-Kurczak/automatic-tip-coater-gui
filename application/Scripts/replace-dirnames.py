#!/usr/bin/env python3

import fnmatch
import os
import argparse

def recursive_replace(path, matcher, old_substring, new_substring):
    for directory_paths, directory_names, _ in os.walk(path, topdown=False):
        for directory_name in directory_names:
            if fnmatch.fnmatch(directory_name, matcher):
                old_path = os.path.join(directory_paths, directory_name)
                new_path = old_path.replace(old_substring, new_substring)

                os.rename(old_path, new_path)

                print(f"{old_path} =>")
                print(f"{new_path}\n")

if __name__ == "__main__":
    parser = argparse.ArgumentParser()
    parser.add_argument("path", type=str)
    parser.add_argument("matcher", type=str)
    parser.add_argument("old_substring", type=str)
    parser.add_argument("new_substring", type=str)
    args = parser.parse_args()

    recursive_replace(
        args.path,
        args.matcher,
        args.old_substring,
        args.new_substring
    )
