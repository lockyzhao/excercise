import sys

import pygame
import Image
from GifAnimation import GifAnimation
from pygame.locals import QUIT


def terminate():
    pygame.quit()
    sys.exit()


def make_render(image_sequence):
    seq = image_sequence
    id =[0]   # dont use local variable of simple type because myget1frame will change it.

    def myget1frame():
       #print id[0]
        im = seq[id[0]]
        id[0] = (id[0] + 1) % len(seq)
        return im

    return myget1frame


def load_anim_from_png(file_name):
    
    im = Image.open(file_name)
    image_seq = []
    for i in xrange(4):
        for j in xrange(4):
            im0 = im.crop([128 * x for x in (i, j, i + 1, j + 1)])
            image_seq.append(pygame.image.fromstring(im0.tostring(), im0.size, 'RGBA'))
    return image_seq


if __name__ == "__main__":
    pygame.init();
    main_clock = pygame.time.Clock()
    window = pygame.display.set_mode((800, 600))
    pygame.mouse.set_visible(True)
    font = pygame.font.SysFont(None, 32)

    scene=[]
    image_seq_list=[]
    #img=pygame.image.load('SnowPea.gif')
    # im = Image.open('SnowPea.gif')
    gif_anim = GifAnimation()
    gif_anim.load('BucketheadZombie.gif')
    image_seq_list.append([pygame.image.fromstring(im.tostring(), im.size, gif_anim.format) for im in gif_anim.frame_sequence])
    gif_anim.load("SnowPea.gif")
    image_seq_list.append([pygame.image.fromstring(im.tostring(), im.size, gif_anim.format) for im in gif_anim.frame_sequence])
    gif_anim.load("ConeheadZombieAttack.gif")
    image_seq_list.append([pygame.image.fromstring(im.tostring(), im.size, gif_anim.format) for im in gif_anim.frame_sequence])

    image_seq_list.append(load_anim_from_png('01.png'))
    #scene=[ make_render(image_seq), make_render(gif_seq) , make_render(gif_seq1),make_render(gif_seq2)]
    scene=[ make_render(x) for x in image_seq_list]
    #index = 0
    while True:
        for event in pygame.event.get():
            if event.type == QUIT:
                terminate()
        window.fill((0, 255, 0))
        #window.blit(gif_anim.get1frame(-1, gif_seq), (0, 0))

        for obj in scene:
            window.blit(obj(), (scene.index(obj)*100,0))
            #window.blit(get1_image_seq(), (300, 0))
        #index += 1
        #if index >= len(gif_seq): index %= len(gif_seq)
        pygame.display.update()
        main_clock.tick(8)

