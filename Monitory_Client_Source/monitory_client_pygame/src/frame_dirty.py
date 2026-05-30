import time

global frame_dirty
frame_dirty = False

global frame_dirty_time
frame_dirty_time = time.time()

def get_frame_dirty_time():
    global frame_dirty_time
    return frame_dirty_time

def set_frame_dirty_time(value):
    global frame_dirty_time
    frame_dirty_time = value
    
def get_frame_dirty():
    global frame_dirty
    return frame_dirty
    
def set_frame_dirty(value):
    global frame_dirty
    frame_dirty = value
    
    global frame_dirty_time
    frame_dirty_time = time.time()
