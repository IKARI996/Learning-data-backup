close all;
clear all;
img = imread('lena.tif');

count = 0;
while (true)
    count = count + 1;
    g = fft2(img);
    g = fftshift(g);
    result = g

%     imshow(abs(g),[])
    [N1,N2] = size(g);
    n = 2;
    d0 = 30; 

    n1 = fix(N1/2);
    n2 = fix(N2/2);

    for i = 1:N1
      for j = 1:N2
          d = sqrt((i - n1)^2 + (j - n2)^2);
          h = 1 - exp(- d * d / (2 * d0 * d0));
          result(i,j) = h * result(i,j);
      end
    end
    result = ifftshift(result);
    img2 = ifft2(res);
    img2 = uint8(real(img2));
    
    imshow(img2);
    fprintf('%d \n', count);
    if isequal(img2, img)
         break;
    else
        old = result;
    end
    img = img2;
%     if mod(count, 200) == 0   
%         % fft��һά����Ҷ�任������ʱ���ź�ת��ΪƵ���ź�
%         % fftshift�����Ƶ��ģ���FFT��DC�����Ƶ�Ƶ������
%         % ����Ƶ���ͼ�񣬣�������һ��ˮƽ�ߺ�һ����ֱ�߽�Ƶ��ͼ�ֳ��Ŀ飩�����Ŀ���жԽ��ߵĽ����뷴�Խ��ߵĽ���
%         % ifft means the inverse of fft.
%         % get the initial result of image.
%         result = ifftshift(result);
%         X2=ifft2(result);
%         final=uint8(real(X2));
%         imshow(final);
%     end
end