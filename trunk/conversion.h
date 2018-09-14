#ifndef __CONVERSION_H__
#define __CONVERSION_H__

#include <limits>
#include <typeinfo>

#include "error.h"

namespace safe{

    template<typename A, typename B>
    B cast(A value, A min, A max){
        if(min <= value && value <= max){
            return static_cast<B>(value);
        }
        else{
            ERROR_MESSAGE("Invalid conversion from " << value
                    << " between " << min << " and " << max);
            exit(0);
        }

    }

    template<typename A, typename B>
    B cast(A value){
        return safe::cast<A,B>(value,
                std::numeric_limits<B>::min(), std::numeric_limits<B>::max());
    }

};

#endif
