import numpy as np
from PIL import Image
from matplotlib import cm
matrix = np.loadtxt('BITMAP.txt', usecols=range(1000))
im = Image.fromarray(np.uint8(cm.turbo(matrix)*255))
im.save("map.bmp")