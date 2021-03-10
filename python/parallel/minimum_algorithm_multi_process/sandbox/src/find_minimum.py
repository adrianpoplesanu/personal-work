import time
from multiprocessing import Process, Queue

def worker(q, items):
    time.sleep(5)
    min = items[0]
    for item in items:
        if min > item:
            min = item
    q.put(min)

if __name__ == '__main__':
    processes = []
    q = Queue()
    for i in range(5):
        p = Process(target=worker, args=(q, [4, 3, 1, 6, 3, -2, 9],))
        processes.append(p)
        p.start()

    for p in processes:
        p.join()

    while not q.empty():
        print q.get()
