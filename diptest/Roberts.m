clc  
clear  
x=imread('Moon.bmp');
[m,n,k]=size(x);      
xd=double(x);
b=zeros(m,n,3);   
c=zeros(m,n,3);

for top=1:3
    for i=1:m-2   
        for j=1:n-2   
            b(i+1,j+1,top)=xd(i,j,top)-xd(i+1,j+1,top);   
            c(i+1,j+1,top)=xd(i,j+1,top)-xd(i+1,j,top);   
            b(i+1,j+1,top)=sqrt(b(i+1,j+1,top)^2+c(i+1,j+1,top)^2)+100;   
        end  
    end
end
imshow(uint8(x)-uint8(b));

%clear;