import socket
import threading


class Client:
    """A classs to send command to the server."""

    def __init__(self, ip, port):
        "Create a socket with server ip and serv port."
        self.ip = ip
        self.port = port
        self.sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)

    def cmdReset(self):
        "Send reset command to the server."
        self.sock.sendto("exe:reset 0 0".encode(), (self.ip, self.port))

    def cmdStop(self):
        "Send stop command to the server."
        self.sock.sendto("exe:stop 0 0".encode(), (self.ip, self.port))

    def cmdMove(self, x, y):
        "Send move with two number command to the server."
        self.sock.sendto(f"exe:move {x} {y}".encode(), (self.ip, self.port))

    def cmdAxe(self, x, y):
        "Send axe with two number command to the server."
        self.sock.sendto(f"exe:axe {x} {y}".encode(), (self.ip, self.port))

    def loop(self):
        "Event loop to print the acknowledgment from server."
        while True:
            data, addr = self.sock.recvfrom(1024)
            print(f"{addr} say {data}")


# Example of usage
if __name__ == "__main__":
    c = Client("127.0.0.1", 5000)

    # To output acknowledgment
    threading.Thread(target=c.loop).start()

    c.cmdAxe(42, 56)
    c.cmdMove(42, 56)
    c.cmdStop()
    c.cmdReset()
