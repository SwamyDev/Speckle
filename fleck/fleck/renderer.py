import os
import platform
from ctypes import cdll

name = "libspeckle.so"
if platform.uname()[0] == "Windows":
    name = "speckle.dll"

speckle = cdll.LoadLibrary(os.path.join(os.path.dirname(__file__), os.path.join('lib', name)))


class Renderer:
    def __init__(self):
        self.renderer = speckle.MakeRenderer()

    def resize(self, width, height):
        speckle.Resize(self.renderer, width, height)

    def render(self):
        speckle.Render(self.renderer)
