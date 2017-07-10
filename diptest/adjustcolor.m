clear,clc
i=imread('Moon.bmp');
j=imadjust(i,[0.3,0.7],[]);
imshow(j)%对比度调整
