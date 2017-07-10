clear,clc;
bb=8; % block size
RR=4; % redundancy factor
K=RR*bb^2; % number of atoms in the dictionary

sigma = 10; 
imageName = 'Moon.bmp';
IMin=imread(imageName);
y=IMin;
IMin1=im2double(IMin(:,:,1));
IMin2=im2double(IMin(:,:,2));
IMin3=im2double(IMin(:,:,3));
if (max(IMin1(:))<2)
    IMin1 = IMin1*255;
end
if (max(IMin2(:))<2)
    IMin2 = IMin2*255;
end
if (max(IMin3(:))<2)
    IMin3 = IMin3*255;
end
[IoutAdaptive1,output1] = denoiseImageKSVD(IMin1, sigma,K);
[IoutAdaptive2,output2] = denoiseImageKSVD(IMin2, sigma,K);
[IoutAdaptive3,output3] = denoiseImageKSVD(IMin3, sigma,K);
y(:,:,1)=uint8(IoutAdaptive1);
y(:,:,2)=uint8(IoutAdaptive2);
y(:,:,3)=uint8(IoutAdaptive3);
imshow(y);
