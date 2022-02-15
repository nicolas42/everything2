import socket

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




def send_message(HOST, PORT, message):
    # e.g. send_message('127.0.0.1', 50007, "Hello World!")
    s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    s.connect((HOST, PORT))
    s.sendall(bytes(message, "utf8"))
    data = s.recv(1024)
    print('Received', repr(data))
    s.close()



from threading import Thread
from time import sleep

def threaded_function(conn):
    while True:
        data = conn.recv(1024)
        if not data: break
        # conn.sendall(data)
        print("sent", data)  


def threaded_server():
    HOST = ''                 # Symbolic name meaning all available interfaces
    PORT = 50000              # Arbitrary non-privileged port
    s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    s.bind((HOST, PORT))
    s.listen(1)
    while True:
        conn, addr = s.accept()
        # with conn:
        print('Connected by', addr)
        thread = Thread(target = threaded_function, args = (conn, ))
        thread.start()
        thread.join()
        # print("thread finished...exiting")
    
    s.close()



