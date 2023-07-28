import threading

def runner(n):
    print ("starting thread")
    for i in range(n):
        print (i)
    print ("finish thread")

t1 = threading.Thread(target=runner, args=(100,))
t2 = threading.Thread(target=runner, args=(100,))
t3 = threading.Thread(target=runner, args=(100,))

t1.start()
t2.start()
t3.start()
