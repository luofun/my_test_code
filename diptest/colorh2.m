clear,clc
fc = imread('Moon.bmp');
h = rgb2hsi(fc);
H = h (:,:,1);
S = h (:,:,2);
I = h (:,:,3);

figure;imshow(fc);  title('ԭͼ');
lapMatrix=[1 1 1;1 -8 1;1 1 1];    
i_tmp=imfilter(H,lapMatrix,'replicate'); 
H_sharped=imsubtract(H,i_tmp); 
img_h_sharped = cat(3,H_sharped,S,I); 
rgb_h_sharped = hsi2rgb(img_h_sharped);
figure; imshow(rgb_h_sharped); title('H�����񻯺�');
imwrite(rgb_h_sharped, 'H�����񻯺�.jpg');