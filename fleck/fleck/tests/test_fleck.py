import pytest
from OpenGL.GL import *
from OpenGL.GLUT import *
from PIL import Image

import fleck

WIDTH = 160
HEIGHT = 90


class Colors:
    BLACK = (0, 0, 0, 255)
    TEST_TRIANGLE = (255, 127, 51, 255)


@pytest.fixture(autouse=True)
def context():
    glutInit(sys.argv)
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB)
    glutInitWindowSize(WIDTH, HEIGHT)
    glutCreateWindow(b"Test OpenGL context")


def get_scene():
    glPixelStorei(GL_PACK_ALIGNMENT, 1)
    raw = glReadPixels(0, 0, WIDTH, HEIGHT, GL_RGBA, GL_UNSIGNED_BYTE)
    return Image.frombytes("RGBA", (WIDTH, HEIGHT), raw)


def test_render_test_scene():
    renderer = fleck.Renderer()
    renderer.render()

    scene = get_scene()

    assert scene.getpixel((0, 0)) == Colors.BLACK
    assert scene.getpixel((WIDTH / 2, HEIGHT / 2)) == Colors.TEST_TRIANGLE
