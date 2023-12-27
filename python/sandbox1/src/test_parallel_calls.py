import requests

from multiprocessing import Process


def worker(n):
    print ('start worker' + str(n))
    response = requests.get("http://localhost:5003")
    print (response)
    print (response.text)
    print ('end worker' + str(n))

if __name__ == "__main__":
    p1 = Process(target=worker, args=(1,))
    p1.start()
    p2 = Process(target=worker, args=(2,))
    p2.start()
    p1.join()
    p2.join()


