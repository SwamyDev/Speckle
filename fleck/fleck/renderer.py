import os
from ctypes import cdll

speckle = cdll.LoadLibrary(os.path.join(os.path.dirname(__file__), 'lib/libSpeckle.so'))


class Renderer:
    def __init__(self):
        self.renderer = speckle.MakeRenderer()

    def resize(self, width, height):
        speckle.Resize(self.renderer, width, height)

    def render(self):
        speckle.Render(self.renderer)
