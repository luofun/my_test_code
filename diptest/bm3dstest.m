clear
in=imread('Moon.bmp');
sigma = 5;
alpha_sharp = 1.3;
[ysharp1] = BM3DSHARP(in(:,:,1), sigma, alpha_sharp);
[ysharp2] = BM3DSHARP(in(:,:,2), sigma, alpha_sharp);
[ysharp3] = BM3DSHARP(in(:,:,3), sigma, alpha_sharp);
out=in;
out(:,:,1)=uint8(ysharp1*255);
out(:,:,2)=uint8(ysharp2*255);
out(:,:,3)=uint8(ysharp3*255);
imshow(out)
