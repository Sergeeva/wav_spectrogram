close all
clear all

load A_out.dat

fd = 24000.0;
nFFT = 256;

fScale = ((fd/nFFT)*linspace(0, 127, 128));
yScale = linspace(1, 1204, 1204);

figure;

imagesc(fScale, yScale,  A_out);
axis xy;
axis image;



