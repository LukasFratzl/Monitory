import time
from src.io import read_data

class AppThemeSlice:
    def __init__(self):
        self.font_color = (0,0,0,0)
        self.font_bg_color = (0,0,0,0)
        self.graph_average_line_color = (0,0,0,0)
        self.graph_bottom_line_color = (0,0,0,0)
        self.graph_bg_color = (0,0,0,0)
        self.graph_line_color = (0,0,0,0)
        self.line_color_offset = 16

class AppTheme:
    def __init__(self):
        self.color_transparent = (0, 0, 0, 0)
        self.none = None
        

class DarkTheme(AppTheme):
    def __init__(self):
        super().__init__()
        self.screen_color = (0, 0, 0, 255)
        self.color_green = (0, 255, 0, 255)
        self.color_blue = (0, 0, 128, 255)
        self.color_blue_half = (0, 0, 128, 100)
        self.color_pink = (248, 12, 255, 255)
        self.color_purple_half = (182, 155, 255, 100)
        
        self.time_slice = AppThemeSlice()
        self.time_slice.font_color = self.color_green
        self.time_slice.font_bg_color = self.none
        # Thats the line between tima and date
        self.time_slice.graph_bottom_line_color = self.color_pink 
        
        self.date_slice = AppThemeSlice()
        self.date_slice.font_color = self.color_green
        self.date_slice.font_bg_color = self.none
        
        self.cpu_slice = AppThemeSlice()
        self.cpu_slice.font_color = self.color_green
        self.cpu_slice.font_bg_color = self.none
        self.cpu_slice.graph_average_line_color = self.color_pink
        self.cpu_slice.graph_bottom_line_color = self.color_transparent
        self.cpu_slice.graph_bg_color = self.color_blue_half
        self.cpu_slice.graph_line_color = self.color_transparent
    
        self.dram_slice = AppThemeSlice()
        self.dram_slice.font_color = self.color_green
        self.dram_slice.font_bg_color = self.none
        self.dram_slice.graph_average_line_color = self.color_transparent
        self.dram_slice.graph_bottom_line_color = self.color_transparent
        self.dram_slice.graph_bg_color = self.color_blue
        self.dram_slice.graph_line_color = self.color_green
        
        self.disk_slice = AppThemeSlice()
        self.disk_slice.font_color = self.color_green
        self.disk_slice.font_bg_color = self.none
        self.disk_slice.graph_average_line_color = self.color_transparent
        self.disk_slice.graph_bottom_line_color = self.color_transparent 
        self.disk_slice.graph_bg_color = self.color_blue
        self.disk_slice.graph_line_color = self.color_green
        
        self.gpu_slice = AppThemeSlice()
        self.gpu_slice.font_color = self.color_green
        self.gpu_slice.font_bg_color = self.none
        self.gpu_slice.graph_average_line_color = self.color_transparent
        self.gpu_slice.graph_bottom_line_color = self.color_transparent 
        self.gpu_slice.graph_bg_color = self.color_blue
        self.gpu_slice.graph_line_color = self.color_green
        
        self.vram_slice = AppThemeSlice()
        self.vram_slice.font_color = self.color_green
        self.vram_slice.font_bg_color = self.none
        self.vram_slice.graph_average_line_color = self.color_transparent
        self.vram_slice.graph_bottom_line_color = self.color_transparent 
        self.vram_slice.graph_bg_color = self.color_blue
        self.vram_slice.graph_line_color = self.color_green
        
        self.net_slice = AppThemeSlice()
        self.net_slice.font_color = self.color_green
        self.net_slice.font_bg_color = self.none
        self.net_slice.graph_average_line_color = self.color_transparent
        self.net_slice.graph_bottom_line_color = self.color_transparent 
        self.net_slice.graph_bg_color = self.color_transparent
        self.net_slice.graph_line_color = self.color_transparent
        self.net_slice.line_color_offset = 27
        
        self.watt_slice = AppThemeSlice()
        self.watt_slice.font_color = self.color_green
        self.watt_slice.font_bg_color = self.none
        self.watt_slice.graph_average_line_color = self.color_transparent
        self.watt_slice.graph_bottom_line_color = self.color_transparent 
        self.watt_slice.graph_bg_color = self.color_transparent
        self.watt_slice.graph_line_color = self.color_transparent
        
        self.temp_slice = AppThemeSlice()
        self.temp_slice.font_color = self.color_green
        self.temp_slice.font_bg_color = self.none
        self.temp_slice.graph_average_line_color = self.color_transparent
        self.temp_slice.graph_bottom_line_color = self.color_transparent 
        self.temp_slice.graph_bg_color = self.color_transparent
        self.temp_slice.graph_line_color = self.color_transparent
        
        
class LightTheme(DarkTheme):
    def __init__(self):
        super().__init__()
        self.screen_color = (234, 239, 245, 255)
        self.color_dark_gray = (40, 47, 51, 255)
        self.color_dark_gray_half = (40, 47, 51, 100)
        self.color_blue_gray = (185, 202, 221, 255)
        self.color_blue_gray_half = (185, 202, 221, 100)
        
        self.time_slice = AppThemeSlice()
        self.time_slice.font_color = self.color_dark_gray
        self.time_slice.font_bg_color = self.none
        # Thats the line between tima and date
        self.time_slice.graph_bottom_line_color = self.color_dark_gray
        
        self.date_slice = AppThemeSlice()
        self.date_slice.font_color = self.color_dark_gray
        self.date_slice.font_bg_color = self.none
        
        self.cpu_slice = AppThemeSlice()
        self.cpu_slice.font_color = self.color_dark_gray
        self.cpu_slice.font_bg_color = self.none
        self.cpu_slice.graph_average_line_color = self.color_pink
        self.cpu_slice.graph_bottom_line_color = self.color_transparent
        self.cpu_slice.graph_bg_color = self.color_purple_half
        self.cpu_slice.graph_line_color = self.color_transparent
    
        self.dram_slice = AppThemeSlice()
        self.dram_slice.font_color = self.color_dark_gray
        self.dram_slice.font_bg_color = self.none
        self.dram_slice.graph_average_line_color = self.color_transparent
        self.dram_slice.graph_bottom_line_color = self.color_transparent
        self.dram_slice.graph_bg_color = self.color_purple_half
        self.dram_slice.graph_line_color = self.color_green
        
        self.disk_slice = AppThemeSlice()
        self.disk_slice.font_color = self.color_dark_gray
        self.disk_slice.font_bg_color = self.none
        self.disk_slice.graph_average_line_color = self.color_transparent
        self.disk_slice.graph_bottom_line_color = self.color_transparent 
        self.disk_slice.graph_bg_color = self.color_purple_half
        self.disk_slice.graph_line_color = self.color_green
        
        self.gpu_slice = AppThemeSlice()
        self.gpu_slice.font_color = self.color_dark_gray
        self.gpu_slice.font_bg_color = self.none
        self.gpu_slice.graph_average_line_color = self.color_transparent
        self.gpu_slice.graph_bottom_line_color = self.color_transparent 
        self.gpu_slice.graph_bg_color = self.color_purple_half
        self.gpu_slice.graph_line_color = self.color_green
        
        self.vram_slice = AppThemeSlice()
        self.vram_slice.font_color = self.color_dark_gray
        self.vram_slice.font_bg_color = self.none
        self.vram_slice.graph_average_line_color = self.color_transparent
        self.vram_slice.graph_bottom_line_color = self.color_transparent 
        self.vram_slice.graph_bg_color = self.color_purple_half
        self.vram_slice.graph_line_color = self.color_green
        
        self.net_slice = AppThemeSlice()
        self.net_slice.font_color = self.color_dark_gray
        self.net_slice.font_bg_color = self.none
        self.net_slice.graph_average_line_color = self.color_transparent
        self.net_slice.graph_bottom_line_color = self.color_transparent 
        self.net_slice.graph_bg_color = self.color_transparent
        self.net_slice.graph_line_color = self.color_transparent
        self.net_slice.line_color_offset = 27
        
        self.watt_slice = AppThemeSlice()
        self.watt_slice.font_color = self.color_dark_gray
        self.watt_slice.font_bg_color = self.none
        self.watt_slice.graph_average_line_color = self.color_transparent
        self.watt_slice.graph_bottom_line_color = self.color_transparent 
        self.watt_slice.graph_bg_color = self.color_purple_half
        self.watt_slice.graph_line_color = self.color_green
        
        self.temp_slice = AppThemeSlice()
        self.temp_slice.font_color = self.color_dark_gray
        self.temp_slice.font_bg_color = self.none
        self.temp_slice.graph_average_line_color = self.color_transparent
        self.temp_slice.graph_bottom_line_color = self.color_transparent 
        self.temp_slice.graph_bg_color = self.color_purple_half
        self.temp_slice.graph_line_color = self.color_green
        
class Theme:
    def __init__(self):
        self.dark_theme = DarkTheme()
        self.light_theme = LightTheme()
        self.start_timer = time.time()
        self._is_dark_theme = True
        self._theme_init = False
    
    def is_dark_theme(self):
        end = time.time()
        length = end - self.start_timer
        if length > 15.0 or not self._theme_init:
            self._theme_init = True
            self.start_timer = time.time()
            data = read_data()
            self._is_dark_theme = data["dark_mode"]
        return self._is_dark_theme
    
    def get_screen_color(self):
        # Some theme logic
        if self.is_dark_theme():
            return self.dark_theme.screen_color
        else:
            return self.light_theme.screen_color
            
    def get_time_slice(self):
        # Some theme logic
        if self.is_dark_theme():
            return self.dark_theme.time_slice
        else:
            return self.light_theme.time_slice
            
    def get_date_slice(self):
        # Some theme logic
        if self.is_dark_theme():
            return self.dark_theme.date_slice
        else:
            return self.light_theme.date_slice
    
    def get_cpu_slice(self):
        # Some theme logic
        if self.is_dark_theme():
            return self.dark_theme.cpu_slice
        else:
            return self.light_theme.cpu_slice
            
    def get_dram_slice(self):
        # Some theme logic
        if self.is_dark_theme():
            return self.dark_theme.dram_slice
        else:
            return self.light_theme.dram_slice
            
    def get_disk_slice(self):
        # Some theme logic
        if self.is_dark_theme():
            return self.dark_theme.disk_slice
        else:
            return self.light_theme.disk_slice
    
    def get_gpu_slice(self):
        # Some theme logic
        if self.is_dark_theme():
            return self.dark_theme.gpu_slice
        else:
            return self.light_theme.gpu_slice
            
    def get_vram_slice(self):
        # Some theme logic
        if self.is_dark_theme():
            return self.dark_theme.vram_slice
        else:
            return self.light_theme.vram_slice
        
    def get_net_slice(self):
        # Some theme logic
        if self.is_dark_theme():
            return self.dark_theme.net_slice
        else:
            return self.light_theme.net_slice
            
    def get_watt_slice(self):
        # Some theme logic
        if self.is_dark_theme():
            return self.dark_theme.watt_slice
        else:
            return self.light_theme.watt_slice
            
    def get_temp_slice(self):
        # Some theme logic
        if self.is_dark_theme():
            return self.dark_theme.temp_slice
        else:
            return self.light_theme.temp_slice
