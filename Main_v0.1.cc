#include <cstdio>

int px[1000],py[1000],pdir[1000],plen[1000],cx[1000],cy[1000],tp;
int board[8][8],boardid[8][8],bmem[10000][8][8],bmemi;
int qid[1000],qshift[1000];

void puzzleIn()
{
	int c,id=0;
	memset(board,0,sizeof(board));
	memset(boardid,0,sizeof(boardid));
	bmemi=1;
	
	cx[0]=px[0]=3;cy[0]=py[0]=1;pdir[0]=10;plen[0]=2;
	boardid[3][1]=boardid[3][2]=100;
	
	for(int i=0;i<8;i++)
	{
		boardid[0][i]=-1;
		boardid[i][0]=-1;
		boardid[7][i]=-1;
		boardid[i][7]=-1;
	}
	
	for(int i=1;i<=6;i++)
	{
		for(int j=1;j<=6;j++)
		{
			c=getchar()-'0';
			board[i][j]=c;
			if(c=='r'-'0' || c<=0)
			{
				continue;
			}
			if((board[i-1][j]!=c) && (board[i][j-1]!=c))
			{
				id++;
				cx[id]=px[id]=i;cy[id]=py[id]=j;plen[id]=1;
				boardid[i][j]=id;
			}
			if(board[i-1][j]==c)
			{
				int t=boardid[i-1][j];
				plen[t]++;pdir[t]=1;
				boardid[i][j]=t;
			}
			if(board[i][j-1]==c)
			{
				int t=boardid[i][j-1];
				plen[t]++;pdir[t]=10;
				boardid[i][j]=t;
			}
		}
		getchar();
	}
	for(int i=1;i<=6;i++)
	{
		for(int j=1;j<=6;j++)
		{
			bmem[0][i][j]=boardid[i][j];
		}
		
	}
	tp=id;
}

int mshifting(int id)
{
	int dis=-1;
	int xdis=pdir[id]%10,ydis=pdir[id]/10;
	while(boardid[cx[id]+(xdis*dis)][cy[id]+(ydis*dis)]==0)
	{
		dis--;
	}
	return dis+1;
}

int xshifting(int id)
{
	int dis=1;
	int xdis=pdir[id]%10,ydis=pdir[id]/10;
	int tx=cx[id]+(xdis*(plen[id]-1)),ty=cy[id]+(ydis*(plen[id]-1));
	while(boardid[tx+(xdis*dis)][ty+(ydis*dis)]==0)
	{
			dis++;
	}
	return dis-1;
}

void printb()
{
	for(int i=1;i<=6;i++)
	{
		for(int j=1;j<=6;j++)
			printf("%3d ",boardid[i][j]);
		puts("");
	}
	puts("");
}

void modboard(int id,int sh)
{
	if(pdir[id]==1)
	{
		if(sh<0)
		{
			for(int i=cx[id]+sh;i<cx[id]+plen[id];i++)
			{
				boardid[i][cy[id]]=0;
			}
			for(int i=cx[id]+sh;i<cx[id]+plen[id]+sh;i++)
			{
				boardid[i][cy[id]]=id;
			}
			cx[id]+=sh;
		}
		else if(sh>0)
		{
			for(int i=cx[id];i<cx[id]+plen[id]+sh;i++)
			{
				boardid[i][cy[id]]=0;
			}
			for(int i=cx[id]+sh;i<cx[id]+plen[id]+sh;i++)
			{
				boardid[i][cy[id]]=id;
			}
			cx[id]+=sh;
		}
	}
	else if(pdir[id]==10)
	{
		if(sh<0)
		{
			for(int i=cy[id]+sh;i<cy[id]+plen[id];i++)
			{
				boardid[cx[id]][i]=0;
			}
			for(int i=cy[id]+sh;i<cy[id]+plen[id]+sh;i++)
			{
				boardid[cx[id]][i]=id;
			}
			cy[id]+=sh;
		}
		else if(sh>0)
		{
			for(int i=cy[id];i<cy[id]+plen[id]+sh;i++)
			{
				boardid[cx[id]][i]=0;
			}
			for(int i=cy[id]+sh;i<cy[id]+plen[id]+sh;i++)
			{
				boardid[cx[id]][i]=id;
			}
			cy[id]+=sh;
		}
	}
	printb();
}

bool hasseen()
{
	int dif;
	for(int k=0;k<bmemi;k++)
	{
		dif=0;
		for(int i=1;i<=6;i++)
		{
			for(int j=1;j<=6;j++)
			{
				if(bmem[k][i][j]!=boardid[i][j])
				{
					dif=1;
					break;
				}
			}
			if(dif)break;
		}
		if(!dif)return 1;
	}
	bmemi++;
	for(int i=1;i<=6;i++)
	{
		for(int j=1;j<=6;j++)
		{
			bmem[bmemi][i][j]=boardid[i][j];
		}
	}
	return 0;
}

bool puzzleRun(int id,int step)
{
	printf("id %d step %d\n",id,step);
	int mshift=mshifting(id),xshift=xshifting(id);
	printf("xshift %d mshift %d\n",xshift,mshift);
	printb();
	for(int i=mshift;i<=xshift;i++)
	{
		printf("i %d\n",i);
		if(!i)continue;
		qid[step]=id;qshift[step]=i;
		modboard(id,i);
		printf("cx %d cy %d\n\n",cx[id],cy[id]);
		if(hasseen()){puts("true");continue;}
		for(int j=1;j<=3;j++)
		{
			if(j==id)continue;
			puzzleRun(j,step+1);
		}
		puts("back");
		modboard(id,-i);
	}
}

int main()
{
	freopen("input.txt","r",stdin);
	puzzleIn();
	puzzleRun(1,0);
}