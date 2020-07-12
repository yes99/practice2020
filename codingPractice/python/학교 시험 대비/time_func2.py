import time

t=time.localtime()
print("%4d/%02d/%02d"%(t.tm_year, t.tm_mon, t.t_mday))
print("%02d:%02d:%02d"%(t.tm_hour, t.tm_min, t.tm_sec))
print("%d %03d"%(t.tm_wday, t.tm_yday))
xxxx