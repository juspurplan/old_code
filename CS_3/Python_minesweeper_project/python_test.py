import pygame
import sys
import random
from pygame.event import *
from pygame.locals import *
from pygame.key import *

pygame.init()

fps = pygame.time.Clock()
surface = pygame.display.set_mode( (800,600) )
clock = pygame.time.Clock()

x = 0
y =0
rad =10

r=0
g=0
b=0
a=0

while True:
    surface.fill((0,0,0))
    
    #params (surface, color tuple, loc tuple, radius, width)
    pygame.draw.circle(surface, (r,g,b,a), (x,y), rad, 0 )
    
    if(x < 800):
        x=x+25
    else:
        x=0
        if(y<600):
            y = y+25
        else:
            y =0

    r = random.randint(0,255)
    g = random.randint(0,255)
    b = random.randint(0,255)
    a = random.randint(0,255)

    font = pygame.font.Font(None, 30)
    text = font.render("Hello = "+str(clock.get_time()), 1, (255,255,255) )
    surface.blit(text, (350,250))


    #n= y+300
    #m= x+400
    #m = m%800
    #n = n%600
    #r = random.randint(0,255)
    #g = random.randint(0,255)
    #b = random.randint(0,255)
    #a = random.randint(0,255)
    #pygame.draw.circle(surface, (r,g,b,a), (m,n), rad, 0 )


    #r = random.randint(0,255)
    #g = random.randint(0,255)
    #b = random.randint(0,255)
    #a = random.randint(0,255)
    #o = random.randint(0,800)
    #p = random.randint(0,600)
    #pygame.draw.circle(surface, (r,g,b,a), (o,p), rad, 0 )


    #events
    for event in pygame.event.get():
        if(event.type == QUIT):
            pygame.quit()
            sys.exit()
        if(event.type == KEYDOWN):
            if(event.key == K_ESCAPE):
                pygame.quit()
                sys.exit()
    
    #repaint
    pygame.display.update()
    fps.tick(60)
    clock.tick()
