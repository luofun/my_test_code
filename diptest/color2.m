clear,clc
rgb= imread('Moon.bmp');
figure;  imshow(rgb); title('ԭͼ');
lapMatrix=[1 1 1;1 -8 1;1 1 1];    
  i_tmp=imfilter(rgb,lapMatrix,'replicate'); 
 i_sharped=imsubtract(rgb,i_tmp); 
 figure;   imshow(i_sharped); title('�񻯺�');
imwrite(i_sharped, 'RGB��ɫ�ռ��񻯺�.jpg');