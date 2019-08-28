//*************************************************************************************//
//обозначение файла: f_fft.c                                        
//назначение       : 
//входные данные   :                                               
//выходные данные  :                                               
//разработчик      :  Сергеева Е. И.
//*************************************************************************************//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "def_types.h"
#include "bpf.h"
#include "f_fft.h"

void rfft_256(cfloat *sig_out, float *sig_in){

	char* fname = "rfft_256";
	//printf("start function: %s\n", fname);

	float sig_in_re[256];
	float sig_in_im[256];

	int i;

	memcpy(sig_in_re, sig_in, 256*sizeof(float));

	for(i=0; i<256; i++) sig_in_im[i] = 0.0;

	bpf(256, 1, sig_in_re, sig_in_im);

	for(i=0; i<256; i++){
		sig_out[i].r = sig_in_re[i];
		sig_out[i].i = sig_in_im[i];
	}

	//printf("end function: %s\n", fname);

	return;
}
