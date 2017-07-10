% Color Enhancement  
clc,clear,close all  
src1 = imread('Moon.bmp');  
src2 = imread('wiennerpast.bmp');  
  
src1_hsv = rgb2hsv(src1);  
src2_hsv = rgb2hsv(src2);  
  
h1 = src1_hsv(:,:,1);  
s1 = src1_hsv(:,:,2);  
v1 = src1_hsv(:,:,3);  
  
h2 = src2_hsv(:,:,1);  
s2 = src2_hsv(:,:,2);  
v2 = src2_hsv(:,:,3);  
%   
meanS1 = mean(s1(:));  
varS1  = std2(s1);   
%   
meanS2 = mean(s2(:));  
varS2  = std2(s2);   
%   
deltaS = s2 - s1;  
deltaV = v2 - v1;  
  
%% test1 : 观测“原饱和度-饱和度调整增量”的关系 saturation and delta saturation  
figure;  
oriS = zeros(101,2);  
s3 = s1;  
j = 1;  
for i = 0: 0.01 : 1  
    oriS(j,1) = i + 0.01;  
    oriS(j,2) =  mean(deltaS(find(s1 > i & s1< i + 0.01)));  
    j = j + 1;  
end  
X  = oriS(:,1);  
Y  = oriS(:,2);  
XX = oriS(:,1) * 255;  
YY = oriS(:,2) * 255;  
plot(XX,YY)  
