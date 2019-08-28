close all;
clear all;


fd = 24000.0;
fs = 2*880.0;

n_fft = 256;
n_times = 300
%gen samples
for n = 1:1:(n_times*n_fft);
ton_sig(n) = sin((n-1)*(2*pi*fs/fd));
end;

filename = 'ton_signal.wav';
wavwrite(ton_sig, fd, filename);