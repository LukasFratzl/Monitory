import pygame
import pygame.freetype  # Import the freetype module.
import math
from src.distinct_colors import get_color_safe

class Graph:
    def __init__(self, screen_p_x, screen_p_y, size_p_x, size_p_y, grid_p):
        # Origin of the plot
        self.screen_p_x = screen_p_x
        self.screen_p_y = screen_p_y
        # Size of the plot
        self.size_p_x = size_p_x
        self.size_p_y = size_p_y
        
        # The percentage of the graph grid for xy
        self.grid_p = grid_p
        self.data_slice = [[]]
        self.data_slice_runtime = [[]]
        self.average_data_runtime = []
        
        if self.screen_p_x < self.size_p_x:
            print("Make sure screen_p_x is >= than size_p_x to fit it into the screen")
        if self.screen_p_y < self.size_p_y:
            print("Make sure screen_p_y is >= than size_p_y to fit it into the screen")
    
    
    def build(self, current_data, screen, app_theme_slice):
        # if len(self.data_slice) > 0 and len(current_data) != len(self.data_slice[-1]):
        #     print(f"current graph has different size ... " + \
        #             f"new: {len(current_data)}, current: {len(self.data_slice[-1])}")
        
        self.num_slices_x = int(math.floor(self.size_p_x / self.grid_p))
        if len(self.data_slice) != self.num_slices_x:
            print(f"init graph slices ... " + \
                    f"new: {self.num_slices_x}, current: {len(self.data_slice)}")
            self.data_slice = [ [ float for y in range( len(current_data) ) ] for x in range( self.num_slices_x ) ]
            
        if self.num_slices_x != len(self.average_data_runtime):
            self.average_data_runtime = [ float for y in range( self.num_slices_x ) ]
        
        # Make room for new data
        num_data = len(self.data_slice)
        self.data_slice_runtime = self.data_slice.copy()
        idx_y = 1
        for idx_x in range(num_data):
            if idx_y < num_data:
                self.data_slice[idx_y] = self.data_slice_runtime[idx_x]
            idx_y += 1
        
        # Add new data to the first element
        self.data_slice[0] = current_data
        
        # Starting from top left point of the screen
        w, h = pygame.display.get_surface().get_size()
        
        # Draw the plot
        idx_x = 0
        previous_best_val = 0.0
        for elem_x in self.data_slice:
            # Function is calling the previous point to draw a line, idx 0 has no prev.
            if idx_x == 0:
                idx_x += 1
                continue
            idx_y = 0
            best_value = 0.0
            filled_quad = False
            for elem_y in elem_x:
                try:
                    # When the array is fresh we don't need to draw zeros
                    x1 = float(elem_y)
                except:
                    continue
                if elem_y > best_value:
                    best_value = elem_y
            for elem_y in elem_x:
                try:
                    # When the array is fresh we don't need to draw zeros
                    x1 = float(elem_y)
                    x0 = float(self.data_slice[idx_x - 1][idx_y])
                except:
                    continue
                x = (w * self.screen_p_x) - (idx_x * (w * self.grid_p))
                y = (h * self.screen_p_y) - (elem_y * (h * self.size_p_y))
                
                pre_x = (w * self.screen_p_x) - ((idx_x - 1) * (w * self.grid_p))
                pre_y = (h * self.screen_p_y) - (self.data_slice[idx_x - 1][idx_y] * (h * self.size_p_y))
                
                # x is more to the right of screen x than pre_x
                # se we use pre_x with zero y to have the 1st point from the polygon
                if app_theme_slice.graph_bg_color[3] > 0 and not filled_quad:
                    filled_quad = True
                    y = (h * self.screen_p_y) - (best_value * (h * self.size_p_y))
                    pre_y = (h * self.screen_p_y) - (previous_best_val * (h * self.size_p_y))
                    poly_y = (h * self.screen_p_y)
                    
                    if app_theme_slice.graph_bg_color[3] != 100:
                        # But we have to fill the quad and not just the triangle
                        # _____
                        # \   |
                        #  \  |
                        polygon_list = [(x, y), (pre_x, poly_y), (pre_x, pre_y)]
                        pygame.draw.polygon(screen, app_theme_slice.graph_bg_color, polygon_list)
                        # |  \
                        # | __ \
                        polygon_list = [(x, y), (x, poly_y), (pre_x, poly_y)]
                        pygame.draw.polygon(screen, app_theme_slice.graph_bg_color, polygon_list)
                    else:
                        # It looks cool having stripes inside the graph sometimes
                        # pygame.draw.line(screen, app_theme_slice.graph_bg_color, (pre_x, pre_y), (pre_x, poly_y))
                        # |  \
                        # | __ \
                        polygon_list = [(x, y), (x, poly_y), (pre_x, poly_y)]
                        pygame.draw.polygon(screen, app_theme_slice.graph_bg_color, polygon_list)
                
                x = (w * self.screen_p_x) - (idx_x * (w * self.grid_p))
                y = (h * self.screen_p_y) - (elem_y * (h * self.size_p_y))
                
                pre_x = (w * self.screen_p_x) - ((idx_x - 1) * (w * self.grid_p))
                pre_y = (h * self.screen_p_y) - (self.data_slice[idx_x - 1][idx_y] * (h * self.size_p_y))
                
                if app_theme_slice.graph_line_color[3] < 255:
                    wanted_color = get_color_safe(idx_y, app_theme_slice.line_color_offset, 255)
                else:
                    wanted_color = app_theme_slice.graph_line_color
                
                pygame.draw.line(screen, wanted_color, (pre_x, pre_y), (x, y))
                
                
                idx_y += 1
            idx_x += 1
            previous_best_val = best_value
            # need_fill = False
        
        # Darw average line
        if app_theme_slice.graph_average_line_color[3] > 0: # If we have alpha
            average_value = -1.0
            for elem in current_data:
                if average_value < -0.5:
                    average_value = elem
                else:
                    try:
                        average_value += elem
                        average_value /= 2
                    except:
                        continue
            if average_value > 0:
                a_x = (w * self.screen_p_x) - ((self.num_slices_x + 2) * (w * self.grid_p))
                a_y = (h * self.screen_p_y) - (average_value * (h * self.size_p_y))
            
                a_pre_x = (w * self.screen_p_x) - ((-2) * (w * self.grid_p))
                # a_pre_y = (h * self.screen_p_y) - (self.data_slice[idx_x - 1][idx_y] * (h * self.size_p_y))
                pygame.draw.line(screen, app_theme_slice.graph_average_line_color, (a_pre_x, a_y), (a_x, a_y), 2)
        
        # Draw bottom line
        if app_theme_slice.graph_bottom_line_color[3] > 0: # If we have alpha
            a_x = (w * self.screen_p_x) - ((self.num_slices_x) * (w * self.grid_p))
            a_y = (h * self.screen_p_y)
            
            a_pre_x = (w * self.screen_p_x) - (w * self.grid_p)
            pygame.draw.line(screen, app_theme_slice.graph_bottom_line_color, (a_pre_x, a_y), (a_x, a_y))
            
class Plot:
    def __init__(self, screen_p_x, screen_p_y, size_p_x, size_p_y, hw_name, app_theme_slice, label_font, grid_p=0.005):
        self.screen_p_x = screen_p_x
        self.screen_p_y = screen_p_y
        self.size_p_x = size_p_x
        self.size_p_y = size_p_y
        self.grid_p = grid_p
        self.num_slices_x = int(math.floor(self.size_p_x / self.grid_p))
        self.percentage_value = -1.0
        self.graph_value = -1.0
        self.hw_name = hw_name
        self.label_font = label_font
        self.stats_name = ""
        
        self.main_graph = Graph(screen_p_x=screen_p_x, screen_p_y=screen_p_y, \
                                size_p_x=size_p_x, size_p_y=size_p_y, grid_p=self.grid_p)
        
        self.hw_label_text = label_font.render(hw_name, True, app_theme_slice.font_color, app_theme_slice.font_bg_color)
        self.hw_label_rect = self.hw_label_text.get_rect()
        
        self.stats_label_text = label_font.render(self.stats_name, True, app_theme_slice.font_color, app_theme_slice.font_bg_color)
        self.stats_label_rect = self.stats_label_text.get_rect()
        
    def update_val(self, perc_val, value, app_theme_slice, label_font):
        # just in case there its switching theme
        self.hw_label_text = self.label_font.render(self.hw_name, True, app_theme_slice.font_color, app_theme_slice.font_bg_color)
        
        self.percentage_value = perc_val
        self.graph_value = value
        
        # Assuming they are strings
        wanted_txt = self.stats_name + perc_val + value;
            
        self.stats_label_text = label_font.render(wanted_txt, True, app_theme_slice.font_color, app_theme_slice.font_bg_color)
        self.stats_label_rect = self.stats_label_text.get_rect()
        
                                
    def build(self, screen, graph_data, app_theme_slice):
        self.main_graph.build(graph_data, screen, app_theme_slice)
        
        self.move_text(screen)
        
    def move_text(self, screen):
        # Starting from top left point of the screen
        w, h = pygame.display.get_surface().get_size()
        
        hw_y = (h * self.screen_p_y) - (h * self.size_p_y)
        hw_x = (w * self.screen_p_x) - ((self.num_slices_x) * (w * self.grid_p))
        self.hw_label_rect.update((hw_x, hw_y), self.hw_label_rect.size)
        screen.blit(self.hw_label_text,  self.hw_label_rect)
        
        st_y = (h * self.screen_p_y) - (h * self.size_p_y)
        st_x = (w * self.screen_p_x)
        self.stats_label_rect = self.stats_label_text.get_rect(topright = (st_x + 1, st_y - 1))
        # self.stats_label_rect.update((st_x, st_y), self.stats_label_rect.size)
        screen.blit(self.stats_label_text,  self.stats_label_rect)
        
    
