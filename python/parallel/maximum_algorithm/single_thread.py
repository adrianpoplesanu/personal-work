import threading

def thread_function(id):
    print 'aaa'

if __name__ == '__main__':
    thread = threading.Thread(target=thread_function, args=(1,))
    thread.start()
    
