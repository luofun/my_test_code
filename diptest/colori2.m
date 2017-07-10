clear,clc
fc = imread('Moon.bmp');
h = rgb2hsi(fc);
H = h (:,:,1);
S = h (:,:,2);
I = h (:,:,3);
figure;imshow(fc);  title('原图');
lapMatrix=[1 1 1;1 -8 1;1 1 1];    
i_tmp=imfilter(I,lapMatrix,'replicate'); 
i_sharped=imsubtract(I,i_tmp); 
img_i_sharped = cat(3,H,S,i_sharped); 
rgb_i_sharped = hsi2rgb(img_i_sharped);
figure; imshow(rgb_i_sharped); title('I分量锐化后');
imwrite(rgb_i_sharped, 'I分量锐化后.jpg');