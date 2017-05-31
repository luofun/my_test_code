from PIL import Image
import matplotlib.pyplot as plt
img=Image.open('xuecolorout.bmp')
img.show()
img2=Image.open('xuegaryout.bmp')
img2.show()
print('\nxuecolorout.bmp info')
print(img.size)
print(img.mode) 
print(img.format)
print('\nxuegaryout.bmp info')
print(img2.size)
print(img2.mode) 
print(img2.format)