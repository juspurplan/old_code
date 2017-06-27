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
    def get_tile_index(self, (x,y)):
        #returns indices of tiles given a set of mouse coords, on a grid line or out-of-bounds returns None
        gridx,gridy = self.grid_dim
        gridxpos,gridypos = self.grid_pos
        tilex,tiley = self.tile_dim
        a = 0
        b =0
        while (a<gridx):
            b =0
            while(b<gridy):
                xleft = gridxpos+(tilex*a)+(self.line_size*a)+1
                xright = xleft+tilex-1
                ytop = gridypos+(tiley*b)+(self.line_size*b)+1
                ybot = ytop+tiley-1
                if( x >=xleft and x <= xright and y >= ytop and y<=ybot):
                    return (a,b)
                b= b+1
            a= a+1
        return(-1,-1)

class Tile:
    pos = (0,0)
    mine = False
    digged = False
    flagged = False
    image_id = 0
    mine_id = 0
    def __init__(self, (x,y), image_id , mine_id ):
        self.pos = (x,y)
        self.image_id = image_id
        self.mine_id = mine_id
        self.digged = False
        self.flagged = False
        self.mine = False
    def dig(self):
        self.digged = True
    def is_mine(self):
        return self.mine
    def is_flagged(self):
        return self.flagged
    def flag (self):
        self.flagged = True
    def unflag(self):
        self.flagged = False
    def get_pos(self):
        return self.pos
    def set_mine(self, a):
        self.mine = a
    def is_digged(self):
        return self.digged
    def get_image_id(self):
        return self.image_id
    def get_mine_id(self):
        return self.mine_id

#Functions
def search_tile((x,y), tiles ):
    for tile in tiles:
        a,b = tile.get_pos()
        if(a==x and b == y):
            return tile
        


###states
INIT = 0
RUN = 1
LOSE = 2
WIN = 3
EXIT = 4
###Actions
NONE = 0
DIG = 1
FLAG = 2
NEWGAME = 3
EXITGAME = 4

###########
###Game
pygame.init()
pygame.display.set_caption("PythoPyGameProject")

fps = pygame.time.Clock()
surface = pygame.display.set_mode( (960,596) )
grid = Grid( (24,21) ,(25,25) ,(25,25) , 1, (0,0,0) )

grid_x_tiles, grid_y_tiles = grid.get_tile_size()
num_tiles = grid_x_tiles * grid_y_tiles
grid_xpos, grid_ypos = grid.get_grid_pos()

state = INIT
action = NONE

fill_color = (200,200,200)
font_size = 30
text_buffer = []
text_color = (255,255,255)

kirby_1 = pygame.image.load("kirby_1_r.png")
tile_1 = pygame.image.load("tile_1.png")
tile_2 = pygame.image.load("tile_2.png")
tile_3 = pygame.image.load("tile_3.png")
tile_4 = pygame.image.load("tile_4.png")
tile_5 = pygame.image.load("tile_5.png")
dirt_pic = pygame.image.load("dirt.png")
flag_pic = pygame.image.load("flag.png")
zero= pygame.image.load("0.png")
one = pygame.image.load("1.png")
two = pygame.image.load("2.png")
three = pygame.image.load("3.png")
four = pygame.image.load("4.png")
five = pygame.image.load("5.png")
six = pygame.image.load("6.png")
seven = pygame.image.load("7.png")
eight = pygame.image.load("8.png")
cross = pygame.image.load("x.png")
circle = pygame.image.load("or.png")

mousepos = (0,0)
lastclick = (0,0)

tiles = []
num_mines = 10
num_flags = 10
max_flags = 10
num_flagged_mines=0


while (state != EXIT):

    #process game
    if(state == INIT):
        print "INITIALIZING"
        grid = Grid( (24,21) ,(25,25) ,(25,25) , 1, (0,0,0) )
        fill_color = (200,200,200)
        font_size = 30
        text_buffer = []
        text_color = (255,255,255)
        tiles = []
        num_mines = 60
        num_flags = 60
        max_flags = 60
        num_flagged_mines=0
        action = NONE
        surface.fill(fill_color)
        print "\tcreating tiles"
        a =0
        b =0
        while(a<grid_x_tiles):
            b = 0
            while(b<grid_y_tiles):
                t_id = random.randint(0,4)
                m_id = 0
                tiles.append( Tile( (a,b), t_id, m_id ) )
                print "\ttile( "+str(a)+" , "+str(b)+" )"
                b= b+1
            a=a+1
        print"\tcreating mines"
        temp = 0
        while(temp < num_mines):
            index = random.randint(0,len(tiles)-1)
            if(not(tiles[index].is_mine())):
                a,b = tiles[index].get_pos()
                print "\tmine"+str(temp)+" ( "+str(a)+" , "+str(b)+" )"
                tiles[index].set_mine(True)
                temp = temp+1
        del a,b,temp,index,t_id,m_id
        state = RUN
    elif (state == LOSE):
        print "GAME LOST"
        if(action == NEWGAME):
            state =INIT
        if(action == EXITGAME):
            state = EXIT
    elif (state == WIN):
        print "GAME WON"
        if(action == NEWGAME):
            state =INIT
        if(action == EXITGAME):
            print "EXITING"
            state = EXIT
    elif (state == RUN):
        print "RUNNING + action = "+str(action)
        if(action == DIG):
            xindex, yindex = grid.get_tile_index( mousepos )
            #text_buffer.append( str(xindex)+" "+str(yindex)  )##debugging to see if finding pos from click works ## edit works
            if(xindex>=0 and yindex>=0):
                tile = search_tile((xindex, yindex), tiles)
                tile.dig() ##error here, thinks tiles[i] is a bool type ##edit fixed... prob was there was a field called dig and a func named dig()
                if(tile.is_mine()):
                    state = LOSE
                lastclick = (xindex,yindex)
                del xindex,yindex
        elif(action == FLAG):
            xindex, yindex = grid.get_tile_index( mousepos )
            if (xindex >=0 and yindex>=0):
                tile = search_tile((xindex,yindex), tiles)
                if(tile.is_flagged()):
                    tile.unflag()
                    num_flags = num_flags+1
                    if(tile.is_mine()):
                        num_flagged_mines = num_flagged_mines-1
                elif(num_flags>0):
                    tile.flag()
                    num_flags = num_flags-1
                    if(tile.is_mine()):
                        num_flagged_mines = num_flagged_mines+1
                lastclick = (xindex,yindex)
                del xindex,yindex
        elif(action == NEWGAME):
            state = INIT
        elif(action == EXITGAME):
            state = EXIT
        elif(action == NONE):
            if(num_flagged_mines >= num_mines):
                state = WIN
    action = NONE

    #events
    for event in pygame.event.get():
        if(event.type == QUIT):
            pygame.quit()
            sys.exit()
        if(event.type == KEYDOWN):
            if(event.key == K_ESCAPE):
                action = EXITGAME
            if(event.key==K_SPACE):
                color = (random.randint(0,255), random.randint(0,255), random.randint(0,255),)
                grid.set_line_color(color)
                fill_color = (random.randint(0,255), random.randint(0,255), random.randint(0,255))
            if(event.key==K_F1):
                state = INIT
        if(event.type == MOUSEMOTION):
            mousepos = event.pos
        if(event.type == MOUSEBUTTONDOWN):
            if(event.button == 1):
                action = DIG
                mousepos = event.pos
            if(event.button == 3):
                action = FLAG
                mousepos = event.pos

    #clear surface w/ bg color
    print"\tDRAWING"
    surface.fill( fill_color )

    if(state != INIT):
        #draw grid
        print"\tdrawing grid"
        grid.draw_grid(surface)
        #draw tiles
        print "\tdrawing tiles"
        for tile in tiles:
            a,b = grid.get_tile_pos(tile.get_pos())
            if(tile.get_image_id()==0):
                surface.blit(tile_1, (a,b) )
            elif(tile.get_image_id()==1):
                surface.blit(tile_2, (a,b) )
            elif(tile.get_image_id()==2):
                surface.blit(tile_3, (a,b) )
            elif(tile.get_image_id()==3):
                surface.blit(tile_4, (a,b) )
            elif(tile.get_image_id()==4):
                surface.blit(tile_5, (a,b) )
        del a,b
        #draw flags
        print "\tdrawing flags"
        for tile in tiles:
            if(tile.is_flagged()):
                a,b = grid.get_tile_pos(tile.get_pos())
                surface.blit(flag_pic, (a,b))
                del a,b
        #draw digs then numbers
        print"\tdrawing numbers"
        for tile in tiles:
            ##check if tile is digged
            if(tile.is_digged()):
                a,b = tile.get_pos()
                x,y = grid.get_tile_pos((a,b))
                ###searching for adj. tiles
                surface.blit(dirt_pic, (x,y))
                count = 0
                for tile in tiles:
                    c,d = tile.get_pos()
                    if( tile.is_mine() and ((c==a-1 and d==b-1)or(c==a and d==b-1)or(c==a+1 and d==b-1)or(c==a-1 and d==b)or(c==a+1 and d==b)or(c==a-1 and d==b+1)or(c==a and d==b+1)or(c==a+1 and d==b+1)) ):
                        count = count+1
                ###draw nums
                if (count==0):
                    surface.blit(zero, (x,y))
                elif (count==1):
                    surface.blit(one, (x,y))
                elif (count==2):
                    surface.blit(two, (x,y))
                elif (count==3):
                    surface.blit(three, (x,y))
                elif (count==4):
                    surface.blit(four, (x,y))
                elif (count==5):
                    surface.blit(five, (x,y))
                elif (count==6):
                    surface.blit(six, (x,y))
                elif (count==7):
                    surface.blit(seven, (x,y))
                elif (count==8):
                    surface.blit(eight, (x,y))
                del a,b,c,d,count,x,y
        #draw win or lose if won or lost game
        if(state == LOSE):
            for tile in tiles:
                a,b = grid.get_tile_pos(tile.get_pos())
                if(tile.is_mine()):
                    surface.blit(kirby_1, (a,b))
                if(tile.is_mine() and tile.is_flagged()):
                    surface.blit(cross,(a,b))
                x,y = tile.get_pos()
                xx,yy = lastclick
                if(x== xx and y == yy):
                    surface.blit(circle,(a,b))
                del a,b,x,y,xx,yy
        if(state == WIN):
            for tile in tiles:
                a,b = grid.get_tile_pos(tile.get_pos())
                if(tile.is_mine()):
                    surface.blit(kirby_1, (a,b))
                    surface.blit(cross, (a,b))

    #add to text buffer
    text_buffer.append("Find The Kirbies")
    text_buffer.append("aka MineSweeper")
    text_buffer.append("")
    if(action == NEWGAME or state==INIT):
        text_buffer.append("State: INIT")
    elif(state == RUN):
        text_buffer.append("State: RUN")
    elif(state == WIN):
        text_buffer.append("State: WIN")
    elif(state == LOSE):
        text_buffer.append("State: LOSE")
    elif(state == EXIT):
        text_buffer.append("State: EXIT")
    text_buffer.append("")
    text_buffer.append("FlagsLeft: "+str(num_flags)+"/"+str(max_flags))
    text_buffer.append("")
    a,b = mousepos
    text_buffer.append("MousePos: ( "+str(a)+" , "+str(b)+" )")
    a,b = lastclick
    text_buffer.append("LastClick: ( "+str(a)+" , "+str(b)+" )")
    text_buffer.append("====================")
    text_buffer.append("Help:")
    text_buffer.append("ESC: Quit")
    text_buffer.append("F1: New Game")
    text_buffer.append("Mouse1: Dig (find kirby)")
    text_buffer.append("Mouse3: Flag Spot")
    del a,b

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
                
    #repaint
    pygame.display.update()
    fps.tick(60)

pygame.quit()
