str1="Hello World!"
str2="  Hello  "
print(str1) #Hello World!
print(len(str1)) #12
print(str1.count("o")) #2
print("[",str2.lstrip(),"]") #[ Hello   ]
print("[",str2.rstrip(),"]") #[   Hello ]
print("[",str2.strip(),"]")  #[ Hello ]
print(str1.upper())  # HELLO WORLD!
print(str1.lower())  # hello world!
print(str1.find("o")) # 4
print(str1.index("o")) # 4
print(str1.replace("World","!")) #Hello !!
print(str1.split('e')) # ['H', 'llo World!']

str3="I am a good programmer"
print(str3.split()) # ['I', 'am', 'a', 'good', 'programmer']
print("*".join(str1)) # H*e*l*l*o* *W*o*r*l*d*!
str4="Time is 5pm"
print(str4[0].isalpha()) #True
print(str4[8].isdigit()) #True
c=str4[4]
print(c.isspace()) #True
