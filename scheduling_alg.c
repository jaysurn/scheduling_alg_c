#include<stdio.h>
#include<stdlib.h>
//gcc -g -Wall -o Lab5 Lab5.c -lm -lpthread
typedef struct process{//Proccess attributes
	int name;
	int bt;
	int at;
	int wt,ta;
	int flag;
}processes;

int accept( processes P[] ){//Process creator and attribute setter
	int i;
	int n =- 1;
	int t =- 1;
	while( n <= 0 ){
	printf( "\n Enter total no. of processes : " );
	scanf( "%d",&n );
	}
	for( i = 0; i < n ; i++ ){
		printf( "\n PROCESS [ %d ]",i+1 );
		P[ i ].name = i;
		printf( " Enter arrival time : " );
		scanf( "%d",&P[ i ].at );
		t = P[ i ].at;
		while( t<0 ){ 
		printf( " Enter arrival time : " );
		scanf( "%d",&P[ i ].at );
		t = P[ i ].at;
		}
		printf( " Enter burst time : " );
		scanf( "%d",&P[ i ].bt );
		t = P[ i ].bt;
		while( t<0 ){
		printf( " Enter burst time : " );
		scanf( "%d",&P[ i ].bt );
		t = P[ i ].bt;
		}
	}
	printf( "\n PROC.\tA.T.\tB.T.\tPRIORITY" );
	for( i = 0; i < n ; i++ )
		printf( "\n %d\t%d\t%d\t",P[ i ].name,P[ i ].at,P[ i ].bt );
	return n;
}

// FCFS Algorithm
void FCFS( processes P[],int n ){
	int sumw=0,sumt=0;
	float avgwt=0.0,avgta=0.0;
	int i;
		printf( "\n\n PROC.\tB.T.\tA.T." );
		for( i = 0; i < n ; i++ )
			printf( "\n %d\t%d\t%d",P[ i ].name,P[ i ].bt,P[ i ].at );

		sumw = P[ 0 ].wt = 0;
		sumt = P[ 0 ].ta = P[ 0 ].bt - P[ 0 ].at;

		for( i = 1 ; i < n ; i++ ){
			P[ i ].wt = ( P[ i - 1 ].bt + P[ i - 1 ].at + P[ i - 1 ].wt ) - P[ i ].at;;
			P[ i ].ta = ( P[ i ].wt + P[ i ].bt );
			sumw += P[ i ].wt;
			sumt += P[ i ].ta;
		}
		avgwt = ( float )sumw/n;
		avgta = ( float )sumt/n;
		printf( "\n\n PROC.\tB.T.\tA.T.\tW.T\tT.A.T" );
		for( i = 0 ; i < n ; i++ )
			printf( "\n %d\t%d\t%d\t%d\t%d",P[ i ].name,P[ i ].bt,P[ i ].at,P[ i ].wt,P[ i ].ta );
		
	
		printf( "\n\n Average waiting time = %0.2f\n Average turn-around = %0.2f.",avgwt,avgta );
}


//SJF Non Pre-emptive
void SJF_NP( processes P[],int n ){
	processes t;
	int sumw = 0, sumt = 0;
	float avgwt = 0.0, avgta = 0.0;
	int i,j;
	
	for( i = 2 ; i < n ; i++ )
		for( j = 1 ; j < n - i + 1 ; j++ ){
			if( P[ j ].bt > P[ j + 1 ].bt ){
				t = P[ j ];
				P[ j ] = P[ j + 1 ];
				P[ j + 1 ] = t;
			}
		}

	printf( "\n\n PROC.\tB.T.\tA.T." );
		for( i = 0 ; i < n ; i++ )
			printf( "\n %d\t%d\t%d",P[ i ].name,P[ i ].bt,P[ i ].at );

		sumw = P[ 0 ].wt = 0;
		sumt = P[ 0 ].ta = P[ 0 ].bt - P[ 0 ].at;

		for( i=1;i<n;i++ ){
			P[ i ].wt = ( P[ i - 1 ].bt + P[ i - 1 ].at + P[ i - 1 ].wt ) - P[ i ].at;;
			P[ i ].ta = ( P[ i ].wt + P[ i ].bt );
			sumw += P[ i ].wt;
			sumt += P[ i ].ta;
		}
		avgwt = ( float )sumw/n;
		avgta = ( float )sumt/n;
		printf( "\n\n PROC.\tB.T.\tA.T.\tW.T\tT.A.T" );
		for( i = 0 ; i < n ; i++ )
			printf( "\n %d\t%d\t%d\t%d\t%d",P[ i ].name,P[ i ].bt,P[ i ].at,P[ i ].wt,P[ i ].ta );
		

		printf( "\n\n Average waiting time = %0.2f\n Average turn-around = %0.2f.",avgwt,avgta );
}



//Round Robin Scheduling
void RR( processes P[],int n )
{
	int pflag = 0, t, tcurr = 0, k, i, Q = 0 ;
	int sumw = 0 , sumt = 0 ;
	float avgwt = 0.0 , avgta = 0.0 ;
	processes temp2[ 10 ];	
	for( i = 0 ; i < n ; i++ )
		temp2[ i ] = P[ i ];
	
	printf( "\n Enter quantum time : " );
	scanf( "%d",&Q );
	
	for( k = 0 ;; k++ ){
		if( k > n-1 )
			k = 0;
		if( P[ k ].bt > 0 )
		t = 0;
		while( t < Q && P[ k ].bt > 0 ){
			t++;
			tcurr++;
			P[ k ].bt--;
		}  
		if( P[ k ].bt  <=  0 && P[ k ].flag != 1 ){
			P[ k ].wt = tcurr - temp2[ k ].bt - P[ k ].at;
			P[ k ].ta = tcurr - P[ k ].at;
			pflag++;
			P[ k ].flag = 1;
			sumw += P[ k ].wt;
			sumt += P[ k ].ta;
		}
		if( pflag == n )
			break;
	}
	avgwt = ( float )sumw/n;
	avgta = ( float )sumt/n;
	
	printf( "\n\n PROC.\tB.T.\tA.T.\tW.T\tT.A.T" );
		for( i = 0 ; i < n ; i++ )
			printf( "\n %d\t%d\t%d\t%d\t%d",P[ i ].name,P[ i ].bt,P[ i ].at,P[ i ].wt,P[ i ].ta );
	printf( "\n\n Average waiting time = %0.2f\n Average turn-around = %0.2f.",avgwt,avgta );
}

int main(  ){
	
	processes P[ 10 ];
	int ch,n;
	do{
		printf( "\n\n SIMULATION OF CPU SCHEDULING ALGORITHMS\n" );
		printf( "\n Options:" );
		printf( "\n 0. Enter process data." );
		printf( "\n 1. FCFS" );
		printf( "\n 2. SJF" );
		printf( "\n 3. Round Robin" );
		printf( "\n 4. Exit\n Select : " );
		scanf( "%d",&ch );
		switch( ch ){
			case 0:
				n=accept( P );
				break;
			case 1:
				FCFS( P,n );
				break;
			case 2:
				SJF_NP( P,n );
				break;
			case 3:
				RR( P,n );
				break;
			case 4:exit( 0 );	
		}
	}while( ch != 4 );
	getchar(  );
	return 0;
}