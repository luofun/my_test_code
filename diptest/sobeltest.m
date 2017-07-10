clear,clc
i=imread('Moon.bmp');

h=[1,2,1;0,0,0;-1,-2,-1];%SobelËã×Ó

j1=filter2(h,i(:,:,1));
j2=filter2(h,i(:,:,2));
j3=filter2(h,i(:,:,3));
y=i;
y(:,:,1)=i(:,:,1)-uint8(j1);
y(:,:,2)=i(:,:,2)-uint8(j2);
y(:,:,3)=i(:,:,3)-uint8(j3);

imshow(y);
