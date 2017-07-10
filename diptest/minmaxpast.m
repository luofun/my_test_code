clear;
clc;
test=imread('Moon.bmp');
outmin=test;
outmax=test;
outmin(:,:,1)=ordfilt2(test(:,:,1),1,ones(3,3));
outmin(:,:,2)=ordfilt2(test(:,:,2),1,ones(3,3));
outmin(:,:,3)=ordfilt2(test(:,:,3),1,ones(3,3));
imwrite(outmin,'minpast.bmp');

outmax(:,:,1)=ordfilt2(test(:,:,1),9,ones(3,3));
outmax(:,:,2)=ordfilt2(test(:,:,2),9,ones(3,3));
outmax(:,:,3)=ordfilt2(test(:,:,3),9,ones(3,3));
imwrite(outmax,'maxpast.bmp');

subplot(1,2,1);
imshow(outmin);
subplot(1,2,2);
imshow(outmax);
clear;