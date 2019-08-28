//******************************************************************************
// Обозначение:			def_types.c 				       
// Назначение:			
// Разработчик:     	Сергеева Е.И. 
// Дата последней корректировки: 
//******************************************************************************

#ifndef _DEF_TYPES_H_
#define _DEF_TYPES_H_

// Структура заголовка wav-файла
typedef struct WAVHEADER_tmp
{
    char chunkID[4];
    char chunkSize[4];
    char format[4];
    char subchunk1ID[4];
    char subchunk1Size[4];
    char audioFormat[2];
    char numChannels[2];   // Количество каналов  (Моно \ Стерео) 
    char sampleRate[4];     // Частота дискретизации
    char byteRate[4];       // sampleRate * numChannels * bitsPerSample/8
    char blockAlign[2];    // numChannels * bitsPerSample/8
    char bitsPerSample[2]; // точность звучания  8 бит, 16 бит и т.д.
    char subchunk2ID[4];
    char subchunk2Size[4];
}
	t_wavhdr_tmp;

// Структура заголовка wav-файла
typedef struct WAVHEADER
{
  char chunkID[4];
  //  unsigned long chunkSize;
  unsigned int chunkSize;

  char format[4];

  char subchunk1ID[4];
  // unsigned long subchunk1Size;
  unsigned int subchunk1Size;

  unsigned short audioFormat;
  
  unsigned short numChannels;   // Количество каналов  (Моно \ Стерео) 
  //  unsigned long sampleRate;     // Частота дискретизации
  unsigned int sampleRate;     // Частота дискретизации
  //  unsigned long byteRate;       // sampleRate * numChannels * bitsPerSample/8
  unsigned int byteRate;       // sampleRate * numChannels * bitsPerSample/8
  unsigned short blockAlign;    // numChannels * bitsPerSample/8
  unsigned short bitsPerSample; // точность звучания  8 бит, 16 бит и т.д.

  char subchunk2ID[4];
  //  unsigned long subchunk2Size;
  unsigned int subchunk2Size;
}
	t_wavhdr;

//------------------------------------
// Комплексное число
//------------------------------------
typedef struct 
{
	float r;
	float i;
}
  cfloat;


#endif  /* _DEF_TYPES_H_ */
