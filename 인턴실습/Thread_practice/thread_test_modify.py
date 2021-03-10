import time
import threading

def long_task():
    for i in range(5):
        time.sleep(1)
        print("working: %s \n" %i)

print("Start")

threads = []
for i in range(5):
    t = threading.Thread(target=long_task) #스레드 생성했죠
    threads.append(t)

for t in threads:
    t.start()  #스레드를 시작한다.

print("END")