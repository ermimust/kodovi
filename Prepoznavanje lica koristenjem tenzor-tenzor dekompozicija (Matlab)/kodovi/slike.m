clc;
clear;

% Ispis nekoliko slika

indeksi = randi(165,5,1);
indeksi = sort([indeksi;indeksi+1])

load('Yale_64x64.mat');
figure;
for i = 1:8
    subplot(1,8,i);
    imshow(reshape(fea(indeksi(i),:),64,64),[0,255]);
end
truesize([300,200])
figure;
load('Yale_32x32.mat');
for i = 1:8
    subplot(1,8,i);
    imshow(reshape(fea(indeksi(i),:),32,32),[0,255]);
end
truesize([300,200])