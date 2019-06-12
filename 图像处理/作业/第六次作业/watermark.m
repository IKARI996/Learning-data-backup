alpha = 1;
% ��ȡͼƬ
image = double(imread('test.jpg')) / 255;
water_mark = double(imread('mark.jpg')) / 255;

% ����ˮӡ
image_size = size(image);
tsymmetric = zeros(image_size(1) * 0.5, image_size(2), image_size(3));
tsymmetric1 = tsymmetric;
tsymmetric1(1:size(water_mark, 1), 1:size(water_mark, 2), :) = water_mark;
% ����������б���
m = randperm(0.5 * image_size(1));
n = randperm(image_size(2));
for i = 1:image_size(1) * 0.5
    for j = 1:image_size(2)
        tsymmetric(i, j, :) = tsymmetric1(m(i), n(j), :);
    end
end
encoded_mark = zeros(image_size(1), image_size(2), image_size(3));
encoded_mark(1:image_size(1) * 0.5, 1:image_size(2), :) = tsymmetric;
for i = 1:image_size(1) * 0.5
    for j = 1:image_size(2)
        encoded_mark(image_size(1) + 1 - i, image_size(2) + 1 - j, :) = tsymmetric(i, j, :);
    end
end

% ��������ˮӡ����ͼƬ
fimage = fft2(image);
fwater_image = fimage + alpha * double(encoded_mark);
output = ifft2(fwater_image);

% ��ͼ����ȡ��ˮӡ
fout = fft2(output);
gwatermark = (fout - fimage) / alpha;
out_water_mark = gwatermark;
for i = 1:image_size(1) * 0.5
    for j = 1:image_size(2)
        out_water_mark(m(i), n(j), :) = gwatermark(i, j, :);
    end
end
for i = 1:image_size(1) * 0.5
    for j = 1:image_size(2)
        out_water_mark(image_size(1) + 1 - i, image_size(2) + 1 - j, :) = out_water_mark(i, j, :);
    end
end

% ����ͼ��
subplot(221); imshow(image); title('ԭͼ');
subplot(222); imshow(water_mark); title('ˮӡ');
subplot(223); imshow(output); title('����ˮӡ��ͼ��');
subplot(224); imshow(out_water_mark); title('��ȡ����ˮӡ');