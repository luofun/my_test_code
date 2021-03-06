figure(1);
RGB = imread('xue.bmp'); % 读取彩色图
subplot(121);
imshow(RGB);
title('彩色图');

[R, C, K] = size(RGB); % 新增的K表示颜色通道数

% 统计每个像素值出现次数
cnt = zeros(K, 256);
for i = 1 : R
    for j = 1 : C
        for k = 1 : K
            cnt(k, RGB(i, j, k) + 1) = cnt(k, RGB(i, j, k) + 1) + 1;
        end
    end
end

f = zeros(3, 256);
f = double(f); cnt = double(cnt);

% 统计每个像素值出现的概率， 得到概率直方图
for k = 1 : K
    for i = 1 : 256
        f(k, i) = cnt(k, i) / (R * C);
    end
end

figure(2);
bar(1:256,f(1,:),0.2);
figure(3);
bar(1:256,f(2,:),0.2);
figure(4);
bar(1:256,f(3,:),0.2);

% 求累计概率，得到累计直方图
for k = 1 : K
    for i = 2 : 256
        f(k, i) = f(k, i - 1) + f(k, i);
    end
end

% 用f数组实现像素值[0, 255]的映射。 
for k = 1 : K
    for i = 1 : 256
        f(k, i) = f(k, i) * 255;
    end
end

% 完成每个像素点的映射
%I = double(I);
for i = 1 : R
    for j = 1 : C
        for k = 1 : K
            RGB(i, j, k) = f(k, RGB(i, j, k) + 1);
        end
    end
end

% 输出
RGB = uint8(RGB);
figure(1);
subplot(122);
imshow(RGB);
title('彩色直方图均衡化');