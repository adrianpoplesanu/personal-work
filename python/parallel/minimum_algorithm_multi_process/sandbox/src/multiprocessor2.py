import time
import sys
from multiprocessing import Process

def f(id, name):
    time.sleep(5)
    print('hello', id, name)

if __name__ == '__main__':
    processes = []
    for i in range(5):
        p = Process(target=f, args=(i, 'aditz',))
        processes.append(p)
        p.start()

    for i in range(5):
        processes[i].join()
