clear,clc
fc = imread('Moon.bmp');
h = rgb2hsi(fc);
H = h (:,:,1);
S = h (:,:,2);
I = h (:,:,3);
figure;imshow(fc);  title('ԭͼ');
%ƽ���˲� 
m=fspecial('average',[8,8]); 
s_filtered=imfilter(S,m);
img_s_filtered = cat(3,H,s_filtered,I); 
rgb_s_filtered = hsi2rgb(img_s_filtered);
figure;imshow(rgb_s_filtered);  title('S����ģ����');
imwrite(rgb_s_filtered, 'S����ģ����.jpg');