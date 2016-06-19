/*
 *  COPYRIGHT NOTICE
 *  Copyright (c) 2015, Douyu Network Technology Co., Ltd. in Wuhan
 *  All rights reserved.
 *
 *  @version : 1.0
 *  @author : mxl
 *  @E-mail：xiaolongicx@gmail.com
 *  @date : 2015/5/19
 *
 *  Revision Notes :
*/

#include "stdafx.h"
#include "dy_barrage_client.h"
#include <iostream>
#include <string>
#include <stdint.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <fstream>

#ifndef _MSC_VER
#	include <netdb.h>
#	include <sys/socket.h>
#else
#   include <winsock.h>
#   pragma comment(lib, "ws2_32")
#endif


using namespace std;

void usage()
{
	std::cout << "usage:" << std::endl;
	std::cout << "\t./get_dy_barrage room_id" << std::endl;
}

#ifdef _MSC_VER
void thr_keep_live(void *args)
#else
void* thr_keep_live(void *args)
#endif
{
	dy_barrage_client *dy_bclient = (dy_barrage_client *)args;

	int heart_count = 1 ;

	char filename[100]="result0619.txt";
	ofstream fout(filename,ios::app);

	while(1)
	{
		//cout << "begin to keep live" << endl;

		dy_bclient->keep_alive();
		int barr_num_pre = dy_bclient->get_dy_barr_num();

#ifdef _MSC_VER
		Sleep(45000);
#else
		sleep(45);      //keep live once per 45 seconds
#endif


		int online_num ;
		online_num = dy_bclient->get_online_num();

		cout << "\n[Prompt] The online number has been refreshed to [" << online_num <<"] just now!"<<endl;
		
		int barr_num_now = dy_bclient->get_dy_barr_num();
		int barr_num_change = barr_num_now - barr_num_pre;
		cout << "[Prompt] The barrage number in this time quantum (45s) is [" << barr_num_change << "]!\n" << endl;	

		fout << "@" << heart_count << "  " << barr_num_change << "  " << online_num << endl; 

		cout << "[Prompt] The record file has been refreshed successfully!" << endl;

		heart_count =heart_count +1 ;

		}
}



int main(int argc, char **args)
{
	int ret = 0;
	int room_id = 0;
	std::string host_name = "openbarrage.douyutv.com";
	int32_t port = 8601;
	std::string host;

	if(argc < 2)
	{
		usage();
		return 0;
	}

	// parse parameters
	room_id = atoi(args[1]);

	char filename[100]="result0619.txt";
	ofstream fout(filename,ios::app);
	fout << "#" << room_id << "$" << endl;



	dy_barrage_client dy_bclient;

	ret = dy_bclient.connect_dy_server(host_name.c_str(), port);
	if(0 != ret)
	{
		std::cout << "please check the address and restart the program" << std::endl;
		return 0;
	}

	ret = dy_bclient.login_dy_room();
	if(0 != ret)
	{
		return 0;
	}

	//ret = dy_bclient.join_dy_room_group(room_id, -9999);
    ret = dy_bclient.join_dy_room_group(room_id, -9999);
	if(0 != ret)
	{
		return 0;
	}

	// create a thread to keep alive
#ifdef _MSC_VER
	HANDLE handle = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)thr_keep_live, &dy_bclient, 0, NULL);
	//WaitForSingleObject(handle, INFINITE);
#else
	pthread_t tid;
	ret = pthread_create(&tid, NULL, &thr_keep_live, &dy_bclient);
	if(ret != 0)
	{
		cout << "[Prompt] Create pthread error!" << endl;
		return 0;
	}

#endif

	while(1)
	{	
		dy_bclient.get_dy_server_msg();
		dy_bclient.get_room_status(room_id);
	}

#ifdef _MSC_VER
#else
    pthread_join(tid, NULL);
#endif

	return 0;
}
