#include<stdio.h>
#include<stdlib.h>
#include <windows.h>
#include <time.h>
#include<string.h>
#include <mmsystem.h>
#include<io.h> //findfirst��ͷ�ļ�
#pragma comment(lib, "WINMM.LIB")  //#pragma ��һ��������ָ�� ����winmm.lib��
//�궨��
#define SINGLE_LOOP					1					// ����ѭ��
#define ORDER_LOOP					2					// ˳�򲥷�
#define RANDOM_LOOP					3					// �������
//ȫ�ֱ���
struct _finddata_t F[50];
int totalMusicCount,numPlayMusicNow,lnumPlayMusicNow,iLoopType=2;
//��������
void menu();
void playmusic(struct _finddata_t F[],int lnumPlayMusicNow);
void pausemusic(struct _finddata_t F[],int lnumPlayMusicNow);
void resumemusic(struct _finddata_t F[],int lnumPlayMusicNow);
void closemusic(struct _finddata_t F[],int lnumPlayMusicNow);
void JumpMusic(int num,int iLoopType);
void playmode();
//������
int main()
{
    FILE *fp1=fopen("mp3��ʷ��¼.txt","r");      //��ȡ�ϴβ��ż�¼
    int i,j=0,k;
    char n[100];
    long Handle;
    struct _finddata_t F[50];
    menu();
    //��ʾ�����б�
    k=Handle=_findfirst("*.mp3",&F[j]);     //Ŀ¼����
    printf("\n��  �����б�   \n");
    while(k!=-1L)
    {
        printf("%d. %s\n",j+1,F[j].name);
        j++;
        k = _findnext(Handle, &F[j] );
    }
    totalMusicCount=j;
    _findclose(Handle);
    fscanf(fp1,"%d%d",&lnumPlayMusicNow,&iLoopType);     //�ϴιر�ǰ���ŵĸ���������ģʽ
    if(fp1==NULL)
        playmusic(F,0);
    else
        playmusic(F,lnumPlayMusicNow);
    if(iLoopType==1)
        printf("�� ��ǰ����ģʽ�� ����ѭ��\n");
    else if(iLoopType==2)
        printf("�� ��ǰ����ģʽ�� ˳��ѭ��\n");
    else if(iLoopType==3)
        printf("�� ��ǰ����ģʽ�� ���ѭ��\n");
    for(i=0;; i++)     //����ѭ�������Բ�����������
    {
        printf("\n��  ��ѡ�����Ĳ���:");
        scanf("%s",n);        //ʹ���ַ����洢ѡ�񣬿ɴ����쳣����
        if(strcmp(n,"1")==0)
        {
            printf("��  ������Ҫ���ŵĸ�����ţ�");
            scanf("%d",&numPlayMusicNow);
            if(numPlayMusicNow>0&&numPlayMusicNow<=totalMusicCount)   //ȷ��������źϷ�
            {
                closemusic(F,lnumPlayMusicNow);
                lnumPlayMusicNow=numPlayMusicNow-1;
                playmusic(F,lnumPlayMusicNow);
            }
            else
                printf("�Ƿ��ĸ������!");
        }
        else if(strcmp(n,"2")==0)
            pausemusic(F,lnumPlayMusicNow);
        else if(strcmp(n,"3")==0)
            resumemusic(F,lnumPlayMusicNow);
        else if(strcmp(n,"4")==0)
            JumpMusic(-1,iLoopType,F);
        else if(strcmp(n,"5")==0)
            JumpMusic(1,iLoopType,F);
		else if(strcmp(n,"p")==0)
            JumpMusic(-1,iLoopType,F);
        else if(strcmp(n,"n")==0)
            JumpMusic(1,iLoopType,F);
        else if(strcmp(n,"6")==0)
            playmode();
        else if(strcmp(n,"7")==0)
            menu();
        else if(strcmp(n,"8")==0)
        {
            FILE *fp2=fopen("mp3��ʷ��¼.txt","w");    //�ر�ǰ���ô�ʹ�ü�¼д���ļ�
            fprintf(fp2,"%d %d",lnumPlayMusicNow,iLoopType);
            fclose(fp2);
            return 0;
        }
        else
            printf("����ѡ������!");
    }
    fclose(fp1);
    return 0;
}
/***
     �����ܣ���ʾ���˵�
     �����������
     ���ߣ�nc
***/
void menu()
{
    printf("|����������  ���˵�  ����������|\n");
    printf("|��------------------------------------------��|\n");
    printf("|��               1. ����                    ��|\n");
    printf("|��               2. ��ͣ                    ��|\n");
    printf("|��               3. ����                    ��|\n");
    printf("|��               4.��һ����p��              ��|\n");
    printf("|��               5.��һ����n��              ��|\n");
    printf("|��               6.����ģʽ                 ��|\n");
    printf("|��               7.��ʾ�˵�                 ��|\n");
    printf("|��               8.�˳�                     ��|\n");
    printf("|������������������������|\n");

}
/***
     �����ܣ���������
     ����������洢������Ϣ�Ľṹ�壬Ҫ���ŵĸ������
     ���ߣ�nc
***/
void playmusic(struct _finddata_t F[],int lnumPlayMusicNow)
{
    char s1[200],s2[200];
    printf("�� ��ǰ���ţ�%d. %s\n",lnumPlayMusicNow+1,F[lnumPlayMusicNow].name);
    sprintf(s1,"play %s",F[lnumPlayMusicNow].name);    //��������д��s1�ַ���
    mciSendString(s1,NULL,0,NULL);
}
/***
     �����ܣ���ͣ����
     ����������洢������Ϣ�Ľṹ�壬Ҫ���ŵĸ������
     ���ߣ�nc
***/
void pausemusic(struct _finddata_t F[],int lnumPlayMusicNow)
{
    char s[200];
    sprintf(s,"pause %s",F[lnumPlayMusicNow].name);
    mciSendString(s,NULL,0,NULL);
}
/***
     �����ܣ��ָ�����
     ����������洢������Ϣ�Ľṹ�壬Ҫ���ŵĸ������
     ���ߣ�nc
***/
void resumemusic(struct _finddata_t F[],int lnumPlayMusicNow)
{
    char s[200];
    sprintf(s,"resume %s",F[lnumPlayMusicNow].name);
    mciSendString(s,NULL,0,NULL);
}
/***
     �����ܣ�ֹͣ����
     ����������洢������Ϣ�Ľṹ�壬Ҫ���ŵĸ������
     ���ߣ�nc
***/
void closemusic(struct _finddata_t F[],int lnumPlayMusicNow)
{
    char s[200];
    sprintf(s,"close %s",F[lnumPlayMusicNow].name);
    mciSendString(s,NULL,0,NULL);
}
/***
     �����ܣ���һ�� / ��һ����ת����
     �����������ǰ������ţ�����ģʽ���洢������Ϣ�Ľṹ��
     ���ߣ�nc
***/
void JumpMusic(int num,int iLoopType,struct _finddata_t F[])
{
    if(num==-1)    //��һ��
    {
        if(iLoopType==RANDOM_LOOP)     //���ݲ���ģʽȷ����ת��ʽ
        {
            closemusic(F,lnumPlayMusicNow);
            lnumPlayMusicNow = rand() % (totalMusicCount);
            playmusic(F,lnumPlayMusicNow);
        }
        else if(iLoopType==ORDER_LOOP)
        {
            if(lnumPlayMusicNow > 0)
            {
                lnumPlayMusicNow = lnumPlayMusicNow - 1;
                closemusic(F,lnumPlayMusicNow+1);
                playmusic(F,lnumPlayMusicNow);
            }
            else if(lnumPlayMusicNow==0)
            {
                lnumPlayMusicNow = totalMusicCount - 1;
                closemusic(F,0);
                playmusic(F,lnumPlayMusicNow);
            }
        }
        else if(iLoopType==SINGLE_LOOP)
        {
            closemusic(F,lnumPlayMusicNow);
            playmusic(F,lnumPlayMusicNow);
        }
    }
    else if(num==1)   //��һ��
    {
        if(iLoopType==RANDOM_LOOP)
        {
            closemusic(F,lnumPlayMusicNow);
            lnumPlayMusicNow = rand() % (totalMusicCount);
            playmusic(F,lnumPlayMusicNow);
        }
        else if(iLoopType==ORDER_LOOP)
        {
            if(lnumPlayMusicNow == totalMusicCount-1)
            {
                lnumPlayMusicNow = 0;
                closemusic(F,totalMusicCount-1);
                playmusic(F,lnumPlayMusicNow);
            }
            else
            {
                lnumPlayMusicNow = lnumPlayMusicNow + 1;
                closemusic(F,lnumPlayMusicNow-1);
                playmusic(F,lnumPlayMusicNow);
            }
        }
        else if(iLoopType==SINGLE_LOOP)
        {
            closemusic(F,lnumPlayMusicNow);
            playmusic(F,lnumPlayMusicNow);
        }
    }
}
/***
     �����ܣ�����ģʽ
     �����������
     ���ߣ�nc
***/
void playmode()
{
    int mode;
    printf("��  ��ѡ�񲥷�ģʽ��\n");
    printf("    1.����ѭ��\n");
    printf("    2.˳�򲥷�\n");
    printf("    3.�������\n");
    scanf("%d",&mode);
    if(mode==1)
        iLoopType=SINGLE_LOOP;
    else if(mode==2)
        iLoopType= ORDER_LOOP ;
    else if(mode==3)
        iLoopType=RANDOM_LOOP;
}
