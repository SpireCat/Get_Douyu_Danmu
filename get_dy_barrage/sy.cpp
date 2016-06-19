#include <stdlib.h>
#include <string.h>
#include <stdio.h>

int main(int argc, char const *argv[])
{
	
	int room_id = 6324;
	char n[16];
	sprintf(n,"%d",room_id);

	char b[100]="http://open.douyucdn.cn/api/RoomApi/room/";
	strcat(b,n);

	char a[100]="wget ";
	strcat(a,b);

	char c[100]=" -q -O room_status.html" ;
	strcat(a,c);


	system(a);

	return 0;


}