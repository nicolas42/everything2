from sockets_lib import *

# run_echo_server('', 8888)
# # listen to all ip addresses on port 8888
# send_message('127.0.0.1', 8888, "Hello World!")


from threading import Thread
from time import sleep


def run_echo_server(HOST, PORT):
    # e.g. run_echo_server('127.0.0.1', 50007) 
    s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    s.bind((HOST, PORT))
    s.listen(1)
    while True:
        conn, addr = s.accept()
        # with conn:
        print('Connected by', addr)
        while True:
            data = conn.recv(1024)
            if not data: break
            conn.sendall(data)
            print("sent", data)  
    
    s.close()





def threaded_function(args):
    run_echo_server('127.0.0.1', 50007) 




thread = Thread(target = threaded_function, args = (10, ))
thread.start()

print("hello")

thread.join()



