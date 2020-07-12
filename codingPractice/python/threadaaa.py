import threading
import time

start_time = time.time()
def test():
    while True:
        time.sleep(1)
        print(time.time() - start_time)


def test2():
    while True:
        time.sleep(1)
        print("abc")

t = threading.Thread(target=test,daemon=True)
t.start()
t2 = threading.Thread(target=test2,daemon=True)
t2.start()



while True:
    line = input()
    print(line)
