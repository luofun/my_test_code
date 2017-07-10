clear,clc
rgb= imread('Moon.bmp');
figure;  imshow(rgb); title('原图');
 %平滑滤波  
r=rgb(:,:,1);  
g=rgb(:,:,2); 
 b=rgb(:,:,3); 
m=fspecial('average',[8,8]); 
 r_filtered=imfilter(r,m);
 g_filtered=imfilter(g,m); 
 b_filtered=imfilter(b,m);  
 rgb_filtered=cat(3,r_filtered,g_filtered,b_filtered); 
 figure;  imshow(rgb_filtered);  title('模糊后');
imwrite(rgb_filtered, 'RGB彩色空间模糊后.jpg');