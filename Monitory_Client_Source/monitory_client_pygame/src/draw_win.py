import pygame
import math
import random

from src.draw_plot import Plot
from src.data_extract import export_stats_json
from src.theme import *
from src.io import read_data

class AppWindow:
    def __init__(self):
    
        
        # self.color_transparent = (0, 0, 0, 0)
        # self.color_light_gray = (198, 198, 198, 255)
        # self.color_dark_gray = (167, 167, 167, 255)
        # self.color_light_gray_half = (198, 198, 198, 100)
        # self.color_pink = (248, 12, 255, 255)
        # self.color_white = (255, 255, 255)
        # self.color_green = (0, 255, 0, 255)
        # self.color_blue = (0, 0, 128, 255)
        # self.color_blue_half = (0, 0, 128, 100)
        saved_data = read_data()
        self.font_size = saved_data["font_size"]
        self.default_font = pygame.font.Font('assets/ttf/FiraCode-Light.ttf', self.font_size)
        
        self.grid_p = 0.005
        
        self.theme = Theme()
        self.time_slice = self.theme.get_time_slice()
        self.date_slice = self.theme.get_date_slice()
        self.cpu_slice = self.theme.get_cpu_slice()
        self.vram_slice = self.theme.get_vram_slice()
        self.disk_slice = self.theme.get_disk_slice()
        self.gpu_slice = self.theme.get_gpu_slice()
        self.vram_slice = self.theme.get_vram_slice()
        self.net_slice = self.theme.get_net_slice()
        self.watt_slice = self.theme.get_watt_slice()
        self.temp_slice = self.theme.get_temp_slice()
        
        # 1st ROW
        self.cpu_plot = Plot(screen_p_x=0.32, screen_p_y=0.45, \
                                size_p_x=0.30, size_p_y=0.2, hw_name='CPU', \
                                app_theme_slice=self.cpu_slice, \
                                label_font=self.default_font, grid_p=self.grid_p)
                                
        self.cpu_ram_plot = Plot(screen_p_x=0.65, screen_p_y=0.45, \
                                size_p_x=0.30, size_p_y=0.2, hw_name='DRAM', \
                                app_theme_slice=self.vram_slice, \
                                label_font=self.default_font, grid_p=self.grid_p)
                                
        self.drives_plot = Plot(screen_p_x=0.98, screen_p_y=0.45, \
                                size_p_x=0.30, size_p_y=0.2, hw_name='DISK', \
                                app_theme_slice=self.disk_slice, \
                                label_font=self.default_font, grid_p=self.grid_p)
        
        # 2nd ROW
        self.gpu_util_plot = Plot(screen_p_x=0.32, screen_p_y=0.7, \
                                size_p_x=0.30, size_p_y=0.2, hw_name='GPU', \
                                app_theme_slice=self.gpu_slice, \
                                label_font=self.default_font, grid_p=self.grid_p)
        
        self.gpu_ram_plot = Plot(screen_p_x=0.65, screen_p_y=0.7, \
                                size_p_x=0.30, size_p_y=0.2, hw_name='VRAM', \
                                app_theme_slice=self.vram_slice, \
                                label_font=self.default_font, grid_p=self.grid_p)
                                
        self.net_plot = Plot(screen_p_x=0.98, screen_p_y=0.7, \
                                size_p_x=0.30, size_p_y=0.2, hw_name='NET', \
                                app_theme_slice=self.net_slice, \
                                label_font=self.default_font, grid_p=self.grid_p)
                                
        # 3rd ROW
        self.wattage_plot = Plot(screen_p_x=0.27, screen_p_y=0.95, \
                                size_p_x=0.25, size_p_y=0.2, hw_name='WATT', \
                                app_theme_slice=self.gpu_slice, \
                                label_font=self.default_font, grid_p=self.grid_p)
                                
        self.temp_plot = Plot(screen_p_x=0.79, screen_p_y=0.95, \
                                size_p_x=0.25, size_p_y=0.2, hw_name='TEMP', \
                                app_theme_slice=self.gpu_slice, \
                                label_font=self.default_font, grid_p=self.grid_p)

    def draw_window(self, screen):
        # Lets get the latest theme data in case of an theme switch
        self.time_slice = self.theme.get_time_slice()
        self.date_slice = self.theme.get_date_slice()
        self.cpu_slice = self.theme.get_cpu_slice()
        self.vram_slice = self.theme.get_vram_slice()
        self.disk_slice = self.theme.get_disk_slice()
        self.gpu_slice = self.theme.get_gpu_slice()
        self.vram_slice = self.theme.get_vram_slice()
        self.net_slice = self.theme.get_net_slice()
        self.watt_slice = self.theme.get_watt_slice()
        self.temp_slice = self.theme.get_temp_slice()
        
        self.legent_label_font = pygame.font.Font('assets/ttf/FiraCode-Light.ttf', int(self.font_size * 0.5))
    
        # background
        screen.fill(self.theme.get_screen_color())
        
        # Time, Date
        self.draw_time(screen, self.time_slice, self.date_slice)
        
        # COU Util
        cpu_util = export_stats_json["Cpu_Utility_Thread"]
                        
        self.cpu_plot.build(screen, cpu_util, app_theme_slice=self.cpu_slice, has_relative_data=False)
        
        cpu_perc = export_stats_json["Cpu_Utility_Total"] * 100.0
        cpu_ghz = export_stats_json["Cpu_Clock_Average"] / 1024
        self.cpu_plot.update_val(" {:.1f}%".format(cpu_perc), " {:.2f}GHz".format(cpu_ghz), \
                                app_theme_slice=self.cpu_slice, \
                                label_font=self.default_font)
        
        # Cpu dram
        cpu_dram_available = export_stats_json["Cpu_Memory_Available"]
        cpu_dram_used = export_stats_json["Cpu_Memory_Used"]
        if cpu_dram_available == 0 or cpu_dram_used == 0:
            cpu_dram_per = []
            cpu_dram_per.append(0)
        else:
            cpu_dram_per = []
            cpu_dram_per.append(float(cpu_dram_used) / float(cpu_dram_available))
            
        
        self.cpu_ram_plot.build(screen, cpu_dram_per, app_theme_slice=self.vram_slice, has_relative_data=False)
        
        self.cpu_ram_plot.update_val(" {:.1f}%".format(cpu_dram_per[0] * 100), " {:.1f}GB".format(cpu_dram_used), \
                                app_theme_slice=self.vram_slice, \
                                label_font=self.default_font)
        
        # Storage Load
        storage = []
        max_load = 0
        for x in export_stats_json["Storage_Load"].values():
            x_01 = x * 0.01
            storage.append(x_01)
            if x_01 > max_load:
                max_load = x_01
        
        self.drives_plot.build(screen, storage, app_theme_slice=self.disk_slice, has_relative_data=False)
        
        self.drives_plot.update_val(" {:.1f}%".format(max_load * 100), "", \
                                app_theme_slice=self.disk_slice, \
                                label_font=self.default_font)
                                
        # GPU Util
        gpu_util = [export_stats_json["Gpu_Utility"]]
        gpu_ghz = export_stats_json["Gpu_Clock"]
        self.gpu_util_plot.build(screen, gpu_util, app_theme_slice=self.gpu_slice, has_relative_data=False)
        
        self.gpu_util_plot.update_val(" {:.1f}%".format(gpu_util[0] * 100), " {:.2f}GHz".format(gpu_ghz / 1024), \
                                app_theme_slice=self.gpu_slice, \
                                label_font=self.default_font)
                                
        # GPU RAM
        gpu_mem_available = export_stats_json["Gpu_Memory_Available"]
        gpu_mem_used = export_stats_json["Gpu_Memory_Used"]
        if gpu_mem_available == 0 or gpu_mem_used == 0:
            gpu_vram_per = []
            gpu_vram_per.append(0)
        else:
            gpu_vram_per = []
            gpu_vram_per.append(float(gpu_mem_used) / float(gpu_mem_available + gpu_mem_used))
            
        self.gpu_ram_plot.build(screen, gpu_vram_per, app_theme_slice=self.vram_slice, has_relative_data=False)
        
        self.gpu_ram_plot.update_val(" {:.1f}%".format(gpu_vram_per[0] * 100), " {:.1f}GB".format(gpu_mem_used), \
                                app_theme_slice=self.vram_slice, \
                                label_font=self.default_font)
        
        # Net
        net_up = export_stats_json["Net_Upload_Speed"]
        net_down = export_stats_json["Net_Download_Speed"]
        
        net_traffic = [net_down, net_up]
        
        self.net_plot.build(screen, net_traffic, app_theme_slice=self.net_slice, has_relative_data=True)
        self.net_plot.update_val("↑ {:.1f}Mbps  ".format(net_up / 100000), "↓ {:.1f}Mbps".format(net_down / 100000), \
                                app_theme_slice=self.net_slice, \
                                label_font=self.default_font)
        
        # WATT
        max_w = 0
        watt_values = []
        for w in export_stats_json["Wattage"].values():
            watt_values.append(w)
            max_w += w
        
        (max_value, max_val_combined) = self.wattage_plot.build(screen, watt_values, app_theme_slice=self.watt_slice,\
                                                                has_relative_data=True)
        if max_value > 0.0:
            self.wattage_plot.update_val("{:.0f}  W".format(max_w), "   ", \
                                    app_theme_slice=self.watt_slice, \
                                    label_font=self.default_font)
                                    
            self.wattage_plot.update_max_val(screen, app_theme_slice=self.watt_slice,\
                                            screen_p_x=0.32, screen_p_y=0.75, \
                                            max_value_str="{:.0f}  MAX".format(max_val_combined))
            self.wattage_plot.draw_legend_items(screen, self.legent_label_font, app_theme_slice=self.watt_slice,\
                                                screen_p_x=0.32, screen_p_y=0.85,\
                                                items=export_stats_json["Wattage"], value_format="{:.0f}")
                                
        # TEMP                
        max_t = 0
        temp_values = []
        for t in export_stats_json["Temperature"].values():
            temp_values.append(t)
            if t > max_t:
                max_t = t
        
        (max_value, max_val_combined) = self.temp_plot.build(screen, temp_values, app_theme_slice=self.temp_slice,\
                                                            has_relative_data=True)
        if max_value > 0.0:
            self.temp_plot.update_val("{:.1f}  C".format(max_t), "   ", \
                                    app_theme_slice=self.temp_slice, \
                                    label_font=self.default_font)
                                    
            self.temp_plot.update_max_val(screen, app_theme_slice=self.temp_slice,\
                                            screen_p_x=0.82, screen_p_y=0.75, \
                                            max_value_str="{:.1f}  MAX".format(max_value))
                                        
            self.temp_plot.draw_legend_items(screen, self.legent_label_font, app_theme_slice=self.temp_slice,\
                                                screen_p_x=0.82, screen_p_y=0.85,\
                                                items=export_stats_json["Temperature"], value_format="{:.0f}")
                                
    
    def draw_time(self, screen, time_slice, date_slice):
        time = export_stats_json["Time_Now"]
        date = export_stats_json["Date_Now"]
        
        w, h = pygame.display.get_surface().get_size()
        
        time_label = self.default_font.render(time, True, time_slice.font_color, time_slice.font_bg_color)
        time_label_rect = time_label.get_rect()
        origin_x = w * 0.15
        t_y = h * 0.091
        # time_label_rect.update((t_x, t_y), time_label_rect.size)
        time_label_rect = time_label.get_rect(bottomleft = (origin_x, t_y - 1))
        screen.blit(time_label,  time_label_rect)
        
        l_y = h * 0.0925
        l_x = w * 0.135
        le_x = origin_x + 300
        pygame.draw.line(screen, time_slice.graph_bottom_line_color, (l_x, l_y), (le_x, l_y), 1)
        
        date_label = self.default_font.render(date, True, date_slice.font_color, date_slice.font_bg_color)
        date_label_rect = date_label.get_rect()
        d_y = h * 0.10
        # date_label_rect.update((d_x, d_y), date_label_rect.size)
        date_label_rect = date_label.get_rect(topleft = (origin_x, d_y - 1))
        screen.blit(date_label,  date_label_rect)
