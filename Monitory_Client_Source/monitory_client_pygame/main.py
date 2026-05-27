import pygame
# import time

from src.draw_win import *
from src.tcp import *
from src.frame_dirty import *

FPS = 10

pygame.init()

white_color = (255,255,255)
black_color = (0, 0, 0)

# CREATING CANVAS
canvas = pygame.display.set_mode((1920, 1080), pygame.RESIZABLE)
def fullscreen():
    native_display_size = pygame.display.get_desktop_sizes()
    canvas = pygame.display.set_mode(native_display_size[0], pygame.RESIZABLE)
    pygame.display.toggle_fullscreen()
# Comment out for fullscreen
save_data = read_data()
if save_data["fullscreen"]:
    fullscreen()

# TITLE OF CANVAS
pygame.display.set_caption("Monitory Client")

# image = pygame.image.load("assets/Screenshot.png")
exit = False
frame_dirty = True

app_window = AppWindow()

tcp_thread = start_tcp_client("192.168.2.84")

# /home/asus-pc/Documents/bay/dev/sync/monitory_app_pygame/assets/ttf/FiraCode-Light.ttf

# font = pygame.font.Font('assets/ttf/FiraCode-Light.ttf', 32)
# text = font.render('GeeksForGeeks', True, green, blue)
# textRect = text.get_rect()
    

while not exit:
    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            exit = True

    if get_frame_dirty():
        set_frame_dirty(False)
        app_window.draw_window(canvas)
    
    pygame.display.update()
    
    # 1 / 10 FPS > 0.1 * 1000 > 100 ms
    ms = int(1.0 / float(FPS) * 1000.0)
    pygame.time.wait(ms)
    # time.sleep(0.2)

# At this point something crashed or we exit
# End networking thread
stop_tcp_client()
  
