import sys
import OpenGL.GL as gl
from PyQt5 import uic
from PyQt5.QtCore import QTimer
from PyQt5.QtWidgets import QMainWindow, QApplication
from fleck import Renderer


class MainWindow(QMainWindow):
    def __init__(self, *args):
        super(MainWindow, self).__init__(*args)
        uic.loadUi("main.ui", self)
        self.speckle = None

    def setupUI(self):
        self.windowsHeight = self.view.height()
        self.windowsWidth = self.view.width()

        self.view.initializeGL()
        self.view.resizeGL(self.windowsWidth, self.windowsHeight)
        self.view.paintGL = self.paintGL
        self.view.initializeGL = self.initializeGL

    def initializeGL(self):
        gl.glEnable(gl.GL_DEPTH_TEST)

    def paintGL(self):
        if self.speckle is None:
            self.speckle = Renderer()
            self.speckle.resize(self.windowsWidth, self.windowsHeight)
        self.speckle.render()

    def update_view(self):
        self.view.update()


if __name__ == "__main__":
    app = QApplication(sys.argv)
    window = MainWindow()
    window.setupUI()
    window.show()

    def render():
        window.update_view()

    timer = QTimer()
    timer.timeout.connect(render)
    timer.start(100)
    sys.exit(app.exec_())
