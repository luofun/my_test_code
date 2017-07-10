clear,clc
i=imread('Moon.bmp');

j=double(i);

h=[0 1 0;1 -4 1;0 1 0];%À­ÊÏËã×Ó

y=i;

y(:,:,1) = i(:,:,1) - uint8(imfilter(i(:,:,1), h, 'replicate'));
y(:,:,2) = i(:,:,2) - uint8(imfilter(i(:,:,2), h, 'replicate'));
y(:,:,3) = i(:,:,3) - uint8(imfilter(i(:,:,3), h, 'replicate'));
imshow(y);

