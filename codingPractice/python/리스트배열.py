gold = ["박인비", "오혜리", "김소희", "구본찬", "장혜진", "기보배", "진종오", "박상영", "최미선", "김우진", "이승윤"]
silver = ["김종현", "안바울", "정보경"]
iron = ["차동민", "이태훈", "정경은", "신승찬"]

print("금메달 리스트")
print(gold)
print("은메달 리스트")
print(silver)
print("동메달 리스트")
print(iron)

print(gold[0])
print(silver[1:2])
print(iron[:5])

gold[1] = "오혜리2"
print(gold)

medal = gold + silver + iron
print(medal)

medalcount = len(gold) + len(silver) + len(iron)
print(medalcount)