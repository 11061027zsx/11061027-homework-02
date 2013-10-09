#include <stdio.h>
#include <string.h>
#define M 100
#define max(a,b) (a)>(b)?(a):(b)
#define sinput "input.txt"

FILE *file;
int a[M][M],i,j,m,n,s;
int color[M][M];
int dx[]={-1,0,1,0},dy[]={0,-1,0,1};

void F()
{
	int g[M][M],f[M][M],i,j,s,x,k;
	for(i=0;i<m;i++)
	for(j=0;j<n;j++) f[i][j]=g[i][j]=0;
	
	s=a[0][0];
	
	for(i=0;i<m;i++){
		g[i][0]=a[i][0];
		for(j=1;j<n;j++) g[i][j]=g[i][j-1]+a[i][j];
	}
	
	for(i=0;i<m;i++)
	for(j=0;j<n;j++)
	for(k=j;k<n;k++){
		x=g[i][k]-g[i][j]+a[i][j];
		if(f[j][k]>0) f[j][k]+=x;
		else f[j][k]=x;
		if(f[j][k]>s) s=f[j][k];
	}
	printf("%d",s);
}


void Fvh(int v,int h)
{
	int g[M][M],f[M][M],l[M][M],i,j,s,aa[M][M],nn,mm,nx,x,k,;
	
	nn=n;
	mm=m;
	
	if(h) nn=2*n;
	if(v) mm=2*m;
	
	for(i=0;i<mm;i++)
	for(j=0;j<nn;j++){
		aa[i][j]=a[i%m][j%n];
		l[i][j]=f[i][j]=g[i][j]=0;
	}
	
	s=a[0][0];
	
	
	for(i=0;i<mm;i++){
		g[i][0]=aa[i][0];
		for(j=1;j<nn;j++) g[i][j]=g[i][j-1]+aa[i][j];
	}
	

	for(i=0;i<mm;i++)
	for(j=0;j<nn;j++)
	for(k=j,nx=0;k<nn;k++,nx++){
		
		if(nx>=n) break;

		
		x=g[i][k]-g[i][j]+aa[i][j];
		
		if(f[j][k]>0&&l[j][k]<m){
			f[j][k]+=x;
			l[j][k]++;
		}
		else{
			f[j][k]=x;
			l[j][k]=1;
		}
		
		if(f[j][k]>s) s=f[j][k];

	}
	printf("%d",s);

}



int IsInvh(int x,int y)
{
	if(x>=0&&x<m&&y>=0&&y<n) return 1;
	return 0;
}


void fany(int x,int y,int z)
{
	int tx,ty,i;
	
	if(s<z) s=z;
	for(i=0;i<4;i++){
		tx=x+dx[i];
		ty=y+dy[i];
		if(IsInvh(tx,ty)&&!color[tx][ty]){
			color[tx][ty]=1;
			fany(tx,ty,z+a[tx][ty]);
			color[tx][ty]=0;
		}
	}
}






main(int N,char **CMD)
{
	int h,v,u;
	u=h=v=0;
	file=fopen(sinput,"r");
	fscanf(file,"%d, %d, ",&m,&n);
	for(i=0;i<m;i++)
	for(j=0;j<n;j++) fscanf(file,"%d, ",a[i]+j);
	
	fclose(file);
	for(i=1;i<N;i++){
		if(!strcmp(CMD[i],"/h")) h=1;
		if(!strcmp(CMD[i],"/v")) v=1;
		if(!strcmp(CMD[i],"/a")) u=1;
	}
	
	
	if(!(h+v)&&!u){
		F();
		return 0;
	}
	if(!u){
		Fvh(v,h);
		return 0;
	}
	
	
	for(i=0;i<m;i++)
	for(j=0;j<n;j++){
		color[i][j]=1;
		fany(i,j,a[i][j]);
		color[i][j]=0;
	}
	printf("%d",s);
	
}
