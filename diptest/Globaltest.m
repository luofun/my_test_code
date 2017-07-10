clear,clc;
bb=8; % block size
RR=4; % redundancy factor
K=RR*bb^2; % number of atoms in the dictionary

sigma = 25; 
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
[IoutGlobal1,output1] = denoiseImageGlobal(IMin1, sigma,K);
[IoutGlobal2,output2] = denoiseImageGlobal(IMin2, sigma,K);
[IoutGlobal3,output3] = denoiseImageGlobal(IMin3, sigma,K);
y(:,:,1)=uint8(IoutGlobal1);
y(:,:,2)=uint8(IoutGlobal2);
y(:,:,3)=uint8(IoutGlobal3);