%% Color Enhancement Module -- Authored by HuangDao,08/17/2015  
% functions: input a image of type BMP or PNG, the program will decide to  
% do the Color Enhancement choice for you.There are four types of Enhanced  
% intensity - 20,40,60,80.The larger number stands for stronger  
% enhancement.  
% And we can also choose the simple color channel(eg.R,G,B) to do the  
% enhancement.There are also four different types of enhanced intensity.  
%  
% parameters table  
%  ------------------------------------------------------------------------  
% | Enhanced  |     MATLAB params             |      OpenCV params         |  
% | intensity |p1        p2        p3         | p1        p2        p3     |  
% | 20        |-0.1661   0.2639    -0.003626  |-0.0006512 0.2639    -0.9246|  
% | 40        |-0.4025   0.6238    -0.0005937 |0.001578   0.6238    -0.1514|  
% | 60        |1.332     1.473     -0.01155   |-0.005222  1.473     -2.946 |  
% | 80        |-4.813    3.459     -0.004568  |-0.01887   3.459     -1.165 |  
%  ------------------------------------------------------------------------  
  
clc; clear ;close all  
% 载入文件夹  
pathName = '.\';  
fileType = '*.bmp';  
files    = dir([pathName fileType]);  
len      = length(files);  
  
for pic = 5%1:1:len  
    srcName = files(pic).name;  
    srcImg  = imread(srcName);  
    srcHSV  = rgb2hsv(srcImg);  
    srcH    = srcHSV(:,:,1);  
    srcS    = srcHSV(:,:,2);  
    srcV    = srcHSV(:,:,3);  
    meanS   = mean(srcS(:));  
    varS    = std2(srcS);  
    %图像整体进行色彩增强处理  
    if (meanS >= 0.5)  
        p1 = 0;p2 = 0;p3 = 0;  
    else if (meanS >= 0.35 && meanS < 0.5)  
            p1 = -0.1661;p2 = 0.2639;p3 = -0.003626;  
        else if (meanS >=0.2 && meanS <0.35)  
                p1 = -0.4025;p2 = 0.6238;p3 = -0.0005937;  
            else  
                p1 = 1.332;p2 = 1.473;p3 = -0.01155;  
            end  
        end  
    end  
    dstS = srcS + p1*srcS.*srcS + p2*srcS + p3 ;  
    dstHSV = srcHSV;  
    dstHSV(:,:,2) = dstS;  
    dstImg = hsv2rgb(dstHSV);  
    figure;imshow(srcImg);  
    figure;imshow(dstImg);  
    %指定R,G,B通道进行色彩增强处理,红色范围（[225-255]）,绿色范围（75-[105-135]-165）,蓝色范围（[-15-15]）  
    p11 = -0.4025;p21 = 0.6238;p31 = -0.0005937;%周边杂色调整系数，40  
    p12 = 1.332;  p22 = 1.473; p32 = -0.01155;  %纯色区域调整系数，60  
    compHue = srcH;  
    GcompS  = dstS;  
    RcompS  = dstS;  
    BcompS  = dstS;  
    channel = 'B';  
    switch channel  
        case 'G'  
            I1 = find(compHue > 0.2083 & compHue <0.2917);  
            GcompS(I1) = dstS(I1) + dstS(I1).*dstS(I1)*p11 + dstS(I1)*p21 + p31;  
            I2 = find(compHue >= 0.2917 & compHue <= 0.3750);  
            GcompS(I2) = dstS(I2) + dstS(I2).*dstS(I2)*p12 + dstS(I2)*p22 + p32;  
            I3 = find(compHue > 0.3750 & compHue <0.4583);  
            GcompS(I3) = dstS(I3) + dstS(I3).*dstS(I3)*p11 + dstS(I3)*p21 + p31;  
            compHSV = dstHSV;  
            compHSV(:,:,2) = GcompS;  
            dstImgG = hsv2rgb(compHSV);  
            figure;imshow(dstImgG);  
        case 'R'  
            I1 = find(compHue > 0.875 & compHue <0.9583);  
            RcompS(I1) = dstS(I1) + dstS(I1).*dstS(I1)*p11 + dstS(I1)*p21 + p31;  
            I2 = find(compHue >= 0.9583 | compHue <= 0.0417);  
            RcompS(I2) = dstS(I2) + dstS(I2).*dstS(I2)*p12 + dstS(I2)*p22 + p32;  
            I3 = find(compHue > 0.0417 & compHue <0.125);  
            RcompS(I3) = dstS(I3) + dstS(I3).*dstS(I3)*p11 + dstS(I3)*p21 + p31;  
            compHSV = dstHSV;  
            compHSV(:,:,2) = RcompS;  
            dstImgR = hsv2rgb(compHSV);  
            figure;imshow(dstImgR);  
        case 'B'  
            I1 = find(compHue > 0.5417 & compHue <0.625);  
            BcompS(I1) = dstS(I1) + dstS(I1).*dstS(I1)*p11 + dstS(I1)*p21 + p31;  
            I2 = find(compHue >= 0.625 & compHue <= 0.7083);  
            BcompS(I2) = dstS(I2) + dstS(I2).*dstS(I2)*p12 + dstS(I2)*p22 + p32;  
            I3 = find(compHue > 0.7083 & compHue <0.7917);  
            BcompS(I3) = dstS(I3) + dstS(I3).*dstS(I3)*p11 + dstS(I3)*p21 + p31;  
            compHSV = dstHSV;  
            compHSV(:,:,2) = BcompS;  
            dstImgB = hsv2rgb(compHSV);  
            figure;imshow(dstImgB);  
    end  
    %进行R,G,B通道之间的互换  
    convH = zeros(size(srcH,1),size(srcH,2)); %convert  
    deltaHue = 240;  
    switch deltaHue  
        case 120  
            disp('R -> G')  
            convH = srcH + 1/3;  
            convH(find(convH >= 1)) = convH(find(convH >= 1)) - 1;  
        case 240  
            disp('R -> B')  
            convH = srcH + 2/3;  
            convH(find(convH >= 1)) = convH(find(convH >= 1)) - 1;  
    end  
    convHSV = dstHSV;  
    convHSV(:,:,1) = convH;  
    convImg = hsv2rgb(convHSV);  
    figure;imshow(convImg)  
    pause();  
end  
