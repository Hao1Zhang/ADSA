/*
 * @Author       : Hao Zhang
 * @Date         : 2021-05-17 21:36:27
 * @LastEditors  : Hao Zhang
 * @LastEditTime : 2021-05-17 23:37:10
 * @FilePath     : \adsa\assignment3\main.cpp
 */
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <iterator>
using namespace std;

char getKey(string data)
{
    return (data.at(data.length() - 1));
}
int getIndex(char ch)
{
    int i = (int)ch - 97;
    return i;
}
char char_table[26] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'};
struct slot
{
    char key;
    string data;
    char status; // n: never used  o:occupied t:tombstone
};

class LinearTable
{
public:
    slot *table[26];
    LinearTable();
    void print();
    int searchData(string key);
    void insertData(string key);
    void deleteData(string key);
};
//create 26 new slots in a table
LinearTable::LinearTable()
{
    for (int i = 0; i < 26; i++)
    {
        table[i] = new slot;
        table[i]->key = char_table[i];
        table[i]->status = 'n';
    }
}

//print the linearhash
void LinearTable::print()
{
    int flag = 0; //lable if have stored in the table  1:has 0:empty

    int i = 0;
    for (int i = 0; i < 26; i++)
    {

        if (table[i]->status == 'o')
        {
            cout << table[i]->data << " ";
            flag = 1;
        }
    }
    if (flag == 0)
    {
        cout << "Empty";
    }
}

int LinearTable::searchData(string key)
{
    //given a key, take its last character as the hash value.
    char last = getKey(key);
    int index = getIndex(last);
    int count = 0;

    while (count <= 26)
    {

        //First try the corre-sponding table slot, if the objective key is there, then you have found it.
        if (table[index]->status == 'o' && table[index]->data == key)
        {
            return index;
        }
        //If the corresponding slot is neverused, terminate because we are certain that the objective is not in the table.
        else if (table[index]->status == 'n')
        {
            return -1;
        }
        //If the slot is occupied but it??snot the objective,
        //or the slot is a ??tombstone??,
        //then we move on to the next slot (may need to wrap aroundthe table if the current slot is the last one).
        else
        {
            index = (index + 1) % 26;
        }

        count++;
    }

        return -1;

}


void LinearTable::insertData(string key)
{
    //First perform searching to ensure that the key does not exist.
    int search_result = searchData(key);
    //If it does not, take the last character of a key as the hash value.
    if (search_result == -1)
    {
        char last = getKey(key);
        int index = getIndex(last);
        int count = 0;
        while (count <= 26)
        {
            //If the correspondingtable slot is not occupied (either ??never used?? or ??tombstone??),
            //put the key there (the slot is now occupied).
            if (table[index]->status != 'o')
            {
                table[index]->data = key;
                table[index]->status = 'o';
                return;
            }
            //If the corresponding slot is already occupied, try the next slot.
            else
            {
                index = (index + 1) % 26;
            }
            count++;
        }
    }
    //If it alreadyexists, then do nothing.
}

void LinearTable::deleteData(string key){
    //given a key, use the searching process to locate its slot.
    int search_result = searchData(key);
    //(If the key is not inthe table, then do nothing.)  
    if (search_result == -1)
    {
        return;
    }
    //change the slot status to ??tombstone??.
    else {
        table[search_result]->status = 't';
    }
    
}

int main(void)
{
    LinearTable table;
    string ip;
    getline(cin, ip);
    istringstream is(ip);
    vector<string> input((istream_iterator<string>(is)), istream_iterator<string>());
    int i = 0;

    //If firstChar is A we insertData key otherwise remove it.
    while (i < input.size())
    {
        if (input[i].front() == 'A')
        {
            table.insertData(input[i].substr(1));
        }
        else if (input[i].front() == 'D')
        {
            table.deleteData(input[i].substr(1));
        }
        i++;
    }
    table.print();
    return 0;
}