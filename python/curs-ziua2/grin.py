import os
import argparse
import re


def highlight_pattern(line, pattern):
    return line.replace(pattern, '\033[96m' + pattern + '\033[0m')

def walk_files(source, pattern):
    paths = os.listdir(source)
    for path in paths:
        current_entry = source + '/' + path
        if os.path.isdir(current_entry):
            walk_files(current_entry, pattern)
        else:
            with open(current_entry, 'r') as file_desc:
                lines = file_desc.readlines()
                for index, line in enumerate(lines, start=1):
                    #if pattern in line:
                    if re.findall(pattern, line):
                        print '{0:35} {1:5}: {2}'.format(current_entry, index, highlight_pattern(line[:-1], pattern))

def get_arguments():
    parser = argparse.ArgumentParser()
    parser.add_argument('--pattern')
    parser.add_argument('--source')
    args = parser.parse_args()
    return args

def run():
    args = get_arguments()
    walk_files(args.source, args.pattern)

if __name__ == '__main__':
    """
    @param: pattern
    @parem: starting point(path de plecare)

    Usage: python grin.py --pattern Alice --source .
    """
    run()