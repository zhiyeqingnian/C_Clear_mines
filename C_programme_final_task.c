#include<stdio.h>
#include<time.h>
#include<stdlib.h>
#define M 100
#define N 100
#define P 102
#define Q 102				        //最大排数和列数不能超过M排N列
char leiqu_show[M][N];			    //展示给玩家的雷区，即实际展示的雷区
char leiqu_actual[P][Q];			//实际生成的雷区，用户见不到，即隐藏部分
int turn=0,win=0;					//定义游玩次数和胜利次数
time_t start,end;					//定义开始和结束时间，用于计时
int countboom(X,Y)					//检测选中区域的周围雷的个数
{
	int c=0;
	if(leiqu_actual[X-1][Y-1]=='1')
	c++;
	if(leiqu_actual[X][Y-1]=='1')
	c++;
	if(leiqu_actual[X+1][Y-1]=='1')
	c++;
	if(leiqu_actual[X-1][Y]=='1')
	c++;
	if(leiqu_actual[X+1][Y]=='1')
	c++;
	if(leiqu_actual[X-1][Y+1]=='1')
	c++;
	if(leiqu_actual[X][Y+1]=='1')
	c++;
	if(leiqu_actual[X+1][Y+1]=='1')
	c++;
	return c;
}
void view(int X,int Y)				//展示出周围的雷数
{
    int m,n;
    m=X-1;
    n=Y-1;
	if(leiqu_actual[X-1][Y-1]=='0')
	leiqu_show[m-1][n-1]=countboom(X-1,Y-1)+'0';
	if(leiqu_actual[X][Y-1]=='0')
	leiqu_show[m][n-1]=countboom(X,Y-1)+'0';
	if(leiqu_actual[X+1][Y-1]=='0')
	leiqu_show[m+1][n-1]=countboom(X+1,Y-1)+'0';
	if(leiqu_actual[X-1][Y]=='0')
	leiqu_show[m-1][n]=countboom(X-1,Y)+'0';
	if(leiqu_actual[X+1][Y]=='0')
	leiqu_show[m+1][n]=countboom(X+1,Y)+'0';
	if(leiqu_actual[X-1][Y+1]=='0')
	leiqu_show[m-1][n+1]=countboom(X-1,Y+1)+'0';
	if(leiqu_actual[X][Y+1]=='0')
	leiqu_show[m][n+1]=countboom(X,Y+1)+'0';
	if(leiqu_actual[X+1][Y+1]=='0')
	leiqu_show[m+1][n+1]=countboom(X+1,Y+1)+'0';
}
int remainunkonwn(i,j)			   	//计算还剩多少个‘*’
{
	int count=0;
	int I=0,J=0;
	for(I=0;I<=i-1;I++)
	{
		for(J=0;J<=j-1;J++)
		{
			if(leiqu_show[I][J]=='*')
			{
				count++;
			}
		}
	}
	return count;
}
int printmapnext(i,j)				//打印后续雷区
{
	int a,b;
	printf("下面是%d排%d列的雷区\n",i,j);		//test
	for(a=0;a<j+1;a++)						//用于生成列数序号
	{
		if(a<=9)
		printf("%d  ",a);
		else
		printf("%d ",a);
	}
	printf("\n");
	for(a=0;a<i;a++)
	{
		if(a<9)								//用于生成行数序号
		printf("%d  ",a+1);					//个位数前面加了一个空格
		else
		printf("%d ",a+1);					//防止个位数带来的排版错位
		for(b=0;b<j;b++)
		{
			printf("%c  ",leiqu_show[a][b]);
		}
		printf("\n");
	}
	printf("\n");
	/*printf("下面是实际计算区域\n",i,j);	//此区域为显示雷所在坐标，不向用户展示
	for(a=0;a<i+3;a++)
	{
		for(b=0;b<j+3;b++)
		{
			printf("%c ",leiqu_actual[a][b]);
		}
		printf("\n");
	}
	printf("\n");*/
	return 0;
}
int printmap(i,j)			       	//初始化雷区并生成雷区
{
	int a,b,t=0,s,degree=0;
	int n,X,Y,k;
	s=i*j;
	for(a=0;a<=i+2;a++)
	{
		for(b=0;b<=j+2;b++)
		{
			leiqu_show[a][b]='*';
			leiqu_actual[a][b]='0';				//初始化雷区显示区域和实际区域							     
		}
	}		
	printf("初始化成功！\n");                 //test
	printf("正在加载...\n");
	printf(">>>>请选择需要的难度:\n");
printf("\n");
printf("\t\t\t##########################\n");
printf("\t\t\t##        1 简单        ##\n");
printf("\t\t\t##        2 中等        ##\n");
printf("\t\t\t##        3 困难        ##\n");
printf("\t\t\t##########################\n");   
scanf("%d",&degree);
switch(degree)                          //用户输入来选择游戏难度
{
    case 1:
        {
          n=(s/10);                     //简单难度
          break;
        }
    case 2:
        {
            n=(s/5);                    //中等难度
            break;
        }
    case 3:
        {
            n=(s/3);                    //困难难度
            break;
        }
    default:
        printf("输入有误，请您从新输入（注意只要输入数字！）\n");break;
        }                                   
								//根据雷区的大小进行布雷								
	k=0;
    while(k<n)
	{  
		X=rand()%(i)+1;
		Y=rand()%(j)+1;					//2020.12.13修改了随机数生成方式，速度变快
        if(leiqu_actual[X][Y]=='0')
		{
            leiqu_actual[X][Y]='1';
            t++;
            k++;
		}
	}
	printf("下面是%d排%d列的雷区\n",i,j);		//test
	for(a=0;a<j+1;a++)						//用于生成列数序号
	{
		if(a<=9)
		printf("%d  ",a);
		else
		printf("%d ",a);
	}
	printf("\n");
	for(a=0;a<i;a++)
	{
		if(a<9)								//用于生成行数序号
		printf("%d  ",a+1);					//个位数前面加了一个空格
		else
		printf("%d ",a+1);					//防止个位数带来的排版错位
		for(b=0;b<j;b++)
		{
			printf("%c  ",leiqu_show[a][b]);
		}
		printf("\n");
	}
	/*printf("\n");
    printf("下面是实际计算区域\n",i,j);			//此区域为显示雷所在坐标，不向用户展示
	for(a=0;a<i+2;a++)
	{
		for(b=0;b<j+2;b++)
		{
			printf("%c ",leiqu_actual[a][b]);
		}
		printf("\n");
	}*/
	printf("\n");
	printf("一共有%d个雷\n",t);			//test
	printf("\n");
	return t;
}
int sweepboom(i,j)					//扫雷函数
{
	int X=0,Y=0;
	int z,rip;
	printf("请输入扫雷的坐标：");			//玩家开始排雷
	scanf("%d %d",&X,&Y);
	if(X>=1&&X<=i&&Y>=1&&Y<=j)
	{
		if(leiqu_actual[X][Y]=='0')			//没踩到雷//到此没有运行问题
		{
			z=countboom(X,Y);
			leiqu_show[X-1][Y-1]=z+'0';
			view(X,Y);
			printmapnext(i,j);
			rip=0;
				return rip;								
		}
		else if(leiqu_actual[X][Y]=='1')		//踩到雷了
		{
			rip=1;					//test
			return rip;
		}
	}
	else
	{
		printf("输入有误，请重新输入\n");
		sweepboom(i,j);
		rip=0;
	}
	return rip;
}
void playgame()					        //开始游戏的函数
{
	int i,j,count,rip=0,t;
	turn++;							//游玩次数加1
	printf("请输入雷区的范围：\n");
	scanf("%d %d",&i,&j);	        
	t=printmap(i,j);				//打印雷区，初始化，并且返还i,j,n的数值		
	while(rip==0)
	{
		rip=sweepboom(i,j);	        //玩家开始扫雷，踩到雷返回1，没踩到返回0
		if(rip==0)
		{
			printf("真不错，你没有踩到雷，继续扫雷吧！\n");
			count=remainunkonwn(i,j);
        	printf("有%d个地雷在此区域内\n",t);           //test
       		printf("还有%d个区域没扫\n",count);          //test
			if(remainunkonwn(i,j)==t)                  //==t输出的是雷的总个数
			{
				win++;									//胜利次数加1
				printmapnext(i,j);
				printf("你赢了！太棒了！\n");
				printf("\n");
				printf(">>>>还要继续吗？\n");
				break;
			}
		}
		if(rip==1)
	    {
        printf("很遗憾，你被雷炸死了\n");
		printf("\n");
		printf(">>>>还要继续吗？\n");
        }
	}
}
int main()					        //主函数
{                    
	int select=0,usetime=0;
	start=time(NULL);
	printf("\t\t\t##########################\n");
	printf("\t\t\t##  欢迎进入 扫雷游戏！\t##\n");
	printf("\t\t\t##########################\n");
	while(select!=2)
	{
		printf("\n");
		printf(">>>>请做出以下选择:\n");
		printf("\n");
		printf("\t\t\t##########################\n");
		printf("\t\t\t##	1 开始游戏！	##\n");
		printf("\t\t\t##	2 结束游戏！	##\n");
		printf("\t\t\t##########################\n");	
		scanf("%d",&select);
		switch(select)          //用户输入来选择模式
		{
			case 1:
				{
                    playgame();	//调用开始游戏函数
                    break;
                }
			case 2:
				{
					printf("您已结束游戏！\n");
					break;		//让玩家决定要不要玩了，不玩就结束循环
				}
			default:
				printf("输入有误，请您从新输入（注意只要输入数字！）\n");break;
		}																			
	}
	end=time(NULL);				//获取结束时间
	usetime=end-start;			//结束时间和开始时间的差为所用时间
	printf("游戏结束，你一共玩了%d局，其中你获胜了%d局，一共用时%d秒，你真的太棒啦！\n",turn,win,usetime);	//包含计数和计时，如果时间够的话会加入获胜率啥的
}