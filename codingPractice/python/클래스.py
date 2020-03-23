class Smartphone
    def __init__(self)
        self.os='Android'
        self.version='Marshmallow'
        self.model = 'Galaxy Note 7'

    def getOS(self):
    return self.os

    def getVersion(self):
        return self.version

    def getModel(self):
        return self.model


phone = Smartphone()

print(phone.getOS())
print(phone.getVersion())
print(phone.getModel())