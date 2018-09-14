#include <cstdlib>
#include <iostream>

#include "Interface.hpp"


#define MAX_UNIT 200
#define MAX_BUID 100
#define MAX_PLAY   2

int main(){
    /*
    std::cout << "Size Unit in memory : " << sizeof(Unit)
        << " ( " << sizeof(Unit)/sizeof(uint64_t) << " int64 )"<< std::endl;
        */
    Interface([](Message& m) {
            });

    return EXIT_SUCCESS;
}
