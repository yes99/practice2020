class Smartphone:
    def __init__(self, number):
        self.os='Android'
        self.version='Marshmallow'
        self.model = 'Galaxy Note 7'
        number2 = number + 30
        self.number = number2

    def getOS(self):
         return self.os

    def getVersion(self):
        return self.version

    def getModel(self):
        return self.model

    def printInfo(self):
        print(self.os)
        print(self.version)
        print(self.model)
        print(self.number)


phone1 = Smartphone(12345)
phone2 = Smartphone(34567)

phones = [phone1, phone2]

for phone in phones:
    print(phone.getOS())
    print(phone.getModel())
    print(phone.getVersion())


def sum(phone1, phone2):
    phone1.number += phone2.number

sum(phone1, phone2)

print(phone1.number)