import example
from pymongo import MongoClient

class SocketWrapper:
    def __init__ (self, sockinfo):
        self._sockinfo = sockinfo

    def send(self, buffer):
        print(f"writing {len(buffer)} bytes to stream")
        self._sockinfo.sock.sendall(buffer)

    def recv(self, to_recv):
        print(f"reading {to_recv} bytes from stream")
        response = self._sockinfo.sock.recv(to_recv)
        print(f"got back {response}")
        return response


client = MongoClient()
# IDK how _socket_for_writes works. This likely a bad idea.
# Maybe the safer thing is to just create a new socket to the primary for libmongocrypt.
with client._socket_for_writes () as sockinfo:
    stream = SocketWrapper(sockinfo)
    example.encrypt(stream)