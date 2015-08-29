#include "climber.h"
#include <cstring>
#include <iostream>
#include <algorithm>
#include <assert.h>
#include <vector>

//invalid return -1
size_t Climber::str2Uint(const char* str, size_t size) const{
    if(NULL == str)
        return -1;
    size_t rt = 0;
    int index = size;
    while(index--){
        if(*(str + index) > '9' || *(str + index) < '0')
            std::cout<<"error: invalid input not number"<<std::endl;
        rt = rt * 10 + (*(str + index) - '0');
    }
    return rt;     
}

void Climber::processHillDataStr(const char* const str){
    char tmp[100];
    strcpy(tmp, str);
    char *p = NULL;
    Hill hill;
    p = strtok(tmp, ",");
    if(p)
        hill.start = str2Uint(p, strlen(p));    
    else
        std::cout<<"error: hill data no start"<<std::endl;
    
    p = strtok(NULL, ",");
    if(p)
        hill.end = str2Uint(p, strlen(p));    
    else
        std::cout<<"error: hill data no end"<<std::endl;   
       
    p = strtok(NULL, ",");
    if(p)
        hill.height = str2Uint(p, strlen(p));    
    else
        std::cout<<"error: hill data no height"<<std::endl;  
    
    p = strtok(NULL, ",");
    if(p)
        std::cout<<"warning: extra data exist in one hill entry"<<std::endl; 
	
    hillList.push_back(hill);
}

void Climber::getHills(const char *str){
    char tmp[200];
    strcpy(tmp, str);
    std::vector<char *> pList;
    char *p = NULL; 
    p = strtok(tmp, "\n");
    if(p)
        hillNum = str2Uint(p, strlen(p));    
    else
        std::cout<<"error: no hill number in input str"<<std::endl;
    
    size_t num = hillNum;
    while(num--){
        p = strtok(NULL, "\n");
        if(p){
            pList.push_back(p);
        }
        else
            std::cout<<"error: hill data number not equal to input number"<<std::endl;   
    }
    p = strtok(NULL, "\n");
    if(p)
        std::cout<<"warning: extra hill entry exist"<<std::endl;
    for(size_t i = 0; i < pList.size(); i++)
        processHillDataStr(pList[i]);
}

bool hillCmpFunc(const Hill& lhs, const Hill& rhs){
    return lhs.start < rhs.start;
}

//adjust hill seq according to it's new start
void Climber::adjustHill(const std::list<Hill>::iterator _iter){
    std::list<Hill>::iterator cur = _iter;
    std::list<Hill>::iterator next = _iter;
    Hill toBeAdjust(cur->start, cur->end, cur->height);
    
    while(next != hillList.end() && next->start < cur->start)
        next++;
    hillList.insert(next, toBeAdjust);
    hillList.erase(cur);
}


void Climber::newHillOverlapOldProcess(const std::list<Hill>::iterator iter, 
        size_t& curStart,
        size_t& curEnd,
        size_t& curHeight,
        size_t& totalStep
        ){
    if(iter->height >= curHeight){
        totalStep += iter->start - curStart;
        totalStep += iter->height - curHeight;
        curStart = iter->start;
        curHeight = iter->height;
        curEnd = iter->end;
    }else{
        totalStep += iter->start - curStart;  
        curStart = iter->start;
        iter->start = curEnd;
        adjustHill(iter);
    }
}

void Climber::newHillInOldProcess(std::list<Hill>::iterator iter, 
        size_t& curStart,
        size_t& curEnd,
        size_t& curHeight,
        size_t& totalStep
        ){
    if(iter->height > curHeight){
        totalStep += iter->start - curStart;
        totalStep += iter->height - curHeight;
        curStart = iter->start;
        curEnd = iter->end;
        curHeight = iter->height;
	iter--;
	if(iter->end > curEnd){
	    iter->start = curEnd;
	    adjustHill(iter);
	}
	iter++;
    }
}

void Climber::newHillAwayOldProcess(const std::list<Hill>::iterator iter, 
        size_t& curStart,
        size_t& curEnd,
        size_t& curHeight,
        size_t& totalStep
        ){
    totalStep += iter->start - curStart;
    totalStep += curHeight + iter->height;
    curStart = iter->start;
    curHeight = iter->height;
    curEnd = iter->end;
}

void Climber::newHillAdjoinOldProcess(const std::list<Hill>::iterator iter, 
        size_t& curStart,
        size_t& curEnd,
        size_t& curHeight,
        size_t& totalStep
        ){
    totalStep += iter->start - curStart;
    totalStep += abs(curHeight - iter->height);
    curStart = iter->start;
    curHeight = iter->height;
    curEnd = iter->end;
}

size_t Climber::computeStep(){
    assert(hillNum == hillList.size());
    assert(hillNum > 0);
    hillList.sort(hillCmpFunc);
    size_t curStart = 0;
    size_t curEnd = 0;
    size_t curHeight = 0;
    size_t totalStep = 0;

    for(std::list<Hill>::iterator iter = hillList.begin();
            iter != hillList.end();
            iter++){
        if(iter->start > curEnd){
            newHillAwayOldProcess(iter, curStart, curEnd, curHeight, totalStep);
        }else if(iter->start == curEnd){
            newHillAdjoinOldProcess(iter, curStart, curEnd, curHeight, totalStep);
        }else{
            if(iter->end > curEnd){
                newHillOverlapOldProcess(iter, curStart, curEnd, curHeight, totalStep);
            //process equal situation
            }else{
                newHillInOldProcess(iter, curStart, curEnd, curHeight, totalStep);
            }
        }//end else if(iter.start > curEnd)
    }//end for
	
    totalStep += curEnd - curStart + curHeight;

    return totalStep;
}


