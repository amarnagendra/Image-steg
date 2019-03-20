#include "functions.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
/*Function to check which operation */

OperationType check_operation_type(int argc,char *argv[],EncodeInfo *encinfo,DecodeInfo *decinfo)
{
    if(argc>=2)
    {
        if(  !(strcmp(*(argv+1),"-e"))  || !(strcmp(*(argv+1),"-pe")))
        {
            if(!(strcmp(*(argv+1),"-pe")))
            {
                printf("Enter your password to be encoded in magic string\n");
                scanf("%s",(char *)encinfo->magic_string + strlen(STEG));
                printf("INFO:The magic string is %s\n",encinfo->magic_string);
            }
            return e_encode;
            //read_and_validate_encode_args(argc,argv,encinfo);
        }
        else if(  !(strcmp(*(argv+1),"-d"))  || !(strcmp(*(argv+1),"-pd")))
        {
            if(!(strcmp(*(argv+1),"-pd")))
            {
                printf("enter your password\n");
                scanf("%s",(char *)decinfo->magic_string + strlen(STEG));
                printf("INFO:The magic string is %s\n",decinfo->magic_string);
            }
            return e_decode;
            //read_and_validate_decode_args(argc,argv,decinfo);
        }
        else
        {
            printf("ERROR:you enterted Unsupported flag\n");
            return e_unsupported;
        }
    }
    else
    {
        printf("command should be of type\n");
        printf("1) ./a.out -e <image.bmp> <secret.txt> <output.bmp>\n");
        printf("2) ./a.out -d <image.bmp> <outputfile>\n");
        printf("NOTE:use -pe or -pd flag to steg or decode with password\n");
        return e_unsupported;
    }

}


/*function to validate encode arguments*/
Status read_and_validate_encode_args(int argc,char *argv[],EncodeInfo *encinfo)
{
    encinfo->src_image_fname=*(argv+2);
    encinfo->secret_fname=*(argv+3);
    if(argc<4)
    {
        printf("command should be of type\n");
        printf("1) ./a.out -e <image.bmp> <secret.txt> <output.bmp>\n");
        printf("2) ./a.out -d <image.bmp> <outputfile>\n");
        printf("NOTE:use -pe or -pd flag to steg or decode with password\n");
        return e_failed;
    }
    if(argc==5)
        encinfo->stego_image_fname=*(argv+4);
    else
        encinfo->stego_image_fname=DEFAULT_FNAME_ENCODING;
    if(strstr(*(argv+2),".bmp")==NULL)
    {
        printf("ERROR:Provide bmp image only!!!\n");
        return e_failed;
    }
    else
    {
        printf("INFO:Extension OK!!!\n");
        //open_enc_files(encinfo);
        return e_success;
    }

}
/*function to validate decode arguments*/
Status read_and_validate_decode_args(int argc,char *argv[],DecodeInfo *decinfo)
{

    if(argc<3)
    {
        printf("command should be of type\n");
        printf("1) ./a.out -e <image.bmp> <secret.txt> <output.bmp>\n");
        printf("2) ./a.out -d <image.bmp> <outputfile>\n");
        printf("NOTE:use -pe or -pd flag to steg or decode with password\n");
        return e_failed;
    }
    decinfo->stego_image_fname=*(argv+2);
    if(argc==4)
    {
        decinfo->output_image_fname=*(argv+3);
        decinfo->flag_output=1;
    }
    else
    {
        printf("INFO:no out put file mentioned... ouput will be in default file\n");
        strcpy(decinfo->output_file_fname,DEFAULT_FNAME_DECODING);
        decinfo->flag_output=0;
    }

    if(strstr(*(argv+2),".bmp")==NULL)
    {
        printf("ERROR:Provide bmp image only!!!\n");
        return e_failed;
    }
    else
    {
        printf("INFO:Extension OK!!!\n");
        //open_dec_files(decinfo);
        return e_success;
    }
}
/*function to open enc files*/
Status open_enc_files(EncodeInfo *encinfo)
{
    printf("INFO:opening required files\n");
    if((encinfo->fptr_src_image=fopen(encinfo->src_image_fname,"r")))
    {
        printf("INFO:src image opened successfully\n");
        if((encinfo->fptr_secret=fopen(encinfo->secret_fname,"r")))
        {
            printf("INFO:secret image opened successfully\n");
            if((encinfo->fptr_stego_image=fopen(encinfo->stego_image_fname,"w+")))
            {
                printf("INFO:stego image opened successfully\n");
                //check_capacity(encinfo);
                return e_success;
            }
            else
            {
                printf("ERROR:opening stego image failed\n");
                return e_failed;
            }
        }
        else
        {
            printf("ERROR:opening secret image failed\n");
            return e_failed;
        }
    }
    else
    {
        printf("ERROR:opening source image failed\n");
        return e_failed;
    }
}
/*function to open decode files*/
Status open_dec_files(DecodeInfo *decinfo)
{
    printf("INFO:opening required files\n");
    if((decinfo->fptr_stego_image=fopen(decinfo->stego_image_fname,"r")))
    {
        printf("INFO:stego image opened successfully\n");
        if(decinfo->flag_output==1)
        {
            if((decinfo->fptr_output_file=fopen(decinfo->output_image_fname,"w+")))
            {
                printf("INFO:output file opened succesfully\n");
                //printf("decoding started\n");
                //start_decode(decinfo);
                //printf("decoding finished :)\n");

                return e_success;
            }
            else
            {
                printf("ERROR:opening output file failed\n");
                return e_failed;
            }
        }
        else
        {
            //printf("decoding started\n");
            //start_decode(decinfo);
            //printf("decoding finished :)\n");
            return e_success;
        }
    }
    else
    {
        printf("ERROR:opening stego image failed\n");
        return e_failed;
    }
}
/*function to check whether file can hold data*/
Status check_capacity(EncodeInfo *encinfo)
{
    //save extension in structure
    int i;
    for(i=0; *(encinfo->secret_fname+i); i++)
    {
        if(*(encinfo->secret_fname+i) == '.')
            break;
    }
    int k;
    for(k=0; *(encinfo->secret_fname+i); k++)
    {
        encinfo->secret_ext[k]=*(encinfo->secret_fname+i);
        i++;
    }
    encinfo->secret_ext[k]='\0';
    printf("INFO:secret_ext is %s\n",encinfo->secret_ext);

    //check for capacity

    img_capacity(encinfo);
    long int image_capacity=encinfo->image_capacity;

    long int total_size = data_size(encinfo);
    printf("INFO:Total Data size : %ld\n",total_size);
    if(image_capacity<total_size)
    {
        printf("ERROR:Image cannot handle data\n");
        return e_failed;
    }
    else
    {
        //printf("Started encoding process\n");
        //start_encoding(encinfo);
        //printf("Done encoding\n");
        return e_success;
    }
}
long int data_size(EncodeInfo *ptr)
{
    fseek(ptr->fptr_secret,0,SEEK_SET);
    int text_size=0;
    char c;
    while((c=fgetc(ptr->fptr_secret))!=EOF)
    {
        text_size++;
    }
    ptr->secret_size=text_size;
    printf("INFO:secret size in bytes: %d\n",ptr->secret_size);
    int ext_size=strlen(ptr->secret_ext);

    //printf("Secret file size %d\n",(4+4+4+text_size+ext_size+strlen(ptr->magic_string)*8));
    return (sizeof(long)+sizeof(long)+sizeof(long)+text_size+ext_size+strlen(ptr->magic_string))*8;
}
void img_capacity(EncodeInfo *ptr)
{
    fseek(ptr->fptr_src_image,IMAGE_OFFSET,SEEK_SET);
    fread(&(ptr->image_capacity),sizeof(int),1,ptr->fptr_src_image);
    printf("INFO:capacity of src_image:%d\n",ptr->image_capacity);

}

/*function to copy header*/
Status copy_header(EncodeInfo *ptr)
{
    unsigned char c;
    int raster_offset;
    fseek(ptr->fptr_src_image,RASTER_OFFSET,SEEK_SET);//get offset by pointing to raster
    fread(&raster_offset,sizeof(int),1,ptr->fptr_src_image);
    /*	if(ferror(ptr->fptr_src_image))
    	{
    		clearerr(ptr->fptr_src_image)
    		return e_failed;
    	}*/
    //printf("offset is : %x %d\n",raster_offset,raster_offset);

    printf("INFO:copying Header File\n");
    fseek(ptr->fptr_src_image,0,SEEK_SET);			//set source to zero
    char *ptr_54=malloc(raster_offset);
    //for(int i=0; i<raster_offset; i++) 			//copy the header file
    //{
        fread(ptr_54,raster_offset,1,ptr->fptr_src_image);
        fwrite(ptr_54,raster_offset,1,ptr->fptr_stego_image);
    //}
    return e_success;
}
/*function to encode magic string*/
Status encode_magic_string(EncodeInfo *ptr)
{
    func_int(strlen(ptr->magic_string),ptr->fptr_src_image,ptr->fptr_stego_image);  //encode length of magic string
    printf("INFO:encoding magic string \n");
    for(int i=0; i<strlen(ptr->magic_string); i++)
    {

        func(ptr->magic_string[i],ptr->fptr_src_image,ptr->fptr_stego_image);	//encode star
    }
    return e_success;
}
/*function to encode extension*/
Status encode_extension(EncodeInfo *ptr)
{
    //encode size of extension ex: .txt  = 4
    func_int(strlen(ptr->secret_ext),ptr->fptr_src_image,ptr->fptr_stego_image);
    //encode extension ex: .txt
    printf("INFO:encoding extension \n");
    for(int i=0; i<strlen(ptr->secret_ext); i++)
    {
        func(ptr->secret_ext[i],ptr->fptr_src_image,ptr->fptr_stego_image);

    }
    return e_success;
}
/*function to encode secret text*/
Status encode_secret_text(EncodeInfo *ptr)
{
    unsigned char c;
    //encode text size ex: abcd =  4
    func_int(ptr->secret_size,ptr->fptr_src_image,ptr->fptr_stego_image);
    //encode text in secret file
    printf("INFO:encoding secret information \n");
    for(int i=0; i<ptr->secret_size; i++)
    {
        fread(&c,1,1,ptr->fptr_secret);
        func(c,ptr->fptr_src_image,ptr->fptr_stego_image);
    }
    return e_success;
}

/*main function which starts encoding*/
Status start_encoding(EncodeInfo *ptr)
{
    unsigned char c1;
    Status status;
    fseek(ptr->fptr_src_image,0,SEEK_SET);		//set source to 0
    fseek(ptr->fptr_secret,0,SEEK_SET);		//set secret to 0
    fseek(ptr->fptr_stego_image,0,SEEK_SET);	//set steg to 0

    if( (status=copy_header(ptr))  ==  e_success )
    {
        if( (status=encode_magic_string(ptr)) == e_success )
        {
            if( (status=encode_extension(ptr)) == e_success )
            {
                if( (status=encode_secret_text(ptr)) == e_success )
                {
                    printf("INFO:Copying remaining bytes after encoding\n");

                    for(;;)
                    {
                        if(feof(ptr->fptr_src_image))
                            break;

                        fread(&c1,1,1,ptr->fptr_src_image);
                        fwrite(&c1,1,1,ptr->fptr_stego_image);
                    }
                    return e_success;
                }
                else
                {
                    return e_failed;
                }
            }
            else
            {
                return e_failed;
            }
        }
        else
        {
            return e_failed;
        }
    }
    else
    {
        return e_failed;
    }
}

/*function to decode magic string*/
Status decode_magic_string(DecodeInfo *ptr)
{
    unsigned long int magic_size=func_dec_int(ptr->fptr_stego_image);
    unsigned char c;
    //decoding magic
    if(magic_size==strlen(ptr->magic_string))
    {
        for(int i=0; i<magic_size; i++)
        {
            c=func_dec(ptr->fptr_stego_image);
            if(c!=ptr->magic_string[i])
            {
                printf("ERROR:image is not stegged or password wrong :( \n");
                return e_failed;
            }

            //printf("%c",c);
        }
    }
    else
    {
        printf("ERROR:image is not stegged or password wrong :( \n");
        return e_failed;
    }
    return e_success;
}

/*function to decode extension */
Status decode_extension(DecodeInfo *ptr)
{
    //decrypt ext size
    unsigned long int  ext_size=func_dec_int(ptr->fptr_stego_image);
    unsigned char c;
    //printf("ext_size : %x %d\n",ext_size,ext_size);
    //decode extension
    int i;
    for(i=0; i<ext_size; i++)
    {
        c=func_dec(ptr->fptr_stego_image);
        //printf("%c",c);
        ptr->output_file_fname[strlen(DEFAULT_FNAME_DECODING)+i]=c;
    }
    ptr->output_file_fname[strlen(DEFAULT_FNAME_DECODING)+i]='\0';
    //printf("\n");
    return e_success;
}
/*function to decode secret text*/
Status decode_secret_text(DecodeInfo *ptr)
{
    if(ptr->flag_output==0)
    {
        printf("INFO:opening default file in name %s\n",ptr->output_file_fname);
        if((ptr->fptr_output_file=fopen(ptr->output_file_fname,"w+")))
        {
            printf("INFO:opening default file successfull\n");
        }
        else
        {
            printf("ERROR:opening default file failed\n");
            return e_failed ;
        }
    }
    //decode text size
    unsigned long int secret_size=func_dec_int(ptr->fptr_stego_image);
    //printf("secret_size : %x %d\n",secret_size,secret_size);

    //decode secret text
    for(int i=0; i<secret_size; i++)
    {
        unsigned char c=func_dec(ptr->fptr_stego_image);
        if(ptr->flag_output==0)
        {
            fwrite(&c,1,1,ptr->fptr_output_file);
            //printf("%c",c);
        }
        else
            fwrite(&c,1,1,ptr->fptr_output_file);
    }
    return e_success;
}
/*main function which starts decoding*/
Status start_decode(DecodeInfo *ptr)
{
    Status status;
    //fseek(ptr->fptr_src_image,0,SEEK_SET);
    //fseek(ptr->fptr_secret,0,SEEK_SET);
    fseek(ptr->fptr_stego_image,0,SEEK_SET); //point to zero at start
    // get raster offset and point to it
    int raster_offset;
    fseek(ptr->fptr_stego_image,RASTER_OFFSET,SEEK_SET);//get offset
    fread(&raster_offset,sizeof(int),1,ptr->fptr_stego_image);
    //poin to raster offset
    //	printf("offset is : %x %d\n",raster_offset,raster_offset);
    fseek(ptr->fptr_stego_image,raster_offset,SEEK_SET);//set to raster offset

    if( (status=decode_magic_string(ptr)) == e_success )
    {
        if( (status=decode_extension(ptr)) == e_success )
        {
            if( (status=decode_secret_text(ptr)) == e_success)
            {
                return e_success;
            }
            else
                return e_failed;
        }
        else
            return e_failed;
    }
    else
        return e_failed;
}




/* real function which encodes char */
void func(unsigned char data,FILE *ptr,FILE* ptr2)
{
    unsigned char byte;
    unsigned char mask =0x01;
    for(int i=0; i<=7; i++)
    {
        fread(&byte,1,1,ptr);
        //printf("original byte %hhx\n ",byte);
        if(data & (mask))
        {
            byte=byte | 0x01;
            //printf("after %hhx\n",(byte | 0x01));
            fwrite(&byte,1,1,ptr2);

        }
        else
        {
            byte=byte & 0xfe;
            //printf("after %hhx\n ",(byte & 0xfe));
            fwrite(&byte,1,1,ptr2);
        }
        mask=mask<<1;
    }
}
/* real function which decodes char*/
unsigned char func_dec(FILE* ptr2)
{
    unsigned char data;
    unsigned char byte;
    for(int i=0; i<=7; i++)
    {
        fread(&byte,1,1,ptr2);
        if(byte & 0x01)
        {
            data=(data | gen_mask(i));
        }
        else
        {
            data=(data & (0xFF - gen_mask(i)));
        }
    }
    return data;
}
/* real function to generate mask for char*/
unsigned char gen_mask(int n)
{
    unsigned char res=1;
    for(int i=0; i<n; i++)
    {
        res=res*2;
    }
    //	printf("%d \n ",res);
    return res;
}
/*real function which encodes int*/
void func_int(long int data,FILE *ptr,FILE* ptr2)
{
    unsigned char byte;
    unsigned long int mask =0x0000000000000001;
    for(int i=0; i<(sizeof(long)*8); i++)
    {
        fread(&byte,1,1,ptr);
        //printf("original byte %hhx\n ",byte);
        if(data & (mask))
        {
            byte=byte | 0x01;
            //printf("after %hhx\n",(byte | 0x01));
            fwrite(&byte,1,1,ptr2);

        }
        else
        {
            byte=byte & 0xfe;
            //printf("after %hhx\n ",(byte & 0xfe));
            fwrite(&byte,1,1,ptr2);
        }
        mask=mask<<1;
    }
}
/*real function which decodes int*/
long int func_dec_int(FILE* ptr2)
{
    long int data;
    unsigned char byte;
    for(int i=0; i<(sizeof(long)*8); i++)
    {
        fread(&byte,1,1,ptr2);
        if(byte & 0x01)
        {
            data=(data | gen_mask_int(i));
        }
        else
        {
            data=(data & (0xFFFFFFFFFFFFFFFF - gen_mask_int(i)));
        }
    }
    return data;
}
unsigned long int gen_mask_int(long int n)
{
    long int res=1;
    for(int i=0; i<n; i++)
    {
        res=res*2;
    }
    //	printf("%d \n ",res);
    return res;
}

