#ifndef CLIMBER_H_
#define CLIMBER_H_
#include <stdio.h>
#include <list>

typedef struct tagHill{
    size_t start;
    size_t end;
    size_t height;
    tagHill() : start(0), end(0), height(0){};
    tagHill(size_t s, size_t e, size_t h) : start(s), end(e), height(h){};
}Hill;

class Climber{
public:    
    Climber():hillNum(0), hillList(){};
    ~Climber(){};

    void getHills(const char*);
    size_t computeStep();

private:
    size_t hillNum;
    std::list<Hill> hillList;
 
    size_t str2Uint(const char* , size_t) const;
    void processHillDataStr(const char*);
    void adjustHill(const std::list<Hill>::iterator);

    void newHillOverlapOldProcess(const std::list<Hill>::iterator, 
        size_t& ,size_t& ,size_t& ,size_t&);
    void newHillInOldProcess(std::list<Hill>::iterator, 
        size_t& ,size_t& ,size_t& ,size_t&);
    void newHillAwayOldProcess(const std::list<Hill>::iterator, 
        size_t& ,size_t& ,size_t& ,size_t&);
    void newHillAdjoinOldProcess(const std::list<Hill>::iterator, 
        size_t& ,size_t& ,size_t& ,size_t&);
};




#endif
