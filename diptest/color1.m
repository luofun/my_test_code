clear,clc
rgb= imread('Moon.bmp');
figure;  imshow(rgb); title('ԭͼ');
 %ƽ���˲�  
r=rgb(:,:,1);  
g=rgb(:,:,2); 
 b=rgb(:,:,3); 
m=fspecial('average',[8,8]); 
 r_filtered=imfilter(r,m);
 g_filtered=imfilter(g,m); 
 b_filtered=imfilter(b,m);  
 rgb_filtered=cat(3,r_filtered,g_filtered,b_filtered); 
 figure;  imshow(rgb_filtered);  title('ģ����');
imwrite(rgb_filtered, 'RGB��ɫ�ռ�ģ����.jpg');