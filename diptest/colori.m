clear,clc
fc = imread('Moon.bmp');
h = rgb2hsi(fc);
H = h (:,:,1);
S = h (:,:,2);
I = h (:,:,3);
figure;imshow(fc);  title('原图');
m=fspecial('average',[8,8]); 
i_filtered=imfilter(I,m);
img_i_filtered = cat(3,H,S,i_filtered); 
rgb_i_filtered = hsi2rgb(img_i_filtered);
figure;imshow(rgb_i_filtered);  title('I分量模糊后');
imwrite(rgb_i_filtered, 'I分量模糊后.jpg');