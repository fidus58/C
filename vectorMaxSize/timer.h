//
//  timer.h
//  vectorMaxSize
//
//  Created by Klaus Ahrens on 28.04.21.
//  Copyright © 2021 Klaus Ahrens. All rights reserved.
//

#ifndef timer_h
#define timer_h
#include <ctime>
#include <iostream>
#include <string>

const auto millis= 1'000'000.0;
class Timer {
    unsigned long t_;
    std::string for_;
    void report()
    { std::cout<<for_<<":\t"<<t_/millis<<"s"<<std::endl; }
public:
    Timer(std::string what): t_{clock()}, for_{what}{}
    ~Timer(){ t_=clock()-t_;report();}
};

#endif /* timer_h */
