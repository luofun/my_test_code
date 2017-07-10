clear
in=imread('Moon.bmp');
sigma=5;
[NA, out] = CBM3D(1, in, sigma); 
imshow(out);