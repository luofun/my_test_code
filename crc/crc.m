clear;
clc;
data=randi(2,1,16)-1; %随机16位0，1数据
g=[1 0 0 1 1];%生成多项式g(x)=x4+x+1，crc-4这个最简单会产生4位冗余码
R=length(g)-1; %冗余码长为生成多项式长度减1
[q,r] = deconv([data zeros(1,R)],g);
%为数据右边补K个0，然后用deconv计算数据多项式除以生成多项式
%商是q(长度16），余数是r（长度16+R)
r=mod(r(end-R+1:end),2);%取余数的最后R位mod2
code=[data r]; %编码是原来的16位数据后加上R位校验冗余码
%发送的信号就是这16+R位二进制编码
 
 
%验证：将接收到的16+R位编码和生成多项式相除
[q,r] = deconv(code,g); 
r=mod(r(end-R+1:end),2);%取余数的最后R位mod2
disp(r)    %如果正确，R位余数全是0
 
errorcode=code;
errorcode(2)=1-errorcode(2); %假设第二位错了
[q,r] = deconv(errorcode,g);
r=mod(r(end-R+1:end),2);
disp(r)    %R位余数全为0
data
code