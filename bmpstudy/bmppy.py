﻿from PIL import Image
import matplotlib.pyplot as plt
img=Image.open('xue.bmp')
img.show()
img2=Image.open('gxue.bmp')
img2.show()
'''plt.figure("1")
plt.imshow(img)
plt.show()
plt.figure("2")
#plt.imshow(img2)
plt.imshow(img2, cmap='Greys_r')
plt.show()'''
print('\nxue.bmp info')
print(img.size)
print(img.mode) 
print(img.format)
print('\ngxue.bmp info')
print(img2.size)
print(img2.mode) 
print(img2.format)