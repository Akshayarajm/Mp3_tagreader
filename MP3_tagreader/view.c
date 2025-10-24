#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "header.h"

//function to convert little endien to big endien and vice versa

int convert(int size)
{
        char *ptr = (char *)&size;
        int swapped = ((unsigned char)ptr[0] << 24) | ((unsigned char)ptr[1] << 16) | ((unsigned char)ptr[2] << 8) | ((unsigned char)ptr[3]);
        return swapped;
}

//function to validate it is a mp3 file

int validate(FILE * fp)
{
	 if (fp == NULL)
	 {
		 printf("File not found.\n");
		 return 0;
	 }
	 char id3[4];
	 fread(id3, 3, 1, fp);
	 id3[3] = '\0';
	 if (strcmp(id3, "ID3") != 0)
	 {
		 printf("It is not an MP3 file.\n");
		 fclose(fp);
		 return 0;
	 }
	 return 1;
}

//function to print the tags of mp3

void view_mp3(FILE * fp)
{
        if(validate(fp)){
		printf("IDV3 Tag Reader and Viewer\n");
		fseek(fp, 10, SEEK_SET);
        	printf("____________________________________________________________\n");


        	while (!feof(fp))
        	{
               		char tag[5];
			int size;

	                if (fread(tag, 4, 1, fp) != 1)
                        break;
        	        tag[4] = '\0';

       	 	        if (tag[0] == 0)
                	        break;

                	fread(&size, 4, 1, fp);
	                size = convert(size);
	
	                fseek(fp, 2, SEEK_CUR);
	
       		        if (size <= 0)
	                break;

        	        char *content = (char *)malloc(size + 1);
                	if (!content)
                        	break;
                	fseek(fp, 1, SEEK_CUR);

                	fread(content, size - 1, 1, fp);
                	content[size - 1] = '\0';
                	if (strcmp(tag, "TIT2") == 0)
                        	printf("Title\t\t:\t%s\n", content);
                	else if (strcmp(tag, "TPE1") == 0)
                        	printf("Artist\t\t:\t%s\n", content);
                	else if (strcmp(tag, "TALB") == 0)
                        	printf("Album\t\t:\t%s\n", content);
                	else if (strcmp(tag, "TYER") == 0)
                 	      	printf("Year\t\t:\t%s\n", content);
                	else if (strcmp(tag, "TCON") == 0)
                        	printf("Genre\t\t:\t%s\n", content);
                	else if (strcmp(tag, "COMM") == 0)
                        	printf("Comment\t\t:\t%s\n", content);
			else if (strcmp(tag, "TDRC") == 0)
                                printf("Time\t\t:\t%s\n", content);
			else if (strcmp(tag, "TCOP") == 0)
                                printf("Copyright\t:\t%s\n", content);
			else if (strcmp(tag, "TPUB") == 0)
                                printf("Publisher\t:\t%s\n", content);
			else if (strcmp(tag, "TCOM") == 0)
                                printf("Composer\t\t:\t%s\n", content);
			else if (strcmp(tag, "TSSE") == 0)
                                printf("Software\t:\t%s\n", content);
			else if (strcmp(tag, "TPE2") == 0)
                                printf("Lead artist\t:\t%s\n", content);
			else if (strcmp(tag, "APIC") == 0)
                                printf("Attached image\t:\t%s\n", content);

                	free(content);
        	}


        	fclose(fp);
	}
	return;
}

//function for printing help menu

void help(void)
{
	printf("-a\t: Edit artist tag.\n");
        printf("-t\t: Edit title tag.\n");
        printf("-A\t: Edit album tag.\n");
        printf("-y\t: Edit year tag.\n");
        printf("-C\t: Edit content tag.\n");
	printf("-c\t: Edit comment tag.\n");
	printf("-Y\t: Edit time tag.\n");
	printf("-w\t: Edit copyright tag.\n");
	printf("-p\t: Edit publisher tag.\n");
	printf("-m\t: Edit comment if not 'c'.\n");
	printf("-s\t: Edit software tag.\n");
	printf("-l\t: Edit album artist tag.\n");
	printf("-i\t: Edit attached tag.\n");
}


