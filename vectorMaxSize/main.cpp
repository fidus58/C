//
//  main.cpp
//  vectorMaxSize
//
//  Created by Klaus Ahrens on 05.06.13.
//  Copyright (c) 2013 Klaus Ahrens. All rights reserved.
//

#include <algorithm>
#include <array>
#include <iostream>
#include <iterator>
#include <list>
#include <set>
#include <vector>
#include <iterator>

#include "timer.h"

template <typename C>
void p(const C& c, size_t n = 10) {
    std::copy_n(std::begin(c), n, std::ostream_iterator<int>(std::cout, " "));
    std::cout<<" ...\n";
}

int main(int argc, const char * argv[])
{
    const auto N = 1'000'000;
    const auto Probe = 777;
    {
        int v[N];
        {
            Timer t{"c array insertion"}; // RAII !
            std::generate(std::begin(v), std::end(v), rand);

            v[N-1]=Probe;
        }
        p(v);
        {
            Timer t{"c array find"};
            auto n = std::find(std::begin(v), std::end(v), Probe);
            if (n != std::end(v)) std::cout<<"found\n";
        }
    }
    {
        using std::vector;
        
        vector<int> v;
        {
            Timer t{"vector insertion"};

            v.reserve(N);
            std::generate(begin(v), end(v), rand);
        }
        p(v);
        {
            Timer t{"vector find"};
            auto n = std::find(begin(v), end(v), Probe);
            if (n != end(v)) std::cout<<"found\n";
        }
    }
    {
        using std::array;

        array<int, N> v;
        {
            Timer t{"std::array insertion"};
            std::generate(begin(v), end(v), rand);
        }
        p(v);
        {
            Timer t{"std::array find"};
            auto n = std::find(begin(v), end(v), Probe);
            if (n != end(v)) std::cout<<"found\n";
        }
    }

    {
        using std::set;
        
        set<int> s;
        {
            Timer t{"set insertion"};
            for (auto i=0; i<N; ++i){
                s.insert(rand());
            }
            // not: std::generate(begin(s), end(s), rand);
        }
        p(s);
        {
            Timer t{"set find"};
            //auto n = std::find(begin(s), end(s), Probe);
            auto n = s.find(Probe);
            if (n != end(s)) std::cout<<"found\n";
        }
    }
    
    {
        using std::list;
        
        list<int> l;
        {
            Timer t{"list insertion"};
            for (auto i=1; i<N; ++i){
                l.push_back(rand());
            }
            l.push_back(Probe);
            l.sort();
        }
        {
            Timer t{"list find"};
            auto n = std::find(begin(l), end(l), Probe);
            // auto n = l.find(Probe);
            if (n != end(l)) std::cout<<"found\n";
        }
    }

    return 0;
}

