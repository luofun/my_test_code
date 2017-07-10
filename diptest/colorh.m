clear,clc
fc = imread('Moon.bmp');
h = rgb2hsi(fc);
H = h (:,:,1);
S = h (:,:,2);
I = h (:,:,3);

figure;imshow(fc);  title('ԭͼ');
m=fspecial('average',[8,8]); 
h_filtered=imfilter(H,m);
img_h_filtered = cat(3,h_filtered,S,I); 
rgb_h_filtered = hsi2rgb(img_h_filtered);
figure;imshow(rgb_h_filtered);  title('H����ģ����');
imwrite(rgb_h_filtered, 'H����ģ����.jpg');