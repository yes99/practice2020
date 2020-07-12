import time
print("10 second")
input(" push enter start")
stime = time.time()
input(" puh enter start")
etime = time.time()
time = etime - stime
print("%.3f second take" %time , end="" )
if time<10:
    print("%.3f fast" %(10-time))
if time>10:
     print("%.3f slow" %(time-10))
if time == 10:
    print("such a miracle")