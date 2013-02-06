//to compile:  g++  -Wall diskbench.cpp -o diskb -lrt
//example input:  ./diskb 10 1 g
// loop 10 times with 1 GB file size, more loop the more precise


#include <iostream>
#include <stdio.h>
#include <time.h>
#include <stdlib.h> 
#include <fcntl.h>
#include <string.h>

using namespace std;

unsigned long long multiplier = 1000ULL*1ULL*1ULL;
unsigned long long  size =10;
int loop = 10;

int main(int argc, char* argv[] )
{
if(argc != 4){
	cout<<"example input: ./name (loop) (file size) (b/k/m/g)"<<endl;
	return 0; 
}
for(int i = 0 ; i <argc; i++){
//cout << argv[i] <<" ";
	if(i == 1){
	loop = (int )strtoul(argv[1],0,0);	
	}
	if(i == 2){
	size = (unsigned long long )strtoul(argv[2],0,0);	
	}
	if(i == 3){
		if(*argv[i] == 'b'){multiplier = 1ULL;}
		if(*argv[i] == 'k'){multiplier = 1000ULL;}
		if(*argv[i] == 'm'){multiplier = 1000000ULL;}
		if(*argv[i] == 'g'){multiplier = 1000000000ULL;}
	}
}
//cout << endl << loop<<" "<< size <<" "<< multiplier<< endl;
char* a = new char[multiplier];
for(unsigned long long i =0 ; i < multiplier ; ++i){
   a[i] = 'a';//fill array
}

timespec TimeStart;
timespec TimeEnd;


FILE* pFile;

clock_gettime(CLOCK_REALTIME, &TimeStart);
for(int k =0; k < loop; k++){


pFile =fopen("benchfile.binary", "wb");
setvbuf(pFile , NULL, _IONBF, 0);
for(unsigned long long j =0 ; j < size; ++j){
   
fwrite(a,1,multiplier*sizeof(char),pFile);

}
fclose(pFile);

}
clock_gettime(CLOCK_REALTIME, &TimeEnd); 

double interval;
interval = (TimeEnd.tv_nsec - TimeStart.tv_nsec);//nano seconds
interval = interval /1000000000 +TimeEnd.tv_sec - TimeStart.tv_sec;
string spd = "B";
long long totalWrote =(size*loop*multiplier);
if(totalWrote > 1000){ 
	spd = "KB";
	totalWrote = totalWrote/1000;
}
if(totalWrote > 1000){ 
	spd = "MB";
	totalWrote = totalWrote/1000;
}

double result = totalWrote/(interval);
cout <<"Wrote: "<<totalWrote<<spd<<" Seconds: " <<interval <<" : "<< result<<spd<<"/s"<<endl;
return 0;

}
