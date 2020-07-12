heroes  = [ "스파이더맨", "슈퍼맨", "헐크", "아이언맨", "배트맨" ]
if "배트맨" in heroes :
	print("배트맨은 영웅입니다. ")

index = heroes.index("슈퍼맨")	# index는 1이 된다. 
print(index)

heroes.pop(1)
print(heroes)
heroes.remove("스파이더맨")
print(heroes)


a = [3,2,1,5,4]
a.sort()
print(a)

b= sorted(a)
print(b)