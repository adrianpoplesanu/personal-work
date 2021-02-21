import threading


class Task(threading.Thread):
    def __init__(self, id):
        threading.Thread.__init__(self)
        self.id = id

    def run(self):
        print 'starting ' + str(self.id)

def solve(a, num_threads):
    threads = []
    for i in range(num_threads):
        threads.append(Task(i))
        threads[i].start()

    for t in threads:
        t.join()
        print 'finished ' + str(t.id)

if __name__ == '__main__':
    a = [67, 45, 32, 87, 34, 12, 6, 3, -5, 67, 4, 78, 89, 2]
    solve(a, 2)
