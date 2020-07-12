import time
import datetime
t=time.time()
print(t)
print(time.ctime(t))
d=datetime.datetime.now()
print("%4d/%02d/%02d"%(d.year, d.month, d.day))
print("%02d:%02d:%02d"%(d.hour, d.minute, d.second))
