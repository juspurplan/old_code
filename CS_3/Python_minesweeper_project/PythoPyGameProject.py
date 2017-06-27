import pygame
import sys
import random
from pygame.event import *
from pygame.locals import *
from pygame.key import *
import math

class Grid:
    line_size=0
    grid_dim = (0,0)#num_x_tiles by num_y_tiles
    tile_dim = (0,0)#for each tile: num_x_pixels by num_y_pixels
    grid_pos = (0,0)#(x,y) coordinate position
        #top left corner, includes padding
    line_color=(0,0,0) #grid line color

    def __init__(self, (gridx,gridy), (tilex,tiley), (x,y), width , (r,g,b) ):
        self.grid_dim = (gridx,gridy)
        self.tile_dim = (tilex,tiley)
        self.grid_pos = (x,y)
        self.line_size = width
        self.color = (0,0,0,255)
    def get_tile_pos(self, (x,y) ):
        #returns the top left position of the specified tile (zero-indexed)
        a, b = self.tile_dim
        c,d = self.grid_pos
        return ( c+(a*x)+(self.line_size*x)+1 , d+(b*y)+(self.line_size*y)+1 )
    def draw_grid(self, surface):
        #draws to the given surface param
        xgrid, ygrid = self.grid_dim
        xtile, ytile = self.tile_dim
        xpos,ypos = self.grid_pos
        xend = xpos + (xgrid*xtile) + (self.line_size*(xgrid))
        yend = ypos + (ygrid*ytile) + (self.line_size*(ygrid))

        x=xpos
        y=ypos
        while (x <= xend):
            pygame.draw.line( surface, self.line_color, (x,y), (x,yend), self.line_size )
            x = x+xtile +1
        x=xpos
        y=ypos    
        while (y <= yend):
            pygame.draw.line( surface, self.line_color, (x,y), (xend,y), self.line_size )
            y = y+ytile +1
    def get_size(self):
        #returns grid size in pixels (includes grid lines)
        xgrid, ygrid = self.grid_dim
        xtile, ytile = self.tile_dim
        xpos,ypos = self.grid_pos
        xend = xpos + (xgrid*xtile) + (self.line_size*(xgrid))
        yend = ypos + (ygrid*ytile) + (self.line_size*(ygrid))
        
        result =(math.fabs(math.fabs(xend)-math.fabs(xpos))+1 , math.fabs(math.fabs(yend)-math.fabs(ypos))+1)
        return result
    def get_tile_size(self):
        #returns grid size in tiles (x_tiles by y_tiles)
        return self.grid_dim
    def get_grid_pos(self):
        #return grid position (top left corner)
        return self.grid_pos
    def set_line_color(self, (r,g,b) ):
        self.line_color=(r,g,b)
    def set_line_size(width):
        self.line_size = width
    def get_tile_bounds(self, (x,y) ):
        #returns top left and bottom right pos of the indicated tile
        topleft = self.get_tile_pos( (x,y) )
        a,b = topleft
        c,d = self.tile_dim
        bottomright = (a+c-1, b+d-1)
        return ( topleft,bottomright )

class Mine:
    pos = (0,0)
    hidden = True
    image_id = 0
    def __init__(self, (x,y), image_id ):
        self.pos = (x,y)
        self.image_id = image_id
        self.hidden=True
    def unhide(self):
        self.hidden = False
    def hide(self):
        self.hidden = True


###states
INIT = 0
RUNNING = 1
GAMEOVER = 2
EXIT = 3
###Actions
NONE = 0
DIG = 1
FLAG = 2
UNFLAG = 3
NEWGAME = 4
EXITGAME = 5

###########
###Game
pygame.init()
pygame.display.set_caption("PythoPyGameProject")

fps = pygame.time.Clock()
surface = pygame.display.set_mode( (960,596) )
grid = Grid( (24,21) ,(25,25) ,(25,25) , 1, (0,0,0) )

grid_x_tiles, grid_y_tiles = grid.get_tile_size()
grid_xpos, grid_ypos = grid.get_grid_pos()

state = 0
action = 0

fill_color = (200,200,200)
font_size = 30
text_buffer = []
text_color = (255,255,255)

kirby_r = pygame.image.load("kirby_sprite_r.png")
kirby_l = pygame.image.load("kirby_sprite_l.png")
facing_right = True
xpos = 0
ypos = 0
mousepos = (0,0)

mines = []

while (state != EXIT):
    surface.fill( fill_color )

    #draw grid
    grid.draw_grid(surface)

    #moving/drawing kirby
    if(xpos <0):
        xpos = 0
    if(xpos >= grid_x_tiles):
        xpos = grid_x_tiles-1
    if(ypos <0):
        ypos = 0
    if(ypos >= grid_y_tiles):
        ypos = grid_y_tiles-1
    a,b = grid.get_tile_pos( (xpos,ypos) )
    if(facing_right):
        surface.blit(kirby_r, (a,b) )
    else:
        surface.blit(kirby_l, (a,b) )
    del a,b

    #add to text buffer
    a,b = mousepos
    text_buffer.append("MousePos: ( "+str(a)+" , "+str(b)+" )")
    del a,b
    text_buffer.append("KirbyPos: ( "+str(xpos)+" , "+str(ypos)+" )")

    #blitting text starting at pos (675,26) adding 30 to the y coord each iteration
    font = pygame.font.Font(None, font_size)
    a,b = grid.get_size()
    line_pos = 26
    for line in text_buffer:
        text = font.render(line, 0, text_color)
        surface.blit(text, (675,line_pos) )
        line_pos = line_pos + 30
    del a,b
    text_buffer=[]
    

    #events
    for event in pygame.event.get():
        if(event.type == QUIT):
            pygame.quit()
            sys.exit()
        if(event.type == KEYDOWN):
            if(event.key == K_ESCAPE):
                pygame.quit()
                sys.exit()
            if(event.key == K_LEFT):
                xpos = xpos-1
                facing_right = False
            if(event.key == K_RIGHT):
                xpos = xpos+1
                facing_right = True
            if(event.key==K_UP):
                ypos = ypos-1
            if(event.key==K_DOWN):
                ypos=ypos+1
            if(event.key==K_SPACE):
                color = (random.randint(0,255), random.randint(0,255), random.randint(0,255),)
                grid.set_line_color(color)
                fill_color = (random.randint(0,255), random.randint(0,255), random.randint(0,255))
        if(event.type == MOUSEMOTION):
            mousepos = event.pos
                
    #repaint
    pygame.display.update()
    fps.tick(60)
