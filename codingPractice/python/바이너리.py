import struct
try:
    file = open("x.bin", "wb")

    bin_value = struct.pack('i', 2020)
    file.write(bin_value)
    bin_value = struct.pack('f', 3.14)
    file.write(bin_value)

    bin_value = struct.pack('5s', 'Korea'.enconde())
    file.write(bin_value)

    bin_value = struct.pack('3s', 'KOR'.encode(encoding='utf-8'))
    file.write(bin_value)

    file.close()
except:
    print("파일을 열 수 없습니다")