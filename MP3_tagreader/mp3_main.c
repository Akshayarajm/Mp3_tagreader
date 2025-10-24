/*
Namei		: Akshaya Raj Mullasseril
Date		: 24/10/2025
Description	: MP3 tag reader and editor
*/

#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include "header.h"
int main(int argc, char * argv[])
{
	printf("_____________________________________________________________\n");
	if (strcmp(argv[1], "-v") == 0)
	{
		char song[30];
        	strcpy(song, argv[2]);
		FILE * fp = fopen(song, "r");
		view_mp3(fp);
	}
	else if(strcmp(argv[1], "-e") == 0)
	{
		char song[30], tag[3], edits[100];
                strcpy(song, argv[4]);
		strcpy(tag, argv[2]);
		strcpy(edits, argv[3]);

		FILE * fp = fopen(song, "r");
		edit_mp3(fp, tag, edits, song);
	}
	
	else if(strcmp(argv[1], "--help") == 0)
	{
		help();

	}
	else
	{
		 printf("Incorrect option\nView\t:./a.out -v <filename>\nEdit\t:./a.out -e <-t/-a/-A/-y/-c/-m> <newcontent> <filename>\nHelp\t:--help\n");
	help();
	}
	printf("______________________________________________________________\n");
}
