class Smartphone:
    def __init__(self):
        self.os='Android'
        self.version='Marshmallow'
        self.model = 'Galaxy Note 7'

    def getOS(self):
         return self.os

    def getVersion(self):
        return self.version

    def getModel(self):
        return self.model


class iPhone(Smartphone)
    def __init__(self):
        self.os = 'iOS'
        self.version = 'iOS9'
        self.model = 'iPhone6(s)'

    def getOS(self):
        return "OS:" + self.os


phone = iPhone()

print(phone.getOS())

