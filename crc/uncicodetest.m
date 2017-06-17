clear;
clc;
txt2='hello ´ó¼ÒºÃ°¡';
txttt=abs(dec2bin(abs(txt2)))-48
sizeraw=size(txttt);
txtm=[zeros(sizeraw(1),16-sizeraw(2)),txttt]
rebuildtxt=char(bin2dec(num2str(txtm)))
crcmode=[1,1,0,1]; %crcmode = x^3 + x^2 + 1
txtmnew=[txtm,zeros(sizeraw(1),length(crcmode))];%finally style
R=length(crcmode)-1;
for i=1:sizeraw(1)   
[q,r] = deconv([txtm(i,:) zeros(1,R)],crcmode);
r=mod(r(end-R+1:end),2);
txtmnew(i,17:19)=r;
end %crc
for i=1:sizeraw(1) 
    tempsum=0;
   for j=1:length(txtmnew)
       tempsum=tempsum+txtmnew(i,j);
   end
   if mod(tempsum,2)==1
       txtmnew(i,20)=1;
   end
end
disp(txtmnew);
temptxt=txtmnew';
txtcolumns=temptxt(:)';
x=0:length(txtcolumns)*10-1;
y=zeros(1,length(txtcolumns)*10);
y2ask=zeros(1,length(txtcolumns)*10);
y2fsk=zeros(1,length(txtcolumns)*10);
y2psk=zeros(1,length(txtcolumns)*10);
ysin1=sin(2*pi/10*x);
ysin2=sin(4*pi/10*x);
ysin3=sin(2*pi/10*x+pi);
for i=1:length(txtcolumns)
   if  txtcolumns(i)==1
      y((i-1)*10:i*10)=1;
      y2ask((i-1)*10+1:i*10)=ysin1((i-1)*10+1:i*10);
      y2fsk((i-1)*10+1:i*10)=ysin2((i-1)*10+1:i*10);
      y2psk((i-1)*10+1:i*10)=ysin3((i-1)*10+1:i*10);
   elseif txtcolumns(i)==0
      y2fsk((i-1)*10+1:i*10)=ysin1((i-1)*10+1:i*10);
      y2psk((i-1)*10+1:i*10)=ysin1((i-1)*10+1:i*10);
   end
end
figure(1);
plot(x,y);
axis([0 length(txtcolumns)*10 -1 2]);
yn=awgn(y,40);
figure(2);
plot(x,yn);
axis([0 length(txtcolumns)*10 -1 2]);
figure(3);
plot(x,y2ask);
axis([0 length(txtcolumns)*10 -2 2]);
figure(4);
y2askn=awgn(y2ask,40);
plot(x,y2ask);
axis([0 length(txtcolumns)*10 -2 2]);
figure(5);
plot(x,y2fsk);
axis([0 length(txtcolumns)*10 -2 2]);
figure(6);
y2fskn=awgn(y2fsk,40);
plot(x,y2fsk);
axis([0 length(txtcolumns)*10 -2 2]);
figure(7);
plot(x,y2psk);
axis([0 length(txtcolumns)*10 -2 2]);
figure(8);
y2pskn=awgn(y2psk,40);
plot(x,y2psk);
axis([0 length(txtcolumns)*10 -2 2]);