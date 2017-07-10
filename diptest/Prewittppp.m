clc  
clear  
x=imread('Moon.bmp');   
[m,n,k]=size(x);   
%figure,imshow(x);   
x=double(x);   
b=zeros(m,n,k);   
c=zeros(m,n,k);
for top=1:k
for i=1:m-2   
    for j=1:n-2   
        b(i+1,j+1,top)=-x(i,j,top)-x(i+1,j,top)-x(i+2,j+2,top)+x(i,j+2,top)+x(i+1,j+2,top)+x(i+2,j+2,top);   
        c(i+1,j+1,top)=x(i,j,top)+x(i,j+1,top)+x(i,j+2,top)-x(i+2,j,top)-x(i+2,j+1,top)-x(i+2,j+2,top);   
        b(i+1,j+1,top)=sqrt(b(i+1,j+1,top)^2+c(i+1,j+1,top)^2)+100;   
        %这儿处理有两种方式，绝对值和统一加一个数,不同的处理会得到不同的效果   
%if b(i+1,j+1)<0   
    %b(i+1,j+1)=-b(i+1,j+1);   
   %end   
    end   
end
end
figure;imshow(uint8(x)-uint8(b));
clear;