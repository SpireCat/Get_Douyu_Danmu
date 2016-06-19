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

#ifndef __DY_CODEC_H__
#define __DY_CODEC_H__

#include <string>
#include <vector>

using namespace std;

class dy_encoder
{
private:
    string buf;

public:
    dy_encoder();
    ~dy_encoder();

    //get result string after douyu style encode
    string get_result();

    //add key-value item
    void add_item(const char *key, const char *value);
    void add_item(const char *key, const int value);
};

struct key_value
{
    string key;
    string value;
};


class dy_decoder
{
public:
    typedef vector<key_value> item_array;

private:
    item_array arr;

public:
    dy_decoder();
    ~dy_decoder();

    //parse douyu style encode string.
    //Note: always do this before get items.
    void parse(const char * data);

    //get item of specified key
    string get_item_as_string(const char *key);
    int get_item_as_int(const char *key);
};

#endif      //__DY_CODEC_H__
