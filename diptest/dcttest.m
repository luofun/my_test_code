clear,clc;
bb=8; % block size
RR=4; % redundancy factor
K=RR*bb^2; % number of atoms in the dictionary

sigma = 5; 
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
[IoutDCT1,output1] = denoiseImageDCT(IMin1, sigma, K);
[IoutDCT2,output2] = denoiseImageDCT(IMin2, sigma, K);
[IoutDCT3,output3] = denoiseImageDCT(IMin3, sigma, K);
y(:,:,1)=uint8(IoutDCT1);
y(:,:,2)=uint8(IoutDCT2);
y(:,:,3)=uint8(IoutDCT3);
imshow(y);