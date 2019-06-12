A = imread('D:\Documents\Pictures\Matlab.jpg');
%---------------�Ҷ�ת��---------------
B = rgb2gray(A);
subplot(1,2,1),subimage(A);
title('ԭͼ��');
subplot(1,2,2),subimage(B);
title('�Ҷ�ת��');
figure;
%---------------ͼ��ƽ��---------------
se = translate(strel(1), [50 50]);
B = imdilate(A, se);
subplot(1,2,1),subimage(A);
title('ԭͼ��');
subplot(1,2,2),subimage(B);
title('ͼ��ƽ��')
figure;
%---------------ͼ��ת��---------------
subplot(1,2,1),subimage(A);
title('ԭͼ��');
Ir = A(:,:,1);
Ig = A(:,:,2);
Ib = A(:,:,3);
[m,n] = size(Ir);
Gr = zeros(m,n);
Gg = zeros(m,n);
Gb = zeros(m,n);
for i = 1 : m
    for j = 1 : n
        Gr(j,i) = Ir(i,j);
        Gg(j,i) = Ig(i,j);
        Gb(j,i) = Ib(i,j);
    end
end
Gr1 = cast(Gr, 'double');
Gg1 = cast(Gg, 'double');
Gb1 = cast(Gb, 'double');
g = cat(3,Gr1,Gg1,Gb1);
subplot(1,2,2),subimage(uint8(g));
title('ͼ��ת��')
figure;
%---------------ͼ������---------------
B = imresize(A,0.5);
subimage(A);
title('ԭͼ��');
figure,subimage(B);
title('ͼ������')
figure;
%---------------ͼ����ת---------------
B= imrotate(A, 30, 'crop');
subplot(1,2,1),subimage(A);
title('ԭͼ��');
subplot(1,2,2),subimage(B);
title('��ת');
