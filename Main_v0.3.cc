#include <cstdio>
#include <queue>
#include <cstdlib>
#define maxn 100000
#define maxp 20

int pid,bid;

class board
{
	public:
		int fa,bcur[8][8],step,mid;
		int curx[maxp],cury[maxp],pdir[maxp][2],plen[maxp];

		void setBorder()
		{
			for(int i=0;i<8;i++)
			{
				bcur[0][i]=bcur[i][0]=bcur[7][i]=bcur[i][7]=-1;
			}	
		}
		
		void printb(int p)
		{
			puts("--------------");
			for(int i=1;i<=6;i++)
			{
				for(int j=1;j<=6;j++)
				{
/*					if(bcur[i][j]==10)
						putchar('<');
					else if(bcur[i][j]==20)
						putchar('>');
					else if(bcur[i][j]==30)
						putchar(94);
					else if(bcur[i][j]==40)
						putchar('v');*/
					if(bcur[i][j]<10 && bcur[i][j])
						printf("%d",bcur[i][j]);
					else if(bcur[i][j]>=10)
						printf("%c",bcur[i][j]+'A'-10);
					else
						printf("-");
                    //printf("%d ",bcur[i][j]);
				}
				puts("");
			}
			puts("--------------");
			
			if(!p)return;

			for(int k=1;k<=pid;k++)
			{
				printf("pid %d curx %d cury %d pdirup %d pdirrt %d plen %d\n",k,curx[k],cury[k],pdir[k][0],pdir[k][1],plen[k]);
			}
		}
	
		void copy(board from)
		{
			for(int i=0;i<8;i++)
			{
				for(int j=0;j<8;j++)
				{
					
				}
			}
		}
	
		void pieceMove(int id, int shift)
		{
			int mc,xc;

			//clean track
			if(pdir[id][1])
			{
				mc=cury[id];	mc+=(shift<0)?shift:0;
//				printf("%d\n",plen[id]);
				xc=cury[id]+plen[id]-1;	xc+=(shift>0)?shift:0;
				for(int i=mc;i<=xc;i++)
				{
					bcur[curx[id]][i]=0;
//					if(shift>0)bcur[curx[id]][i]+=10;
				}
			}
			else
			{
				mc=curx[id];	mc+=(shift>0)?0:shift;
				xc=curx[id]+plen[id]-1;	xc+=(shift>0)?shift:0;
				for(int i=mc;i<=xc;i++)
				{
					bcur[i][cury[id]]=0;
//					if(shift>0)bcur[curx[id]][i]+=10;
				}
			}

			//place piece
			for(int i=0;i<plen[id];i++)
			{
				bcur[curx[id]+pdir[id][0]*(i+shift)][cury[id]+pdir[id][1]*(i+shift)]=id;
			}
			curx[id]+=pdir[id][0]*(shift);cury[id]+=pdir[id][1]*(shift);
		}
	
		int mshifting(int id)
		{
			int cnt=0;
			for(int i=1;i<=6;i++)
			{
				int xd=(curx[id]-i)*pdir[id][1],yd=(cury[id]-i)*pdir[id][0];
				if(!(bcur[i+xd][i+yd]))
				{
					cnt++;
				}
				else if(bcur[i+xd][i+yd]==id)break;
				else
					cnt=0;
			}
			return -1*cnt;
		}
	
		int xshifting(int id)
		{
			int cnt=0;
			for(int i=6;i>=1;i--)
			{
				int xd=(curx[id]-i)*pdir[id][1],yd=(cury[id]-i)*pdir[id][0];
				if(!(bcur[i+xd][i+yd]))
				{
					cnt++;
				}
				else if(bcur[i+xd][i+yd]==id)break;
				else
					cnt=0;
			}
			return cnt;
		}

		bool comp(board he)
		{
			for(int i=1;i<=6;i++)
			{
				for(int j=1;j<=6;j++)
				{
					if(he.bcur[i][j]!=bcur[i][j])
						return 1;
				}
			}
			return 0;
		}
	
}bmem[maxn],braw;

std::queue<board> q;

void puzzleIn()
{    
	//initialize global para
	pid=bid=1;
	
	//set red car as id 1
	bmem[0].curx[1]=3;bmem[0].pdir[1][0]=0;bmem[0].pdir[1][1]=1;bmem[0].plen[1]=2;
	
	bmem[0].setBorder();
	
	//read puzzle
	for(int i=1;i<=6;i++)
	{
		for(int j=1;j<=6;j++)
		{
			int c=getchar()-'0';
			braw.bcur[i][j]=c;
			if(c<=0)continue;
			if(c=='r'-'0')
			{
				if(braw.bcur[i][j-1]!='r'-'0')
				{
					bmem[0].cury[1]=j;
					bmem[0].bcur[3][j]=1;
					bmem[0].bcur[3][j+1]=1;
				}
				continue;
			}
			if(braw.bcur[i-1][j]==c)
			{
				int tid=bmem[0].bcur[i-1][j];
				bmem[0].plen[tid]++;bmem[0].pdir[tid][0]=1;bmem[0].pdir[tid][1]=0;
				bmem[0].bcur[i][j]=bmem[0].bcur[i-1][j];
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
	
	bmem[0].fa=bmem[0].step=bmem[0].mid=0;
	q.push(bmem[0]);
	
	bmem[0].printb(1);
}

bool hasSeen(board me)
{	
	//check memory, dif=1 not seen, dif=0 seen
	for(int k=0;k<bid;k++)
	{
		if(!me.comp(bmem[k]))
		{
			return 1;
		}
	}
	return 0;
}

bool isSolved(board me)
{
	if(me.bcur[3][5]==1 && me.bcur[3][6]==1)
		return 1;
	return 0;
}

void solvePrint(int me)
{	
	if(bmem[me].mid)solvePrint(bmem[me].fa);
	bmem[me].printb(0);
	
	getchar();
}

void intab(int j)
{
	for(int i=0;i<j;i++)
		printf("\t");
}

void puzzleRun()
{
	while(!q.empty())
	{
		braw = q.front();
		for(int id=1;id<=pid;id++)
		{
//			printf("id %d min %d max %d\n",id,braw.mshifting(id),braw.xshifting(id));
			for(int dir=braw.mshifting(id);dir<=braw.xshifting(id);dir++)
			{
				if(!dir)continue;
//				intab(braw.step);printf("id %d dir %d fa %d\n",id,dir,q.front().mid);
				braw.pieceMove(id,dir);
//				braw.printb(0);
				braw.step++;braw.fa=q.front().mid;
				if(hasSeen(braw))
				{
					braw = q.front();
					continue;
				}
				bmem[bid]=braw;bmem[bid].mid=bid;
				if(isSolved(bmem[bid]))
				{
					solvePrint(bid);
					return;
				}
//				printf("id %d curx %d cury %d shift %d\n",id,bmem[bid].curx[id],bmem[bid].cury[id],dir);
//				printf("bid %d father %d step %d\n",bid,bmem[bid].fa,bmem[bid].step);
//				bmem[bid].printb(0);
				q.push(bmem[bid]);
				bid++;
				braw=q.front();
			}
		}
		q.pop();
	}
}

int main()
{
//	freopen("input.txt","r",stdin);
    freopen("/Users/Cheeseonhead1/Documents/Dev_C++/Minor Projects/Unblock Me Solutions/input.txt","r",stdin);
	puzzleIn();
    //puzzleRun();
	
}