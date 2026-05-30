import pygame
# import time
import threading

from src.draw_win import *
from src.tcp import *
from src.frame_dirty import *

FPS = 10

pygame.init()

canvas = pygame.display.set_mode((2100, 1100), pygame.RESIZABLE)
def fullscreen():
    native_display_size = pygame.display.get_desktop_sizes()
    canvas = pygame.display.set_mode(native_display_size[0], pygame.RESIZABLE)
    pygame.display.toggle_fullscreen()
# Comment out for fullscreen
save_data = read_data()
if save_data["fullscreen"]:
    fullscreen()

pygame.display.set_caption("Monitory Client")
exit = False

app_window = AppWindow()
# Set counter to fake a timeout of the connection to show the main menu
set_frame_dirty_time(200.0)
app_window.draw_main_menu(canvas)

tcp_thread = threading.Thread(target=scan_ips, args=(), daemon=True)
tcp_thread.start()
    

while not exit:
    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            exit = True

    if get_frame_dirty():
        set_frame_dirty(False)
        app_window.draw_graph_window(canvas)
    else:
        previous = get_frame_dirty_time()
        end = time.time()
        length = end - previous
        # We ideling for seconds so we are for sure disconncted
        # lets draw the main menu
        if length > 15:
            app_window.draw_main_menu(canvas)
    
    pygame.display.update()
    
    # 1 / 10 FPS > 0.1 * 1000 > 100 ms
    ms = int(1.0 / float(FPS) * 1000.0)
    pygame.time.wait(ms)
    # time.sleep(0.2)

# At this point something crashed or we exit
# End networking thread
stop_tcp_clients()
tcp_thread.join()

pygame.quit()
  
