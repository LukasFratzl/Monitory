import time
import pygame
from src.io import read_data

class AppThemeSlice:
    def __init__(self):
        self.font_color = (0,0,0,0)
        self.font_bg_color = (0,0,0,0)
        self.perc_font_color = (0,0,0,0)
        self.perc_font_bg_color = (0,0,0,0)
        self.stat_font_color = (0,0,0,0)
        self.stat_font_bg_color = (0,0,0,0)
        self.graph_average_line_color = (0,0,0,0)
        self.graph_bottom_line_color = (0,0,0,0)
        self.graph_bg_color = (0,0,0,0)
        self.graph_line_color = (0,0,0,0)
        self.line_color_offset = 16
        self.label_font = pygame.font.Font('assets/ttf/FiraCode-Light.ttf', 40)
        self.stats_0_font = pygame.font.Font('assets/ttf/FiraCode-Light.ttf', 40)
        self.stats_1_font = pygame.font.Font('assets/ttf/FiraCode-Light.ttf', 40)
        self.label_legent_items_font = pygame.font.Font('assets/ttf/FiraCode-Light.ttf', 40)

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
        self.color_light_grey = (155, 155, 157, 255)
        self.color_darkorchid = (153, 50, 204, 255), # darkorchid
        self.color_net_down = (255, 0, 0, 255), # red
        self.color_net_up = (255, 165, 0, 255), # orange
        
        saved_data = read_data()
        self.font_size = saved_data["font_size"]
        self.default_font = pygame.font.Font('assets/ttf/FiraCode-Light.ttf', self.font_size)
        self.default_font_stat_0 = pygame.font.Font('assets/ttf/FiraCode-Bold.ttf', self.font_size)
        self.default_font_stat_1 = pygame.font.Font('assets/ttf/FiraCode-Bold.ttf', self.font_size)
        self.default_label_legent_items_font = pygame.font.Font('assets/ttf/FiraCode-Light.ttf', int(self.font_size * 0.5))
        
        self.time_slice = AppThemeSlice()
        self.time_slice.font_color = self.color_green
        self.time_slice.font_bg_color = self.none
        # Thats the line between tima and date
        self.time_slice.graph_bottom_line_color = self.color_pink
        self.time_slice.label_font = pygame.font.Font('assets/ttf/FiraCode-Bold.ttf', int(self.font_size * 1.25))
        
        self.date_slice = AppThemeSlice()
        self.date_slice.font_color = self.color_green
        self.date_slice.font_bg_color = self.none
        self.date_slice.label_font = self.default_font
        
        self.cpu_slice = AppThemeSlice()
        self.cpu_slice.font_color = self.color_light_grey
        self.cpu_slice.font_bg_color = self.none
        self.cpu_slice.perc_font_color = self.color_green
        self.cpu_slice.perc_font_bg_color = self.none
        self.cpu_slice.stat_font_color = self.color_pink
        self.cpu_slice.stat_font_bg_color = self.none
        self.cpu_slice.graph_average_line_color = self.color_pink
        self.cpu_slice.graph_bottom_line_color = self.color_transparent
        self.cpu_slice.graph_bg_color = self.color_blue_half
        self.cpu_slice.graph_line_color = self.color_transparent
        self.cpu_slice.label_font = self.default_font
        self.cpu_slice.stats_0_font = self.default_font_stat_0
        self.cpu_slice.stats_1_font = self.default_font_stat_1
    
        self.dram_slice = AppThemeSlice()
        self.dram_slice.font_color = self.color_light_grey
        self.dram_slice.font_bg_color = self.none
        self.dram_slice.perc_font_color = self.color_green
        self.dram_slice.perc_font_bg_color = self.none
        self.dram_slice.stat_font_color = self.color_pink
        self.dram_slice.stat_font_bg_color = self.none
        self.dram_slice.graph_average_line_color = self.color_transparent
        self.dram_slice.graph_bottom_line_color = self.color_transparent
        self.dram_slice.graph_bg_color = self.color_blue
        self.dram_slice.graph_line_color = self.color_green
        self.dram_slice.label_font = self.default_font
        self.dram_slice.stats_0_font = self.default_font_stat_0
        self.dram_slice.stats_1_font = self.default_font_stat_1
        
        self.disk_slice = AppThemeSlice()
        self.disk_slice.font_color = self.color_light_grey
        self.disk_slice.font_bg_color = self.none
        self.disk_slice.perc_font_color = self.color_green
        self.disk_slice.perc_font_bg_color = self.none
        self.disk_slice.stat_font_color = self.color_pink
        self.disk_slice.stat_font_bg_color = self.none
        self.disk_slice.graph_average_line_color = self.color_transparent
        self.disk_slice.graph_bottom_line_color = self.color_transparent 
        self.disk_slice.graph_bg_color = self.color_blue
        self.disk_slice.graph_line_color = self.color_transparent
        self.disk_slice.label_font = self.default_font
        self.disk_slice.stats_0_font = self.default_font_stat_0
        self.disk_slice.stats_1_font = self.default_font_stat_1
        
        self.gpu_slice = AppThemeSlice()
        self.gpu_slice.font_color = self.color_light_grey
        self.gpu_slice.font_bg_color = self.none
        self.gpu_slice.perc_font_color = self.color_green
        self.gpu_slice.perc_font_bg_color = self.none
        self.gpu_slice.stat_font_color = self.color_pink
        self.gpu_slice.stat_font_bg_color = self.none
        self.gpu_slice.graph_average_line_color = self.color_transparent
        self.gpu_slice.graph_bottom_line_color = self.color_transparent 
        self.gpu_slice.graph_bg_color = self.color_blue
        self.gpu_slice.graph_line_color = self.color_green
        self.gpu_slice.label_font = self.default_font
        self.gpu_slice.stats_0_font = self.default_font_stat_0
        self.gpu_slice.stats_1_font = self.default_font_stat_1
        
        self.vram_slice = AppThemeSlice()
        self.vram_slice.font_color = self.color_light_grey
        self.vram_slice.font_bg_color = self.none
        self.vram_slice.perc_font_color = self.color_green
        self.vram_slice.perc_font_bg_color = self.none
        self.vram_slice.stat_font_color = self.color_pink
        self.vram_slice.stat_font_bg_color = self.none
        self.vram_slice.graph_average_line_color = self.color_transparent
        self.vram_slice.graph_bottom_line_color = self.color_transparent 
        self.vram_slice.graph_bg_color = self.color_blue
        self.vram_slice.graph_line_color = self.color_green
        self.vram_slice.label_font = self.default_font
        self.vram_slice.stats_0_font = self.default_font_stat_0
        self.vram_slice.stats_1_font = self.default_font_stat_1
        
        self.net_slice = AppThemeSlice()
        self.net_slice.font_color = self.color_light_grey
        self.net_slice.font_bg_color = self.none
        self.net_slice.perc_font_color = self.color_net_down
        self.net_slice.perc_font_bg_color = self.none
        self.net_slice.stat_font_color = self.color_net_up
        self.net_slice.stat_font_bg_color = self.none
        self.net_slice.graph_average_line_color = self.color_transparent
        self.net_slice.graph_bottom_line_color = self.color_transparent 
        self.net_slice.graph_bg_color = self.color_transparent
        self.net_slice.graph_line_color = self.color_transparent
        self.net_slice.label_font = self.default_font
        self.net_slice.stats_0_font = self.default_font_stat_0
        self.net_slice.stats_1_font = self.default_font_stat_1
        self.net_slice.line_color_offset = 27
        
        self.watt_slice = AppThemeSlice()
        self.watt_slice.font_color = self.color_light_grey
        self.watt_slice.font_bg_color = self.none
        self.watt_slice.perc_font_color = self.color_green
        self.watt_slice.perc_font_bg_color = self.none
        self.watt_slice.stat_font_color = self.color_pink
        self.watt_slice.stat_font_bg_color = self.none
        self.watt_slice.graph_average_line_color = self.color_transparent
        self.watt_slice.graph_bottom_line_color = self.color_transparent 
        self.watt_slice.graph_bg_color = self.color_transparent
        self.watt_slice.graph_line_color = self.color_transparent
        self.watt_slice.label_font = self.default_font
        self.watt_slice.stats_0_font = self.default_font_stat_0
        self.watt_slice.stats_1_font = self.default_font_stat_1
        self.watt_slice.label_legent_items_font = self.default_label_legent_items_font
        
        self.temp_slice = AppThemeSlice()
        self.temp_slice.font_color = self.color_light_grey
        self.temp_slice.font_bg_color = self.none
        self.temp_slice.perc_font_color = self.color_green
        self.temp_slice.perc_font_bg_color = self.none
        self.temp_slice.stat_font_color = self.color_pink
        self.temp_slice.stat_font_bg_color = self.none
        self.temp_slice.graph_average_line_color = self.color_transparent
        self.temp_slice.graph_bottom_line_color = self.color_transparent 
        self.temp_slice.graph_bg_color = self.color_transparent
        self.temp_slice.graph_line_color = self.color_transparent
        self.temp_slice.label_font = self.default_font
        self.temp_slice.stats_0_font = self.default_font_stat_0
        self.temp_slice.stats_1_font = self.default_font_stat_1
        self.temp_slice.label_legent_items_font = self.default_label_legent_items_font
        
        
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
        self.time_slice.label_font = pygame.font.Font('assets/ttf/FiraCode-Bold.ttf', int(self.font_size * 1.25))
        
        self.date_slice = AppThemeSlice()
        self.date_slice.font_color = self.color_dark_gray
        self.date_slice.font_bg_color = self.none
        self.date_slice.label_font = self.default_font
        
        self.cpu_slice = AppThemeSlice()
        self.cpu_slice.font_color = self.color_dark_gray
        self.cpu_slice.font_bg_color = self.none
        self.cpu_slice.perc_font_color = self.color_dark_gray
        self.cpu_slice.perc_font_bg_color = self.none
        self.cpu_slice.stat_font_color = self.color_dark_gray
        self.cpu_slice.stat_font_bg_color = self.none
        self.cpu_slice.graph_average_line_color = self.color_pink
        self.cpu_slice.graph_bottom_line_color = self.color_transparent
        self.cpu_slice.graph_bg_color = self.color_blue_gray_half
        self.cpu_slice.graph_line_color = self.color_transparent
        self.cpu_slice.label_font = self.default_font
        self.cpu_slice.stats_0_font = self.default_font_stat_0
        self.cpu_slice.stats_1_font = self.default_font_stat_1
    
        self.dram_slice = AppThemeSlice()
        self.dram_slice.font_color = self.color_dark_gray
        self.dram_slice.font_bg_color = self.none
        self.dram_slice.perc_font_color = self.color_dark_gray
        self.dram_slice.perc_font_bg_color = self.none
        self.dram_slice.stat_font_color = self.color_dark_gray
        self.dram_slice.stat_font_bg_color = self.none
        self.dram_slice.graph_average_line_color = self.color_transparent
        self.dram_slice.graph_bottom_line_color = self.color_transparent
        self.dram_slice.graph_bg_color = self.color_blue_gray_half
        self.dram_slice.graph_line_color = self.color_green
        self.dram_slice.label_font = self.default_font
        self.dram_slice.stats_0_font = self.default_font_stat_0
        self.dram_slice.stats_1_font = self.default_font_stat_1
        
        self.disk_slice = AppThemeSlice()
        self.disk_slice.font_color = self.color_dark_gray
        self.disk_slice.font_bg_color = self.none
        self.disk_slice.perc_font_color = self.color_dark_gray
        self.disk_slice.perc_font_bg_color = self.none
        self.disk_slice.stat_font_color = self.color_dark_gray
        self.disk_slice.stat_font_bg_color = self.none
        self.disk_slice.graph_average_line_color = self.color_transparent
        self.disk_slice.graph_bottom_line_color = self.color_transparent 
        self.disk_slice.graph_bg_color = self.color_blue_gray_half
        self.disk_slice.graph_line_color = self.color_transparent
        self.disk_slice.label_font = self.default_font
        self.disk_slice.stats_0_font = self.default_font_stat_0
        self.disk_slice.stats_1_font = self.default_font_stat_1
        
        self.gpu_slice = AppThemeSlice()
        self.gpu_slice.font_color = self.color_dark_gray
        self.gpu_slice.font_bg_color = self.none
        self.gpu_slice.perc_font_color = self.color_dark_gray
        self.gpu_slice.perc_font_bg_color = self.none
        self.gpu_slice.stat_font_color = self.color_dark_gray
        self.gpu_slice.stat_font_bg_color = self.none
        self.gpu_slice.graph_average_line_color = self.color_transparent
        self.gpu_slice.graph_bottom_line_color = self.color_transparent 
        self.gpu_slice.graph_bg_color = self.color_blue_gray_half
        self.gpu_slice.graph_line_color = self.color_green
        self.gpu_slice.label_font = self.default_font
        self.gpu_slice.stats_0_font = self.default_font_stat_0
        self.gpu_slice.stats_1_font = self.default_font_stat_1
        
        self.vram_slice = AppThemeSlice()
        self.vram_slice.font_color = self.color_dark_gray
        self.vram_slice.font_bg_color = self.none
        self.vram_slice.perc_font_color = self.color_dark_gray
        self.vram_slice.perc_font_bg_color = self.none
        self.vram_slice.stat_font_color = self.color_dark_gray
        self.vram_slice.stat_font_bg_color = self.none
        self.vram_slice.graph_average_line_color = self.color_transparent
        self.vram_slice.graph_bottom_line_color = self.color_transparent 
        self.vram_slice.graph_bg_color = self.color_blue_gray_half
        self.vram_slice.graph_line_color = self.color_green
        self.vram_slice.label_font = self.default_font
        self.vram_slice.stats_0_font = self.default_font_stat_0
        self.vram_slice.stats_1_font = self.default_font_stat_1
        
        self.net_slice = AppThemeSlice()
        self.net_slice.font_color = self.color_dark_gray
        self.net_slice.font_bg_color = self.none
        self.net_slice.perc_font_color = self.color_net_down
        self.net_slice.perc_font_bg_color = self.none
        self.net_slice.stat_font_color = self.color_net_up
        self.net_slice.stat_font_bg_color = self.none
        self.net_slice.graph_average_line_color = self.color_transparent
        self.net_slice.graph_bottom_line_color = self.color_transparent 
        self.net_slice.graph_bg_color = self.color_transparent
        self.net_slice.graph_line_color = self.color_transparent
        self.net_slice.label_font = self.default_font
        self.net_slice.stats_0_font = self.default_font_stat_0
        self.net_slice.stats_1_font = self.default_font_stat_1
        self.net_slice.line_color_offset = 27
        
        self.watt_slice = AppThemeSlice()
        self.watt_slice.font_color = self.color_dark_gray
        self.watt_slice.font_bg_color = self.none
        self.watt_slice.perc_font_color = self.color_dark_gray
        self.watt_slice.perc_font_bg_color = self.none
        self.watt_slice.stat_font_color = self.color_dark_gray
        self.watt_slice.stat_font_bg_color = self.none
        self.watt_slice.graph_average_line_color = self.color_transparent
        self.watt_slice.graph_bottom_line_color = self.color_transparent 
        self.watt_slice.graph_bg_color = self.color_transparent
        self.watt_slice.graph_line_color = self.color_transparent
        self.watt_slice.label_font = self.default_font
        self.watt_slice.stats_0_font = self.default_font_stat_0
        self.watt_slice.stats_1_font = self.default_font_stat_1
        self.watt_slice.label_legent_items_font = self.default_label_legent_items_font
        
        self.temp_slice = AppThemeSlice()
        self.temp_slice.font_color = self.color_dark_gray
        self.temp_slice.font_bg_color = self.none
        self.temp_slice.perc_font_color = self.color_dark_gray
        self.temp_slice.perc_font_bg_color = self.none
        self.temp_slice.stat_font_color = self.color_dark_gray
        self.temp_slice.stat_font_bg_color = self.none
        self.temp_slice.graph_average_line_color = self.color_transparent
        self.temp_slice.graph_bottom_line_color = self.color_transparent 
        self.temp_slice.graph_bg_color = self.color_transparent
        self.temp_slice.graph_line_color = self.color_transparent
        self.temp_slice.label_font = self.default_font
        self.temp_slice.stats_0_font = self.default_font_stat_0
        self.temp_slice.stats_1_font = self.default_font_stat_1
        self.temp_slice.label_legent_items_font = self.default_label_legent_items_font
        
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
