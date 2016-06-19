#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string>
#include <regex>
using namespace std;


int main(int argc, char const *argv[])
{
	FILE * pFile;
	long size;
	char * buffer;
	size_t result;

	pFile=fopen("room_status.html","rb");
	if(pFile==NULL){
		fputs("File error",stderr);
		exit(1);
	}
	fseek(pFile,0,SEEK_END);
	size=ftell(pFile);
	rewind(pFile);

	buffer=(char *)malloc(sizeof(char)*size);
	if(buffer == NULL){
		fputs("M error",stderr);
		exit(2);
	}

	result = fread(buffer,1,size,pFile);

	if(result!=size){
		fputs("R error",stderr);
		exit(3);
	}

	fclose(pFile);
	free(buffer);

	string ss;
	ss.assign(buffer,result);
	//cout<<ss<<endl;

    regex pattern("online\":(\\d+),");  //(?<=online":)\d+(?=,)

	smatch rgresult;

	bool match = regex_search(ss,rgresult,pattern);

	string r;

	if(match){		
		r=rgresult[1].str();		
	}
	else{
		cout<<"Failed to get online number !"<<endl;
	}

	int online_num = atoi(r.c_str());

	cout << online_num << endl;

	return 0;
}
