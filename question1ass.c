#include<stdio.h>
void createAndWriteFile(char *filename1, char *str)
{
    FILE *fp=NULL;
    fp= fopen(filename1, "w");
    if(fp!=NULL)
    {
        fprintf(fp,"%s",str);
        fclose(fp);
    }
    else
    {
        printf("error handling file");
    }

    
}

void readfile(char* filename1)
{
    FILE *fp1=NULL;
    if(fp1==NULL)
    {
        printf("error handling file");
        return;
    }
    char buffer[256];
    fp1=fopen(filename1,"r");
    while(fgets(buffer,sizeof(buffer),fp1)!=NULL)
    {
        printf("%s",buffer);
    }

    fclose(fp1);
}
void appendToFile(char* filename1, char *str1)
{
    FILE *fp2=NULL;
    fp2=fopen(filename1,"a");

    if(fp2==NULL)
    {
        printf("error handling file");
        return;
    }
    fprintf(fp2,"%s",str1);

    fclose(fp2);
}

void modifyLineInFile(char *filename3, int linenumber, char *str2)
{
    FILE *fp3=NULL;
    fp3=fopen(filename3,"r");
    
}