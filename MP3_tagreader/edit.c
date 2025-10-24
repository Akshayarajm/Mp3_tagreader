#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "header.h"

//function to choose the tag to be edited

void edit_mp3(FILE * fp, char * tags, char * edits, char * song)
{
        if(validate(fp))
	{
		FILE * fp1 = fopen("temp.mp3", "w");
		if(!fp1)
		{
			printf("Error creating temperory file\n");
			fclose(fp);
			return;
		}
		char *arr[13] = {"TIT2","TPE1","TALB","TYER","TCON","COMM", "TDRC", "TCOP", "TPUB", "TCOM", "TSSE", "TPE2", "APIC"};
		
//checking for the tag
		
		
		switch(tags[1])
		{
			case 't':
				edit(fp, fp1, arr[0], edits, song);
			        break;
			case 'a':
                                edit(fp, fp1, arr[1], edits, song);
                                break;
			case 'A':
                                edit(fp, fp1, arr[2], edits, song);
                                break;
			case 'y':
                                edit(fp, fp1, arr[3], edits, song);
                                break;
			case 'C':
                                edit(fp, fp1, arr[4], edits, song);
                                break;
			case 'c':
                                edit(fp, fp1, arr[5], edits, song);
                                break;
			case 'Y':
                                edit(fp, fp1, arr[6], edits, song);
                                break;
			case 'w':
                                edit(fp, fp1, arr[7], edits, song);
                                break;
			case 'p':
                                edit(fp, fp1, arr[8], edits, song);
                                break;
			case 'm':
                                edit(fp, fp1, arr[9], edits, song);
                                break;
			case 's':
                                edit(fp, fp1, arr[10], edits, song);
                                break;
			case 'l':
                                edit(fp, fp1, arr[11], edits, song);
                                break;
			case 'i':
                                edit(fp, fp1, arr[12], edits, song);
                                break;
			default:
                                help();
		}
	}
}

//function to edit tag


void edit(FILE * fp, FILE * fp1, char * arr, char * edits, char *song)
{
	int flag = 0;
	rewind(fp);
	char header[10];
	fread(header, 10, 1, fp);
	fwrite(header, 10, 1, fp1);

//writing the header to temp file

	while(!feof(fp))
	{
		char tag[5];
		int size;
		unsigned char flags[2];
		if (fread(tag, 4, 1, fp) != 1)
			break;
		tag[4] = '\0';
		if (tag[0] == 0)
			break;
		if(fread(&size, 4, 1, fp) != 1)
			break;
		size = convert(size);
		fread(flags,2,1,fp);

 //checking for the tag to be edited

		if(strcmp(tag, arr) == 0)
		{
			flag = 1;
			int new_size = strlen(edits) + 1;
			int converted = convert(new_size);

//copying the tag to temp

			fwrite(tag , 4, 1, fp1);
			fwrite(&converted, 4, 1, fp1);
			fwrite(flags, 3, 1, fp1);
			fwrite(edits, new_size - 1, 1, fp1);
			fseek(fp, size,SEEK_CUR);
			char ch;

//writing balance characters to temp

			while((fread(&ch, 1, 1, fp) == 1))
				fwrite(&ch, 1, 1, fp1);
			break;
		}

//if tag is not found content is copied to temp

		else							
		{
			char *content = (char *)malloc(size);
            		fread(content, size, 1, fp);

            		fwrite(tag, 4, 1, fp1);
			int nsize = convert(size);
            		fwrite(&nsize, 4, 1, fp1);
            		fwrite(flags, 2, 1, fp1);
            		fwrite(content, size, 1, fp1);

            		free(content);
		}
	}
	if(flag)
		printf("Edited successfully\n");
	fclose(fp);
	fclose(fp1);	
	remove(song);
	rename("temp.mp3", song);

}
