class GifAnimation:
    __doc__ = """a sequence animation from gif """

    def __init__(self):
        self.frame_sequence = []
        self.current_frame_id = -1
        self.file_name = ''
        self.palette = None
        self.format = 'RGBA'
        self.info=None
        pass

    def load(self, gif_file_name):
        import Image as __myImage
        #import pygame

        if gif_file_name[-3:] != "gif" and gif_file_name[-3:] != "GIF":
            raise Exception("The image is not gif format!")
            return
        self.file_name = gif_file_name
        im = __myImage.open(gif_file_name)
        #im=im0.convert("RGBA")
        # should be executed before other function, such as get/set palette
        if len(im.tile) > 0:
            tag, size0, offset, extra = im.tile[0]

        self.palette = im.getpalette()
        self.info = im.info
        #imstr=im.convert('RGBA').tostring()
        self.frame_sequence = []
        t_seq=[]
        s_seq=[]
        try:
            while True:
                im.putpalette(self.palette)
                new_im = __myImage.new(self.format, im.size, (0, 0, 0, 0))
                new_im.paste(im.crop(size0),size0)
                t_seq.append(new_im)#.crop(size0))
                s_seq.append(size0)
                #imstr = new_im.tostring()
                im.seek(im.tell() + 1)
                tag, size0, offset, extra = im.tile[0]
                #frame_sequence.append(pygame.image.fromstring(imstr, im.size, 'RGBA'))
        except EOFError:
            print len(self.frame_sequence), "frames"

        bounding=s_seq[0]
        for size in s_seq[1:]:
            a=[min((bounding[i],size[i])) for i in xrange(2) ]                
            bounding=a+[max((bounding[i],size[i])) for i in xrange(2,4) ]                

        print bounding
        self.frame_sequence=[im.crop(bounding) for im in t_seq]

    def get1frame(self, index=-1, gif_seq=None):
        if index >= 0: self.current_frame_id = index
        if self.current_frame_id >= len(self.frame_sequence): self.current_frame_id %= len(self.frame_sequence)
        if not gif_seq:
            im = self.frame_sequence[self.current_frame_id]
        else:
            im = gif_seq[self.current_frame_id]

        self.current_frame_id += 1
        return im



