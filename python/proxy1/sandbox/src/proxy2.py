import argparse
import socket
import sys
from _thread import *

listening_port = 1111

parser = argparse.ArgumentParser()

parser.add_argument('--max_conn', help="Maximum allowed connections", default=5, type=int)
parser.add_argument('--buffer_size', help="Number of samples to be used", default=8192, type=int)

args = parser.parse_args()
max_connection = args.max_conn
buffer_size = args.buffer_size

def start():
    try:
        sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        sock.bind(('', listening_port))
        sock.listen(max_connection)
        print("[*] Server started successfully [ %d ]" %(listening_port))
    except Exception as ex:
        print("[*] Unable to Initialize Socket")
        print(ex)
        sys.exit(2)

    while True:
        try:
            conn, addr = sock.accept() #Accept connection from client browser
            data = conn.recv(buffer_size) #Recieve client data
            start_new_thread(conn_string, (conn, data, addr)) #Starting a thread
        except KeyboardInterrupt:
            sock.close()
            print("\n[*] Graceful Shutdown")
            sys.exit(1)

def conn_string(conn, data, addr):
    print ('conn_string')
    try:
        first_line = data.split(b'\n')[0]

        print (str(first_line))

        if b'/dex' in first_line:
            print ('mapping /dex to port 8080')
            webserver = "localhost"
            port = 8080
        else:
            # some default here
            print ('[*] no mapping found for: ' + str(first_line))
            raise Exception
        proxy_server(webserver, port, conn, addr, data)
    except Exception as ex:
        print (ex)
        print ('closing connection')
        conn.close()

def proxy_server(webserver, port, conn, addr, data):
    print ('proxy_server()')
    try:
        sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        sock.connect((webserver, port))
        sock.send(data)

        while 1:
            reply = sock.recv(buffer_size)
            if(len(reply)>0):
                conn.send(reply)
                
                dar = float(len(reply))
                dar = float(dar/1024)
                dar = "%.3s" % (str(dar))
                dar = "%s KB" % (dar)
                print("[*] Request Done: %s => %s <=" % (str(addr[0]), str(dar)))

                if len(reply) < 8192:
                    break

            else:
                break

        sock.close()
        print ('closing connection')
        conn.close()
    except socket.error:
        sock.close()
        conn.close()
        print(sock.error)
        sys.exit(1)



if __name__== "__main__":
    start()
