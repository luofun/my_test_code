clear,clc
rgb= imread('Moon.bmp');
figure;  imshow(rgb); title('原图');
lapMatrix=[1 1 1;1 -8 1;1 1 1];    
  i_tmp=imfilter(rgb,lapMatrix,'replicate'); 
 i_sharped=imsubtract(rgb,i_tmp); 
 figure;   imshow(i_sharped); title('锐化后');
imwrite(i_sharped, 'RGB彩色空间锐化后.jpg');