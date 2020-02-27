#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define MAX 100

typedef struct
{
    float gdp;
    float pcdi;
    int year;
}ECO;

typedef struct
{
    ECO *data;
    int datasize;
    int length;
}ECOM;

int initecom(ECOM *t)
{
    t->data=(ECO *)malloc(sizeof(ECO)*MAX);
    if(t->data==NULL)
        return 0;
    t->datasize=MAX;
    t->length=0;
    for(int i=0;i<MAX;i++)
        t->data[i].year=10000;
    return 1;
}

/*����һ������*/
int addecom(ECOM *e,ECO da,int i)
{
    if(e->length>e->datasize)
        return 0;
    int t=0;
    while(e->data[t].year<i)
        t++;
    for(int j=e->length;j>t;j--)
        e->data[j]=e->data[j-1];
    e->data[t].gdp=da.gdp;
    e->data[t].pcdi=da.pcdi;
    e->data[t].year=i;
    e->length++;
    return 1;
}

/*���ҵ�i�����ݷ�������λ��*/ 
int searchecom(ECOM *e,int i)
{
    int t=0;
    while(e->data[t].year!=i)
        t++;
    if(t>e->length-1)
        return -1;
    else
        return t+1;
}

/*���ҵ�i������*/ 
void Search(ECOM *e,int i)
{
	int t;
	t=searchecom(e,i);
	t--;
	printf("%d��GDP��%.1f,PCDI��%.1f\n",i,e->data[t].gdp,e->data[t].pcdi);
}

/*�޸ĵ�i������*/ 
int modify(ECOM *e,int i,float gdp,float pcdi)
{
	int t;
	t=searchecom(e,i);
	if(t==-1)
	{
		printf("���ݲ�����\n");
		return 0;
	}
	else
	t--;
	e->data[t].gdp=gdp;
	e->data[t].pcdi=pcdi;
	return 1;	
}

/*ɾ����i������*/ 
int deecom(ECOM *e,ECO *da,int i)
{
    int t;
    if(e->length<=0)
        return 0;
    t=searchecom(e,i);
    if(t!=-1)
        t--;
    else
        return 0;
    da->gdp=e->data[t].gdp;
    da->pcdi=e->data[t].pcdi;
    da->year=e->data[t].year;
    int j;
    for(j=t;j<e->length-1;j++)
        e->data[j]=e->data[j+1];
    e->length--;
    return 1;
}

/*��ʾ���д洢����*/ 
void dispecom(ECOM e)
{
	int i=0;
	while(i<e.length)
	{
		printf("%d��GDP(��Ԫ):%.1f,PCDI:%.1f\n",e.data[i].year,e.data[i].gdp,e.data[i].pcdi);
		i++;
	}
}

/*����GDP�����ʿ���*/ 
void quick_sort(float s[], int l, int r)  
{  
    if (l < r)  
    {  

        int i = l, j = r;float x = s[l];  
        while (i < j)  
        {  
            while(i < j && s[j] >= x) 
                j--;    
            if(i < j)   
                s[i++] = s[j];  
              
            while(i < j && s[i] < x) 
                i++;    
            if(i < j)   
                s[j--] = s[i];  
        }  
        s[i] = x;  
        quick_sort(s, l, i - 1);   
        quick_sort(s, i + 1, r);  
    }  
}

/*���ݷ����Ա�*/ 
int analysis(ECOM e)
{
	int i,j;float maxgdp=0,maxpcdi=0;
	int year1,year2;
	float percent[100];
	
	for(i=0;i<e.length;i++)
	{
		
		if(e.data[i].gdp>maxgdp)
		{
			
			maxgdp=e.data[i].gdp;
			year1=e.data[i].year;
			
		}
		if(e.data[i].pcdi>maxpcdi)
		{
			
			maxpcdi=e.data[i].pcdi;
			year2=e.data[i].year;
		}
	}
	printf("%d��GDP���Ϊ��%.1f(��Ԫ)\n%d��PCDI���Ϊ��%.1f\n",year1,maxgdp,year2,maxpcdi);
	
	for(j=0;j<e.length-1;j++)
	{
		
		float a,b,c;
		a=e.data[j].gdp;
		b=e.data[j+1].gdp;
		c=(b-a)/a;
		percent[j]=c;
		
	}
	//������������ 
	quick_sort(percent,0,e.length-2);
	
	float t;
	t=percent[e.length-2]*100;
	printf("GDP���������Ϊ��%.3f %c\n",t,'%');
	
}


void vertical(ECOM *T,int j)
{
    int i=j;
    float maxvalue=0,minivalue=T->data[0].gdp;
    for(i;i<j+10; i++)
    {
        if(T->data[i].gdp>maxvalue)
            maxvalue=T->data[i].gdp;
        if(T->data[i].gdp<minivalue)
            minivalue=T->data[i].gdp;
    }
    float division=(maxvalue-minivalue)/10;
    printf("   y/gdp|\n");
    //����y��
    for(float scale=maxvalue+0.1; scale>minivalue-0.1; scale=scale-division)
    {
        printf("%8.1f|_",scale);
        for(i=j; i<j+10; i++)
        {
            
			 if(T->data[i].gdp<scale&&T->data[i].gdp>scale-division)
                printf("____");
            else if(T->data[i].gdp>scale)
                printf("|  |");
            else
                printf("    ");
        }
        printf("\n");
    }
    //����x��
    printf("        |_");
    for(i=j; i<j+10; i++)
        printf("|__|");
    printf("___��\n");
    for(i=j; i<j+10; i++)
        printf("     ");
    printf("x/year\n");
    printf("        ");
    for(i=j; i<j+10; i++)
        printf("%4d",T->data[i].year);
    printf("\n");
}

void menu()
{
	printf("-----��������ϵͳ-----\n");
	printf("1.�鿴��������\n");
	printf("2.����һ������\n");
	printf("3.ɾ��һ������\n");
	printf("4.��ѯһ������\n");
	printf("5.�޸�һ������\n");
	printf("6.֧���ļ��������\n");
	printf("7.���ݷ����Ա�\n");
	printf("8.��������\n");
	printf("----------------------\n");
}

int main()
{
	ECOM e;ECO data;float gdp,pcdi;int year;
    initecom(&e);
    //�ı���������洢40��GDP��PCDI���� 
    FILE *fp;
    if((fp=fopen("d:\\Dev\\�γ����\\f1.txt","r"))==NULL)
    {
    	printf("error!\n");
    	exit(0);
	}
	
    for(int i=0;i<41;i++)
    {
    	fscanf(fp,"%f%f%d",&e.data[i].gdp,&e.data[i].pcdi,&e.data[i].year);
    	e.length++;
    }
    	
	fclose(fp);
	
	
	while(1)
	{
		int n;
		menu();
		printf("�����빦��ǰ���:\n");
		scanf("%d",&n);
		switch(n)
		{
			case 1:	dispecom(e);
					break;
			case 2: printf("���ӵ���ݣ�");
					scanf("%d",&data.year);
					printf("����GDP(��Ԫ)��");
					scanf("%f",&data.gdp); 
					printf("����PCDI��");
					scanf("%f",&data.pcdi);
					addecom(&e,data,data.year);
					break;
			case 3: printf("Ҫɾ������ݣ�");
					scanf("%d",&year);
					deecom(&e,&data,year);
					break;
			case 4: printf("Ҫ��ѯ����ݣ�");
					scanf("%d",&year);
					Search(&e,year);
					break;
			case 5: printf("Ҫ�޸ĵ���ݣ�");
					scanf("%d",&year);
					printf("%d��GDP(��Ԫ)��",year);
					scanf("%f",&gdp);
					printf("%d��pcdi��",year);
					scanf("%f",&pcdi); 
					modify(&e,year,gdp,pcdi);
					break;
			case 6: if((fp=fopen("d:\\Dev\\�γ����\\ecom_out.txt","w"))==NULL)
					{
						printf("error!\n");
						exit(0);
					}
					printf("input the gdp,pcdi,year:\n");
					scanf("%f%f%d",&gdp,&pcdi,&year);
					rewind(fp);
					fprintf(fp,"%.1f %.1f %d",gdp,pcdi,year);
					fclose(fp);
					if((fp=fopen("d:\\Dev\\�γ����\\ecom_out.txt","r"))==NULL)
					{
						printf("error!\n");
						exit(0);
					}
					fscanf(fp,"%f%f%d",&gdp,&pcdi,&year);
					data.gdp=gdp;
					data.pcdi=pcdi;
					data.year=year;
					addecom(&e,data,year);
					fclose(fp);
					break;
			case 7:	
				{	analysis(e);
					int t=(e.length-0)/10;
					int j;
					for(j=0;j<t;j++)
					vertical(&e,10*j);
					break;
				} 
			case 8: exit(0);
					break;
		}
	}

    return 0;
}
