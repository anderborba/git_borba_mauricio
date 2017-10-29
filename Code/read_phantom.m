%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% To load a .txt file in Matlab (with the above saved format) and write it
% to matrix V.:
clear all;
fid=fopen('Phantom_0.500_4_1_1.txt','r');
M=fscanf(fid,'%d',1);
N=fscanf(fid,'%d',1);
for i=1:M
  for j=1:N
  tmp=fscanf(fid,'%f',1);
  V(i,j)=tmp;
  end
 end
 fscanf(fid,'\n');
status=fclose(fid);
%V=mat2gray(V);
%Va=imadjust(V);
%escala1=mean2(V);
imshow(V);