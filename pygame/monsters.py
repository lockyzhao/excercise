import sys

import pygame
from GifAnimation import *
from pygame.locals import *



def terminate():
    pygame.quit()
    sys.exit()


if __name__ == "__main__":
    pygame.init();
    main_clock = pygame.time.Clock()
    window = pygame.display.set_mode((800, 600))
    pygame.mouse.set_visible(True)
    font = pygame.font.SysFont(None, 32)

    #img=pygame.image.load('SnowPea.gif')
    # im = Image.open('SnowPea.gif')
    gif_anim = GifAnimation()
    gif_anim.load('BucketheadZombie.gif')
    gif_seq = [pygame.image.fromstring(im.tostring(), im.size, gif_anim.format) for im in gif_anim.frame_sequence]

    pygame.display.update()
    index = 0
    while True:
        for event in pygame.event.get():
            if event.type == QUIT:
                terminate()
        window.fill((0, 255, 0))
        #window.blit(gif_anim.get1frame(-1, gif_seq), (0, 0))

        window.blit(gif_seq[index], (0, 0))
        index += 1
        if index >= len(gif_seq): index %= len(gif_seq)
        pygame.display.update()
        main_clock.tick(8)

