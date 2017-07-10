clear,clc
fc = imread('Moon.bmp');
h = rgb2hsi(fc);
H = h (:,:,1);
S = h (:,:,2);
I = h (:,:,3);
figure;imshow(fc);  title('原图');
lapMatrix=[1 1 1;1 -8 1;1 1 1];    
i_tmp=imfilter(S,lapMatrix,'replicate'); 
s_sharped=imsubtract(S,i_tmp); 
img_s_sharped = cat(3,H,s_sharped,I); 
rgb_s_sharped = hsi2rgb(img_s_sharped);
figure; imshow(rgb_s_sharped); title('S分量锐化后');
imwrite(rgb_s_sharped, 'S分量锐化后.jpg');