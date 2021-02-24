import multiprocessing

def sum_up_to(number):
    return sum(range(1, number + 1))

multiprocess_pool = multiprocessing.Pool()

result = multiprocess_pool.map(sum_up_to, range(10))

print(result)
