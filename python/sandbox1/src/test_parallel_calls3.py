import asyncio, requests, time

async def worker(n, delay):
    print ('starting ' + str(n))
    await asyncio.sleep(delay)
    response = requests.get("http://localhost:5003")
    print (response)
    print (response.text)
    print('ending ' + str(n))

async def main():

    task1 = asyncio.create_task(
        worker(1, 2))

    task2 = asyncio.create_task(
        worker(2, 2))

    print(f"started at {time.strftime('%X')}")

    # Wait until both tasks are completed (should take
    # around 2 seconds.)
    await task1
    await task2

    print(f"finished at {time.strftime('%X')}")


asyncio.run(main())
