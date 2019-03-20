#include "functions.h"
#include<string.h>
int main(int argc,char *argv[])
{
	OperationType type;
	Status status;
	EncodeInfo encinfo;
	DecodeInfo decinfo;
	strcpy(encinfo.magic_string,STEG);
	strcpy(decinfo.magic_string,STEG);
	if( (type=check_operation_type(argc,argv,&encinfo,&decinfo))  ==  e_encode)
	{
		status=read_and_validate_encode_args(argc,argv,&encinfo);
		if(status == e_success)
		{
			status=open_enc_files(&encinfo);
			if(status == e_success)
			{
				status=check_capacity(&encinfo);
				if(status == e_success)
				{
					if( (status=start_encoding(&encinfo)) == e_success )
					{
						printf("Encoding Successfull :) \n exiting.......\n");
						return 0;
					}
				}
				else
					return 1;
			}
			else
				return 1;
		}
		else
			return 1;
	}
	else if(type == e_decode)
	{
		status=read_and_validate_decode_args(argc,argv,&decinfo);
		if(status == e_success)
		{
			status=open_dec_files(&decinfo);
			if(status == e_success)
			{
				if( (status=start_decode(&decinfo)) == e_success )
				{
					printf("decoding Successfull :) \n exiting.....\n");
					return 0;
				}
			}
			else
				return 1;
		}
		else
			return 1;
	}
	else
		return 1;

}
