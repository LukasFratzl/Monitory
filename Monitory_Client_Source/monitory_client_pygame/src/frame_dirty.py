global frame_dirty
frame_dirty = True


def get_frame_dirty():
    global frame_dirty
    return frame_dirty
    
def set_frame_dirty(value):
    global frame_dirty
    frame_dirty = value
