#include <cstdio>
#define maxn 1000
#define updir 0
#define rtndir 1


int curx[maxn],cury[maxn],pid,pdir[maxn][2],plen[maxn];
int bid;
int solstep[maxn][8][8],sstep=maxn;

class board
{
	int fa,bcur[8][8],mid,step;
	void declarePiece(int total)
	{
		int curx[total+1],cury[total+1],pdir[total+1][2],plen[total+1];
		return;
	}
}bmem[maxn],braw;

void printcb(int p)
{
	for(int i=1;i<=6;i++)
	{
		for(int j=1;j<=6;j++)
		{
			if(bcur[i][j])
				printf("%d",bcur[i][j]);
			else
				printf("-");
		}
		puts("");
	}
	puts("");
	
	if(!p)return;
	
	for(int k=0;k<pid;k++)
	{
		printf("pid %d curx %d cury %d pdirup %d pdirrt %d plen %d\n",k,curx[k],cury[k],pdir[k][0],pdir[k][1],plen[k]);
	}
}

void puzzleIn()
{
	//initialize global para
	pid=bid=1;
	
	//set red car as id 0
	curx[1]=3;cury[1]=1;pdir[1][0]=0;pdir[1][1]=1;plen[1]=2;
	bcur[3][1]=bcur[3][2]=1;
	
	//set border
	for(int i=0;i<8;i++)
	{
		bcur[0][i]=bcur[i][0]=bcur[7][i]=bcur[i][7]=-1;
	}
	
	//read puzzle
	for(int i=1;i<=6;i++)
	{
		for(int j=1;j<=6;j++)
		{
			int c=getchar()-'0';
			braw.bcur[i][j]=c;
			if(c=='r'-'0' || c<=0)continue;
			if(braw.bcur[i-1][j]==c)
			{
				int tid=bmem[0].bcur[i-1][j];
				bmem[0].plen[tid]++;bmem[0].pdir[tid][0]=1;bmem[0].pdir[tid][1]=0;
				bmem[0].bcur[i][j]=bmem[0].bcurbcur[i-1][j];
			}
			else if(braw.bcur[i][j-1]==c)
			{
				int tid=bmem[0].bcur[i][j-1];
				bmem[0].plen[tid]++;bmem[0].pdir[tid][0]=0;bmem[0].pdir[tid][1]=1;
				bmem[0].bcur[i][j]=bmem[0].bcur[i][j-1];
			}
			else
			{	
				pid++;
				bmem[0].curx[pid]=i;bmem[0].cury[pid]=j;bmem[0].plen[pid]=1;
				bmem[0].bcur[i][j]=pid;
			}
		}
		getchar();
	}
	
	//set first board memory
	
//	printcb(1);
}

int getStep(int bnumber)
{
	if(!bnumber)
	{
//		printf("id 0 step 0\n");
		return 0;
	}
	bstep[bnumber]=getStep(bfa[bnumber])+1;
//	printf("id %d step %d\n",bnumber,bstep[bnumber]);
	return bstep[bnumber];
}

int mshifting(int id)
{
	int cnt=0;
	for(int i=1;i<=6;i++)
	{
		int xd=(curx[id]-i)*pdir[id][1],yd=(cury[id]-i)*pdir[id][0];
		if(!bcur[i+xd][i+yd])
		{
			cnt++;
		}
		else if(bcur[i+xd][i+yd]==id)break;
		else
			cnt=0;
	}
	return (cnt)?1:0;
}

int xshifting(int id)
{
	int cnt=0;
	for(int i=6;i>=1;i--)
	{
		int xd=(curx[id]-i)*pdir[id][1],yd=(cury[id]-i)*pdir[id][0];
		if(!bcur[i+xd][i+yd])
		{
			cnt++;
		}
		else if(bcur[i+xd][i+yd]==id)break;
		else
			cnt=0;
	}
	return cnt;
}

void pieceMove(int id, int shift)
{
	int mc,xc;
	
	//clean track
	if(pdir[id][1])
	{
		mc=cury[id];	mc+=(shift>0)?0:shift;
		xc=cury[id]+plen[id]-1;	xc+=(shift>0)?shift:0;
		for(int i=mc;i<=xc;i++)
		{
			bcur[curx[id]][i]=0;
		}
	}
	else
	{
		mc=curx[id];	mc+=(shift>0)?0:shift;
		xc=curx[id]+plen[id]-1;	xc+=(shift>0)?shift:0;
		for(int i=mc;i<=xc;i++)
		{
			bcur[i][cury[id]]=0;
		}
	}
	
	//place piece
	for(int i=0;i<plen[id];i++)
	{
		bcur[curx[id]+pdir[id][0]*(i+shift)][cury[id]+pdir[id][1]*(i+shift)]=id;
	}
	curx[id]+=pdir[id][0]*(shift);cury[id]+=pdir[id][1]*(shift);
}

void solRecord(int id,int step)
{
	if(step)solRecord(bfa[id],step-1);
	for(int i=1;i<=6;i++)
	{
		for(int j=1;j<=6;j++)
		{
			solstep[step][i][j]=bmem[id][i][j];
		}
	}
}

bool isSolved(int id)
{
	if(bmem[id][3][5]==1 && bmem[id][3][6]==1)
	{
		if(bstep[id]<sstep)
		{
			solRecord(id,getStep(id));
			sstep=bstep[id];
		}
		return 1;
	}
	return 0;
}

int memorize(int step, int fa)
{
	int dif,k;
	
	//check memory, dif=1 not seen, dif=0 seen
	for(k=0;k<bid;k++)
	{
		dif=0;
		for(int i=1;i<=6;i++)
		{
			for(int j=1;j<=6;j++)
			{
				if(bmem[k][i][j]!=bcur[i][j])
				{
					dif=1;break;
				}
			}
			if(dif)break;
		}	
		if(dif)continue;
		else if(!dif)break;
	}
	
	if(dif)
	{
		printf("Saved as %d Father %d\n\n",bid,fa);
		for(int i=1;i<=6;i++)
		{
			for(int j=1;j<=6;j++)
			{
				bmem[bid][i][j]=bcur[i][j];
			}
		}
		bfa[bid]=fa;bstep[bid]=getStep(fa)+1;
		if(isSolved(bid))return 0;
		return bid++;
	}
	else if(!dif)
	{
		printf("dupe of %d\n\n",k);
		if(step<bstep[k])
		{
			printf("original father %d original step %d\n",bfa[k],bstep[k]);
			bfa[k]=fa;bstep[k]=getStep(fa)+1;
			printf("after father %d after step %d\n",bfa[k],bstep[k]);
			return 0;
		}
	}
	
	return 0;
}

void pieceRun(int id, int fa)
{
	int mshift,xshift,step=getStep(fa)+1,me,membid=bid;
	mshift=mshifting(id);xshift=xshifting(id);
	for(int i=mshift;i<=xshift;i++)
	{
		if(!i)continue;
		intab(step-1);printf("Step %d Shifting piece %d %d\n",step,id,i);
		printcb(0);
		pieceMove(id,i);
		printcb(0);
		me=memorize(step,fa);
		if(!me){pieceMove(id,-i);continue;}
		for(int j=1;j<=pid;j++)
		{
			if(j==id)continue;
			pieceRun(j,me);
		}
		pieceMove(id,-i);//restore
	}
	printf("set bid from %d to %d\n",bid,membid);
	bid=membid;
}

void printsol()
{
	for(int k=0;k<=sstep;k++)
	{
		for(int i=1;i<=6;i++)
		{
			for(int j=1;j<=6;j++)
			{
				printf("%d",solstep[k][i][j]);
			}
			puts("");
		}
		puts("");
	}
}

int main()
{
	freopen("input.txt","r",stdin);
	freopen("output.txt","w",stdout);
	puzzleIn();
/*	for(int i=1;i<=pid;i++)
		pieceRun(i,0);
	printf("Fastest steps %d\n",sstep);
	printsol();*/
}