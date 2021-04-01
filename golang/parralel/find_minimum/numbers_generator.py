#!/usr/bin/python
import argparse
import random

if __name__ == '__main__':
    parser = argparse.ArgumentParser()
    parser.add_argument("-o", "--output", help="output file with random numbers", required=True)
    parser.add_argument("-s", "--size", help="number of random entries in the file", required=True)
    args = parser.parse_args()

    filename = args.output
    size = args.size

    with open(filename, 'w') as f:
        for i in range(int(size)):
            f.write(str(random.randint(0, 9)) + ' ')
