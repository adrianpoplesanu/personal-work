#import sys
import argparse

if __name__ == '__main__':
    #args = sys.argv[1:]
    #print args
    parser = argparse.ArgumentParser()
    parser.add_argument('--sum')
    args = parser.parse_args()
    print args
