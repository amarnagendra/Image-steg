#include<stdio.h>
#ifndef functions_h
#define functions_h
#define RASTER_OFFSET 10
#define MAX_EXT_SIZE 7				//to save extension
#define MAX_MAGIC_SIZE 20			//to save password with magic string
#define STEG "$*"				//indicator in magic string
#define DEFAULT_FNAME_ENCODING "Default.bmp"
#define MAX_FILE_NAME_SIZE 30			//buffer for default output file name while decoding
#define DEFAULT_FNAME_DECODING "default"
#define IMAGE_OFFSET 34
long int func_dec_int(FILE *ptr2);
void func_int(long int data,FILE *ptr,FILE *ptr2);
unsigned long int gen_mask_int(long int n);
typedef enum
{
    e_success,
    e_failed
} Status;

typedef enum
{
    e_encode,
    e_decode,
    e_unsupported
} OperationType;
typedef struct _EncodeInfo
{
    /* Source Image info */
    char *src_image_fname;
    FILE *fptr_src_image;
    char src_ext[MAX_EXT_SIZE];
    unsigned int image_capacity;

    /* Secret File Info */
    char *secret_fname;
    FILE *fptr_secret;
    char secret_ext[MAX_EXT_SIZE];
    int secret_size;

    /* Stego Image Info */
    char *stego_image_fname;
    FILE *fptr_stego_image;
    char stego_ext[MAX_EXT_SIZE];
    /*Magic strig*/
    char magic_string[MAX_MAGIC_SIZE];

} EncodeInfo;
typedef struct _DecodeInfo
{
    /*stego image file*/
    char *stego_image_fname;
    FILE *fptr_stego_image;

    /*output file */
    char *output_image_fname;
    FILE *fptr_output_file;
    char output_file_fname[MAX_FILE_NAME_SIZE];
    unsigned char flag_output;

    /*Magic strig*/
    char magic_string[MAX_MAGIC_SIZE];
} DecodeInfo;
Status start_decode(DecodeInfo *ptr);
Status start_encoding(EncodeInfo *ptr);
void func(unsigned char data,FILE *ptr,FILE *ptr2);
void img_capacity(EncodeInfo *ptr);
unsigned char gen_mask(int n);
long int data_size(EncodeInfo *ptr);
unsigned char func_dec(FILE* ptr2);


Status check_capacity(EncodeInfo *encInfo);
Status open_enc_files(EncodeInfo *encInfo);
Status open_dec_files(DecodeInfo *decInfo);
Status read_and_validate_encode_args(int argc,char *argv[],EncodeInfo *encinfo);
Status read_and_validate_decode_args(int argc,char *argv[],DecodeInfo *decinfo);
OperationType check_operation_type(int argc,char *argv[],EncodeInfo *encinfo,DecodeInfo *decinfo);
#endif
