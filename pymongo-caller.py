import pymongocrypt
from pymongo import MongoClient


class SocketWrapper:
    # Sockets are wrapped in this simplified class and passed down
    # to the pymongo <=> libmongocrypt integration layer.

    def __init__(self, sockinfo):
        self._sockinfo = sockinfo

    def send(self, buffer):
        self._sockinfo.sock.sendall(buffer)

    def recv(self, to_recv):
        response = self._sockinfo.sock.recv(to_recv)
        return response


client = MongoClient()
# IDK how _socket_for_writes works. This likely a bad idea.
# Maybe the safer thing is to just create a new socket to the primary for libmongocrypt.
with client._socket_for_writes() as sockinfo:
    stream = SocketWrapper(sockinfo)
    pymongocrypt.encrypt(stream)
