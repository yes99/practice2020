# 20142812 Yang Jongman
import socket
import signal
import threading
import sys
import time

SERVER_IP_DEFAULT = "15.164.163.67"
#SERVER_IP_DEFAULT = "127.0.0.1"
SERVER_PORT_DEFAULT = 32812

CONNECTION_LIMIT_MSG = "C0"
CONNECTION_SUCCESS_MSG = "C1"

NICKNAME_INUSE = "N0"
NICKNAME_OK = "N1"

SOFTWARE_VERSION = 0.9

BANNED_FROM_SERVER = "Z4"

quit_Flag = False

command_dict = {
    "users": "A3",
    "wh": "J4",
    "exit": "C7",
    "version": "D5",
    "rename": "K9",
    "rtt": "Q4"
}

saved_time = time.time()

try:
    CURRENT_NICKNAME = sys.argv[1]
except IndexError:
    print("need nickname argument")
    sys.exit(1)


# users msg form = "[[command]. [nickname@ip1@ip2@ip3@ip4@port], [nickname2..."
def users(msg):
    msg = msg[1:]
    for m in msg:
        # m = nickname@ip1@ip2@ip3@ip4@port
        [nick, ip1, ip2, ip3, ip4, port] = m.split("@")
        print("nickname: {0}, IP: {1}:{2}:{3}:{4}, port: {5}".format(nick, ip1, ip2, ip3, ip4, port))


# whisper will work as plain text for client. so no need to implement
def whisper(msg):
    pass


def quit_client():
    msg = command_dict.get("exit") + "$"
    try:
        client_socket.send(msg.encode())
        client_socket.close()
    except Exception:
        pass
    global quit_Flag
    quit_Flag = True
    sys.exit(0)


def version(msg):
    print("client version: ", SOFTWARE_VERSION)
    print("server version: ", msg[1])


def rename(msg):
    global CURRENT_NICKNAME
    if msg[1] == NICKNAME_OK:
        CURRENT_NICKNAME = msg[2]
    else:
        print("nickname '{0}' is in use".format(msg[2]))
    print(msg)


def rtt(msg):
    print("rtt time:", round((time.time() - saved_time)*1000, 2), "ms")


reverse_command_dict = {
    "A3": users,
    "J4": whisper,
    "C7": quit_client,
    "D5": version,
    "K9": rename,
    "Q4": rtt
}

# --------------- SIGINT handler part
def quit_handler(signum, f):
    quit_client()
    print("bye bye~")
    sys.exit(0)


# set SIGINT handler
signal.signal(signal.SIGINT, quit_handler)


client_socket = socket.socket(family=socket.AF_INET, type=socket.SOCK_STREAM)


# --------------- receive part
def receive_from_server():
    while True:
        global quit_Flag
        msg = client_socket.recv(4096).decode()
        if len(msg) == 0:
            print("server seems like terminated")
            quit_Flag = True
            client_socket.close()
            sys.exit(0)

        if msg.split("$")[0] == BANNED_FROM_SERVER:
            print("you're banned from server")
            quit_Flag = True
            sys.exit(0)
        else:
            msg = msg.split("$")
            if len(msg)>=2:
                reverse_command_dict.get(msg[0])(msg)
            else:
                print(msg[0])


def connect_to_server(nickname, server_ip=SERVER_IP_DEFAULT, server_port=SERVER_PORT_DEFAULT):
    try:
        client_socket.connect((server_ip, server_port))
    except ConnectionRefusedError:
        print("Connection refused")
        sys.exit(0)
    except ConnectionError:
        print("Connection error occured")
        sys.exit(0)

    # get limit msg
    limit_msg = client_socket.recv(2048)

    #print(1)

    # if server limit reached, return
    if limit_msg.decode().split("$")[0] == CONNECTION_LIMIT_MSG:
        print("server connection limit reached")
        return False

    # send nickname
    client_socket.send(nickname.encode())
    nickname_msg = client_socket.recv(2048)

    #print(2)

    # if nickname is in use, return
    result = nickname_msg.decode().split("$")

    global CURRENT_NICKNAME
    if result[0] == NICKNAME_INUSE:
        print("can't use that nickname")
        return False
    # connect success
    else:
        # need to make welcome message
        [ip1, ip2, ip3, ip4, port] = result[1].split("@")
        print("welcome {0}. server ip={1}:{2}:{3}:{4}, port={5}".format(CURRENT_NICKNAME, ip1, ip2, ip3, ip4, port))
        #print(nickname_msg.decode())
        pass

    CURRENT_NICKNAME = nickname
    return True


if connect_to_server(CURRENT_NICKNAME):
    t = threading.Thread(target=receive_from_server, daemon=True)
    t.start()
else:
    sys.exit(0)

while not quit_Flag:
    try:
        line = input()
        if len(line) == 0:
            continue
        if line[0] == "\\":
            if command_dict.get(line.split(" ")[0][1:]) is not None:
                msg = command_dict.get(line.split(" ")[0][1:]) + "$" + line[len(line.split(" ")[0]) + 1:]
            else:
                print("It seems like your command input is wrong")
                continue
        else:
            msg = line
        # print(msg)
        if line == "\\rtt":
            saved_time = time.time()
        client_socket.send(msg.encode())
    except KeyboardInterrupt:
        quit_client()
    except OSError:
        print()






