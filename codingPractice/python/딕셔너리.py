sports = {}
sports  ['양궁'] = '한국종합우승'
sports  ['펜싱'] = '한국 기력 상승'
sports  ['축구'] = '아쉽지만...'
sports  ['유도'] = '그래도 잘했음'
sports  ['사격'] = '세계적인 기록 달성'
sports  ['골프'] = '116년만의 금메달'

print(sports)
print(sports['골프'])
print(sports.keys())
print(sports.values())

if '양궁' in sports:
    print(sports['양궁'])

sports.pop("양궁")
print(sports)

