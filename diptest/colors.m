clear,clc
fc = imread('Moon.bmp');
h = rgb2hsi(fc);
H = h (:,:,1);
S = h (:,:,2);
I = h (:,:,3);
figure;imshow(fc);  title('原图');
%平滑滤波 
m=fspecial('average',[8,8]); 
s_filtered=imfilter(S,m);
img_s_filtered = cat(3,H,s_filtered,I); 
rgb_s_filtered = hsi2rgb(img_s_filtered);
figure;imshow(rgb_s_filtered);  title('S分量模糊后');
imwrite(rgb_s_filtered, 'S分量模糊后.jpg');