import threading

screen_lock = threading.Semaphore(value=1)

def thread_function(id):
    for i in range(100):
        screen_lock.acquire()
        print str(id) + '-' + str(i)
        screen_lock.release()

if __name__ == '__main__':
    threads = []
    for i in range(3):
        thread = threading.Thread(target=thread_function, args=(i,))
        threads.append(thread)
        thread.start()
    for i in range(3):
        thread.join()
    
