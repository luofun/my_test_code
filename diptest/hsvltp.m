clc,clear ,close all  
src = imread('Moon.bmp');  
srcHDR = double(src) * 256;  
hsv = rgb2hsv(srcHDR);  
J = adapthisteq(uint16(hsv(:,:,3)));  
hsv(:,:,3) = double(J);  
dstHDR = hsv2rgb(hsv);  
imshow(uint16(dstHDR));
imwrite(uint8(dstHDR/256),'hsvLTPU8.bmp');
imwrite(uint16(dstHDR),'hsvLTP.png');
clear;
