close all;
clear all;


fd = 6000;
%fd = 24000;

%etal
load listening_cleaned_float_C_etal.dat
norm_coeff_2 = max(listening_cleaned_float_C_etal);
listening_cleaned_float_norm = listening_cleaned_float_C_etal./norm_coeff_2;
%scale(listening_cleaned_float);
filename2 = 'signal_cleaned_C_etal.wav';
wavwrite(listening_cleaned_float_norm, fd, filename2);


