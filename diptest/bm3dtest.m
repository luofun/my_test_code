clear
in=double(imread('Moon.bmp'));
sigma=5;
[NA1, y1] = BM3D(1, in(:,:,1), sigma);
[NA2, y2] = BM3D(1, in(:,:,2), sigma);
[NA3, y3] = BM3D(1, in(:,:,3), sigma);
y=uint8(in);
y(:,:,1)=uint8(y1*255);
y(:,:,2)=uint8(y2*255);
y(:,:,3)=uint8(y3*255);
imshow(y);