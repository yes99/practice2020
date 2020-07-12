def solution(num):
    t = 1
    cnt = 0
    while(True):
        if num / t < 10:
            print(cnt)
            break
        else:
            t *= 10
            cnt = cnt +1

print(solution(156))
print(solution(18961))