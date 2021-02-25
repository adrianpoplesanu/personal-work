import threading


screen_lock = threading.Semaphore(1)

class DataElement(object):
    numbers = []

class Task(threading.Thread):
    def __init__(self, id, data):
        threading.Thread.__init__(self)
        self.id = id
        self.data = data
        self._lock = threading.Lock()

    def process(self):
        with self._lock:
            for number in self.data.numbers:
                screen_lock.acquire()
                print str(self.id) + '-' + str(number)
                screen_lock.release()

    def run(self):
        self.process()


if __name__ == '__main__':
    print 'running...'
    num_threads = 6
    threads = []
    for i in range(num_threads):
        data_element = DataElement()
        data_element.numbers = [1, 2, 3, 4, 5, 6]
        threads.append(Task(i, data_element))
        threads[i].start()

    for i in range(num_threads):
        threads[i].join()
