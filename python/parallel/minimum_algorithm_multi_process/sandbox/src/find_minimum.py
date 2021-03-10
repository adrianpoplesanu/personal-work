from multiprocessing import Process, Queue

def worker(q, items):
    min = items[0]
    for item in items:
        if min > item:
            min = item
    q.put(min)

if __name__ == '__main__':
    q = Queue()
    for i in range(5):
        p = Process(target=worker, args=(q, [4, 3, 1, 6, 3, -2, 9],))
        p.start()
        p.join()
    while not q.empty():
        print q.get()
