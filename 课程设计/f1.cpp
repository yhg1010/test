#include <stdio.h>
#include <stdlib.h>

int main()
{
	FILE *fp;
	fp=fopen("d:\\Dev\\�γ����\\f1.txt","w");
	fprintf(fp,"%s","i am a student!");
	fclose(fp);
	return 0;	
} 
