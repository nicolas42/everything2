# http://www.libpng.org/pub/png/spec/1.2/PNG-Structure.html

import socket

hostname = "localhost"
port = 8080
content = bytes("GET / HTTP/1.1\nHost: www.example.com\n\n","utf8")

s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
s.connect((hostname, port))
s.sendall(content)
s.shutdown(socket.SHUT_WR)
d = s.recv(int(1e6))

start = d.find(b'\x89PNG')
end   = d.find(b'IEND')
f=open("f.png","wb")
f.write(d[start:end+4])
f.close()


def pwd(): 
    return os.getcwd()

def ls():
    return os.listdir()

def read(filename):
    f = open(filename, "rb")
    d=f.read()
    f.close()
    return d

def write(filename):
    f = open(filename, "wb")
    d=f.write()
    f.close()
    return d

# os.getenv("PATH")

def to_string(bytes_data):
    # works data which isn't properly encoded
    return ''.join(map(chr,bytes_data))





