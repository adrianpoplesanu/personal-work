import threading


class Task(threading.Thread):
    def __init__(self, id, numbers):
        threading.Thread.__init__(self)
        self.id = id
        self.numbers = numbers
        self.result = None

    def run(self):
        min = numbers[0]
        for number in self.numbers:
            if min > number:
                min = number
        self.result = min

def solve(numbers, num_threads):
    threads = []
    rang = [(0, 7), (7, 14)]
    for i in range(num_threads):
        threads.append(Task(i, numbers[rang[i][0]:rang[i][1]]))
        threads[i].start()

    for t in threads:
        t.join()
        print 'finished ' + str(t.id)
        print t.result

if __name__ == '__main__':
    numbers = [67, 45, 32, 87, 34, 12, 6, 3, -5, 67, 4, 78, 89, 2]
    solve(numbers, 2)
