clear,clc
in=double(imread('Moon.bmp'));
sigma=5;
[NA1, y1] = BM3D(1, in(:,:,1), sigma);
[NA2, y2] = BM3D(1, in(:,:,2), sigma);
[NA3, y3] = BM3D(1, in(:,:,3), sigma);
y=uint8(in);
y(:,:,1)=uint8(y1*255);
y(:,:,2)=uint8(y2*255);
y(:,:,3)=uint8(y3*255);

alpha_sharp = 1.3;
[ysharp1] = BM3DSHARP(y(:,:,1), sigma, alpha_sharp);
[ysharp2] = BM3DSHARP(y(:,:,2), sigma, alpha_sharp);
[ysharp3] = BM3DSHARP(y(:,:,3), sigma, alpha_sharp);
out=uint8(in);
out(:,:,1)=uint8(ysharp1*255);
out(:,:,2)=uint8(ysharp2*255);
out(:,:,3)=uint8(ysharp3*255);

F=rgb2hsv(out);
F(:,:,2)=F(:,:,2)*1.8;
F(:,:,3)=F(:,:,3)*5/3-1/3;
Iout=hsv2rgb(F)*255;
figure;
imshow(uint8(Iout));
