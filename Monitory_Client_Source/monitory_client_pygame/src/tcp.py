import socket
import threading
import time
from src.data_extract import translate_data
from src.io import read_data


def tcp_client(server, port):
    try:
        time.sleep(3)  # Wait a bit before trying to reconnect
        sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        print(f"Attempting to connect to {server}:{port}")
        sock.settimeout(5)
        sock.connect((server, port))
        print(f"Connected to server {server}")
                
        # Maintain connection and handle incoming data
        while not TCP_EXIT:  # Keep the connection alive if possible
            try:
                data = sock.recv(TCP_BUFFER_SIZE)
                if not data:
                    print(f"Server disconnected {server}")
                    break
                else:
                    try:
                        translate_data(data.decode())
                        global is_tcp_connected
                        is_tcp_connected = True
                    except:
                        continue
            except (ConnectionResetError, BrokenPipeError):
                print(f"Connection lost to {server}, attempting to reconnect...")
                time.sleep(3)  # Wait a bit before trying to reconnect
                break
                
        sock.shutdown(socket.SHUT_RDWR)
        sock.close()
    except (socket.error, ConnectionRefusedError) as e:
        print(f"Connection {server} failed: {e}")
        time.sleep(3)


def start_tcp_client(server, port=54000):
    save_data = read_data()
    global TCP_BUFFER_SIZE
    TCP_BUFFER_SIZE = save_data["buffer_size"]

    client_thread = threading.Thread(target=tcp_client, args=(server, port), daemon=True)
    client_thread.start()
    
    return client_thread

    
def scan_ips():
    save_data = read_data()
    
    global TCP_EXIT
    TCP_EXIT = False;
    
    global running_tcp_clients
    running_tcp_clients = []
    
    global is_tcp_connected
    is_tcp_connected = False
    
    while not TCP_EXIT:
        try:
            for ip in save_data["IPs"]:
                running_tcp_clients.append(start_tcp_client(ip))
            
            for client in running_tcp_clients:
                client.join()
        except:
            continue
        if len(save_data["IPs"]) > 0:
            print("IP scan iteration done ...")
        time.sleep(3)
    
    stop_tcp_clients()

def stop_tcp_clients():
    global TCP_EXIT
    TCP_EXIT = True;
    
    print("Attempting to shutdown TCP clients.")
    
    for client in running_tcp_clients:
        client.join()
        
    
    
    
