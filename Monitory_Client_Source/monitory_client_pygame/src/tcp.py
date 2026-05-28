import socket
import threading
import time
from src.data_extract import translate_data


def tcp_client(server, port):
    while not TCP_EXIT:  # Keep trying to connect/remain connected
        try:
            time.sleep(3)  # Wait a bit before trying to reconnect
            sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
            print(f"Attempting to connect to {server}:{port}")
            sock.connect((server, port))
            print("Connected to server")
            sock.settimeout(5)
            
            # Maintain connection and handle incoming data
            while not TCP_EXIT:  # Keep the connection alive if possible
                try:
                    data = sock.recv(4096)
                    if not data:
                        print("Server disconnected")
                        break
                    else:
                        try:
                            translate_data(data.decode())
                            # print(export_stats_json["Cpu_Utility_Total"])
                            # print(f"Received: {data.decode().split('!')[0]}")
                        except:
                            continue
                except (ConnectionResetError, BrokenPipeError):
                    print("Connection lost, attempting to reconnect...")
                    time.sleep(3)  # Wait a bit before trying to reconnect
                    break
            
            sock.shutdown(socket.SHUT_RDWR)
            sock.close()
        except (socket.error, ConnectionRefusedError) as e:
            print(f"Connection failed: {e}. Retrying in 3 seconds...")
            time.sleep(3)

def start_tcp_client(server, port=54000):
    global TCP_EXIT
    TCP_EXIT = False;

    global client_thread
    client_thread = threading.Thread(target=tcp_client, args=(server, port), daemon=True)
    client_thread.start()
    
    return client_thread

def stop_tcp_client():
    global TCP_EXIT
    TCP_EXIT = True;
    
    print("Attempting to shutdown TCP client.")
    
    client_thread.join()
    
    
