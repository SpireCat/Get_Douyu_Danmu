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
#include "data_def.h"
#include "dy_encoder.h"
#include <time.h>
#include <string>
#include <iostream>

using namespace std;

static string pack_header(string data_str)
{
    string pack_str;

    int data_len = data_str.length() + 8;
    short msg_type = 689;     //client message type is 689
    char encrypt = 0;
    char reserve =0;

    pack_str.append((const char *)&data_len, sizeof(data_len));      // 4 bytes is len
    pack_str.append((const char *)&data_len, sizeof(data_len));      // 4 bytes is len
    pack_str.append((const char *)&msg_type, sizeof(msg_type));      // 2 bytes is message type
    pack_str.append((const char *)&encrypt, sizeof(encrypt));      // 1 bytes is encrypt
    pack_str.append((const char *)&reserve, sizeof(reserve));      // 1 bytes is reserve
    pack_str.append(data_str.data(), data_str.size());        //data

    return pack_str;
}

int get_dy_msg_type(string pack_data)
{
    if (pack_data.size() <= 8)
    {
        return -1;
    }

    int msg_type = 0;

    string dec_str(pack_data.data() + 8, pack_data.size() - 8);
    //cout << dec_str << endl;

    dy_decoder dec;
    dec.parse(dec_str.c_str());

    string type_str = dec.get_item_as_string("type");
    //cout << type_str << endl;
    if(type_str == "chatmsg")
    {
        msg_type = MSG_TYPE_BARRAGE;
    }
    else if (type_str == "loginres")
    {
        msg_type = MSG_TYPE_LOGIN_RESPONSE;
    }

    return msg_type;
}

string dy_login_req::transform_to_dy_string()
{
    dy_encoder enc;
    enc.add_item("type", "loginreq");

    string enc_str = enc.get_result();

    //cout << enc_str << endl;
    //cout << enc_str.length() << ", " << enc_str.size() << endl;

    char c = '\0';
    enc_str.append((const char *)&c, 1);        //should end with '\0'

    //cout << enc_str.length() << ", " << enc_str.size() << endl;

    return pack_header(enc_str);
}

void dy_login_res::parse_from_dy_string(string data)
{
	ret = 0;
    string dec_str(data.data() + 8, data.size() - 8);
    //cout << dec_str << endl;

    dy_decoder dec;
    dec.parse(dec_str.c_str());

    string type_str = dec.get_item_as_string("type");
    //cout << type_str << endl;
    if(type_str != "loginres")
    {
        ret = -1;
    }
}

dy_join_group_req::dy_join_group_req() : room_id(0), group_id(0)
{
}

dy_join_group_req::dy_join_group_req(int rid, int gid) : room_id(rid), group_id(gid)
{
}

string dy_join_group_req::transform_to_dy_string()
{
    dy_encoder enc;
    enc.add_item("type", "joingroup");
    enc.add_item("rid", room_id);
    enc.add_item("gid", group_id);

    string enc_str = enc.get_result();

    //cout << enc_str << endl;
    //cout << enc_str.length() << ", " << enc_str.size() << endl;

    char c = '\0';
    enc_str.append((const char *)&c, 1);        //should end with '\0'

    //cout << enc_str.length() << ", " << enc_str.size() << endl;

    return pack_header(enc_str);
}

#ifdef _MSC_VER
dy_keep_alive_req::dy_keep_alive_req():timestamp(GetTickCount())
{
}
#else
dy_keep_alive_req::dy_keep_alive_req():timestamp(time(NULL))
{
}

#endif

dy_keep_alive_req::dy_keep_alive_req(int ts):timestamp(ts)
{
}

string dy_keep_alive_req::transform_to_dy_string()
{
    dy_encoder enc;
    enc.add_item("type", "keeplive");
    enc.add_item("tick", timestamp);

    string enc_str = enc.get_result();

    //cout << enc_str << endl;
    //cout << enc_str.length() << ", " << enc_str.size() << endl;

    char c = '\0';
    enc_str.append((const char *)&c, 1);        //should end with '\0'

    //cout << enc_str.length() << ", " << enc_str.size() << endl;

    return pack_header(enc_str);
}

void dy_barrage_res::parse_from_dy_string(string data)
{
    string dec_str(data.data() + 8, data.size() - 8);
    //cout << dec_str << endl;

    dy_decoder dec;
    dec.parse(dec_str.c_str());

    ct = dec.get_item_as_int("ct");
    content = dec.get_item_as_string("txt");
    sender_rg = dec.get_item_as_int("rg");
    sender_pg = dec.get_item_as_int("pg");
    sender_name = dec.get_item_as_string("nn");

    /*
    content = dec.get_item_as_string("content");
    string ui_str = dec.get_item_as_string("sui");

    //cout << ui_str << endl;

    dy_decoder dec_ui;
    dec_ui.parse(ui_str.c_str());

    sender_rg = dec_ui.get_item_as_int("rg");
    sender_pg = dec_ui.get_item_as_int("pg");
    sender_name = dec_ui.get_item_as_string("nick");
    */
    //cout << sender_name << endl;

}
