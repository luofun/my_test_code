clear,clc
A=imread('Moon.bmp'); 
figure(1);
subplot(1,2,1);
imshow(A);
title('ԭͼ');
 
I=double(A);
h=[-1 -1 -1;-1 9 -1;-1 -1 -1];
J=conv2(I,h,'same');
K=uint8(J);
subplot(1,2,2);
imshow(K);