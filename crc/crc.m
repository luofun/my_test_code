clear;
clc;
data=randi(2,1,16)-1; %���16λ0��1����
g=[1 0 0 1 1];%���ɶ���ʽg(x)=x4+x+1��crc-4�����򵥻����4λ������
R=length(g)-1; %�����볤Ϊ���ɶ���ʽ���ȼ�1
[q,r] = deconv([data zeros(1,R)],g);
%Ϊ�����ұ߲�K��0��Ȼ����deconv�������ݶ���ʽ�������ɶ���ʽ
%����q(����16����������r������16+R)
r=mod(r(end-R+1:end),2);%ȡ���������Rλmod2
code=[data r]; %������ԭ����16λ���ݺ����RλУ��������
%���͵��źž�����16+Rλ�����Ʊ���
 
 
%��֤�������յ���16+Rλ��������ɶ���ʽ���
[q,r] = deconv(code,g); 
r=mod(r(end-R+1:end),2);%ȡ���������Rλmod2
disp(r)    %�����ȷ��Rλ����ȫ��0
 
errorcode=code;
errorcode(2)=1-errorcode(2); %����ڶ�λ����
[q,r] = deconv(errorcode,g);
r=mod(r(end-R+1:end),2);
disp(r)    %Rλ����ȫΪ0
data
code