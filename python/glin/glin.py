import argparse
import sys
import os
import re


all_files = []
searched_text = ''

def get_version():
    return sys.version_info[0]

def get_all_files():
    global all_files
    all_files = walk_files(".")
    #print all_files
    grep_all_files()

def print_with_colors(entries):
    global searched_text
    if get_version() == 2:
        for filename, occurances in entries.iteritems():
            #sys.stdout.write('\x1b[32m{0}\x1b[0m\n{1}: {2}\n'.format(entry[0], entry[1], entry[2].replace(searched_text, "\x1b[31m" + searched_text + "\x1b[0m")))
            info = ''
            for o in occurances:
                info += '{0:5} : {1}\n'.format(o[0], o[1].replace(searched_text, "\x1b[30m\x1b[43m" + searched_text + "\x1b[0m"))
            sys.stdout.write('\x1b[32m{0}\x1b[0m\n{1}'.format(filename, info))
    else:
        for filename, occurances in entries.items():
            #sys.stdout.write('\x1b[32m{0}\x1b[0m\n{1}: {2}\n'.format(entry[0], entry[1], entry[2].replace(searched_text, "\x1b[31m" + searched_text + "\x1b[0m")))
            info = ''
            for o in occurances:
                info += '{0:5} : {1}\n'.format(o[0], o[1].replace(searched_text, "\x1b[30m\x1b[43m" + searched_text + "\x1b[0m"))
            sys.stdout.write('\x1b[32m{0}\x1b[0m\n{1}'.format(filename, info))

def grep_all_files():
    global all_files
    global searched_text
    results = {}
    for filename in all_files:
        with open(filename, 'r') as fd:
            for line_num, line in enumerate(fd.readlines(), start=1):
                #do the maths
                #if it matches then print file, linenum and the actual line
                found = re.search(searched_text, line)
                if found:
                    #results.append((filename, line_num, line.strip()))
                    try:
                        results[filename].append((line_num, line.rstrip()))
                    except:
                        results[filename] = [(line_num, line.rstrip())]
    print_with_colors(results)
    #print results


def walk_files(base):
    filenames = []
    entries = os.listdir(base)
    for entry in entries:
        #print base + "/" + entry
        if os.path.isdir(base + "/" + entry):
            subdir_entries = walk_files(base + "/" + entry)
            for e in subdir_entries:
                #filenames.append(entry + "/" + e)
                filenames.append(e)
        else:
            #filenames.append(entry)
            filenames.append(base + "/" + entry)
    return filenames

def main2():
    global searched_text
    searched_text = sys.argv[1]
    #sys.stdout.write('running on python 2.x\n')
    get_all_files()

def main3():
    global searched_text
    searched_text = sys.argv[1]
    sys.stdout.write('running on python 3\n')
    get_all_files()

if __name__ == '__main__':
    version = get_version()
    if version == 2:
        main2()
    else:
        main3()
