% ����ͼ��
A=imread('D:\Documents\Pictures\Matlab.jpg');
% �Ҷ�ת��
B = rgb2gray(A);
subplot(1,2,1),subimage(A);
title('ԭͼ��');
subplot(1,2,2),subimage(B);
title('�Ҷ�ת��')
figure;
%ͼ��ƽ��
tran = translate(strel(1), [100 100]);  
B = imdilate(A,tran); 
subplot(1,2,1),subimage(A);
title('ԭͼ��');
subplot(1,2,2),subimage(B);
title('ͼ��ƽ��')
figure;
%ͼ��ת��
B(:,:,1) = A(:,:,1)';
B(:,:,2) = A(:,:,2)';
B(:,:,3) = A(:,:,3)';
subplot(1,2,1),subimage(A);
title('ԭͼ��');
subplot(1,2,2),subimage(B);
title('ͼ��ת��')
figure;
%ͼ������
B=imresize(A,0.5);
subimage(A);
title('ԭͼ��');
figure, subimage(B);
title('����')
figure;
B= imrotate(A, 30, 'crop');
subplot(1,2,1),subimage(A);
title('ԭͼ��');
subplot(1,2,2),subimage(B);
title('��ת');
