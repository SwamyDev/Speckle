from ctypes import cdll

lib = cdll.LoadLibrary("../lib/libSpeckle.so")


class Speckle:
    def __init__(self):
        self.renderer = lib.MakeRenderer()

    def Resize(self, width, height):
        lib.Resize(self.renderer, width, height)

    def Render(self):
        lib.Render(self.renderer)

