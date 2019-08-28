//******************************************************************************
// Обозначение:			main.c 				       
// Назначение:			
// Разработчик:     	Сергеева Е.И.
// Дата последней корректировки: 
//******************************************************************************

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

#include "def_types.h"

//#include "f_fft.h"
#include "bpf.h"

#define N_FFT 256

/*
Функция обработки порции данных:

- БПФ --- пока что возьмем "обертку" для ф-ии bpf из файла bpf.h
          NB можно заменить на ф-ии из FFTW или другие спец. библиотеки     
- вычисление кв. модулей

Вход:
    float s_in[N_FFT] --- порция входного сигнала 
Выход:
    float A_out[N_FFT/2] --- квадраты модулей спектров
 */
void f_processing(float *s_in, float *A_out){

  //	cfloat fft_out[N_FFT];
  //	memset((float*) fft_out, 0.0, 2*N_FFT*sizeof(float));
  //	
  //	rfft_256(fft_out, s_in);

  
	float sig_in_re[N_FFT];
	float sig_in_im[N_FFT];

	int i;

	memcpy(sig_in_re, s_in, N_FFT*sizeof(float));
	memset(sig_in_im, 0.0, N_FFT*sizeof(float));


	bpf(256, 1, sig_in_re, sig_in_im);

	//	for(int i = 0; i<N_FFT/2; i++){
	//	A_out[i] = fft_out[i].r*fft_out[i].r + fft_out[i].i*fft_out[i].i;
	//}

	for(int i = 0; i<N_FFT/2; i++){
		A_out[i] = sig_in_re[i]*sig_in_re[i] + sig_in_im[i]*sig_in_im[i];
	}

	return;
}

/*
Путь к wav-файлу можно задать из командной строки,
по умолчанию открывается data/ton_signal.wav --- сгенерирован в Матлабе (см. параметры для проверки)
 */
int main(int argc, char** argv) {

	char* fin_name = "data/ton_signal.wav";;
	if(argc > 1){
		fin_name = argv[1];
	}

	FILE* f_in = fopen(fin_name, "rb");
	if(f_in == NULL){
	  printf("ERROR in OPEN FILE [%s] \n", fin_name);
	  return 1;
	} else {
	  printf("OPEN FILE [%s] is OK \n", fin_name);
	}

//читаем заголовок
	t_wavhdr header;		

	size_t readed = fread(&header, sizeof(header), 1, f_in);

//печатаем параметры wav-файла
	printf("***** Parametrs of WAV-file [%s] *****\n", fin_name);
	
	printf("chunkID =  %s\n", header.chunkID);
	printf("chunkSize =  %i\n", header.chunkSize);
	printf("format =  %s\n", header.format);
	printf("subchunk1ID =  %s\n", header.subchunk1ID);
	printf("subchunk1Size =  %i\n", header.subchunk1Size);
	printf("audioFormat =  %i\n", header.audioFormat);
	printf("numChannels = %i\n", header.numChannels);
	printf("sampleRate =  %i\n", header.sampleRate);
	printf("blockAlign = %i\n", header.blockAlign);
	printf("bitsPerSample = %i\n", header.bitsPerSample);
	
	printf("subchunk2ID =  %s\n", header.subchunk2ID);
	printf("subchunk2Size =  %i\n", header.subchunk2Size);
	
	printf("*********************************************************\n");

	//всего отсчетов в файле	
	int N_samples = header.subchunk2Size * 8 / header.bitsPerSample;
	int sample_size = header.bitsPerSample/8; //[BYTES]
	printf("Samples count = %i\n", N_samples);

//всего циклов БПФ (порций обработки)
	int N_portions = N_samples / N_FFT; //целых
//+ хвостик
	int tail = N_samples - N_FFT*N_portions; 
	printf("N_portions for FFT = %i\n", N_portions);
	printf("tail = %i\n", tail);


	short s_in[N_FFT];//short --- в предположении, что sample_size = 2 байта и канал 1
	memset(s_in, 0, N_FFT*sizeof(int));
	
	float fs_in[N_FFT];
	memset(fs_in, 0.0, N_FFT*sizeof(float));
	float A_out[N_FFT/2];
	memset(A_out, 0.0, (N_FFT/2)*sizeof(float));

// Пока что результат в файл будем записывать
	FILE* f_out = fopen("data/A_out.dat", "w");
	if(f_out == NULL){
		printf("ERROR in OPEN FILE [A_out.dat] \n");
	}else{
		printf("CREATING FILE [A_out.dat] is OK \n");
	}

//Обработка по всем целым порциям
	for(int j = 0; j < N_portions; j++){
	//Читаем сами данные из файла порциями по N_FFT
		for (int i = 0; i < N_FFT; i++){
			fread(&s_in[i], sample_size, 1, f_in);
//"распаковка" каждого отсчета
			fs_in[i] = (float)s_in[i];
		}

//Обработка новой порции данных
		f_processing(fs_in, A_out);

//Пока что запишем результат в файл
		for (int i = 0; i < N_FFT/2; i++){
			fprintf(f_out, "%f\t", A_out[i]);
		} fprintf(f_out, "\n");
			
	}
	
//Обработка "хвостика"
	//Читаем сами данные из файла
//	for (int i = 0; i < N_FFT; i++){
//		fread(&s_in[i], sample_size, 1, f_in);
//"распаковка" каждого отсчета
		//cs_in[i].r = (float)s_in[i];
		//cs_in[i].i = 0.0;
		//printf("[%i]%i\t(%f, %f)\n", i, s_in[i], cs_in[i].r, cs_in[i].i);
//	}
//		f_processing();
	
//Пока что запишем результат в файл

///////////////////////////////////////
// wav файл прочитан
	fclose(f_in);
	printf("FILE [%s] is READED \n", fin_name);
///////////////////////////////////////
//результат тоже записан
	fclose(f_out);
	printf("FILE [A_out.dat] is WRITED \n");

  return 0;
}
