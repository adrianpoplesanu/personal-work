import time
import sys
from multiprocessing import Process

def f(name):
    time.sleep(5)
    print('hello', name)

if __name__ == '__main__':
    p = Process(target=f, args=('adish',))
    p.start()
    p.join()
