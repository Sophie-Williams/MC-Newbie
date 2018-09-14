#ifndef __ASSERT_H__
#define __ASSERT_H__

#include "error.h"

#define __ASSERT_RUNTIME_TEST__ 1

#define ASSERT_BEGIN if(__ASSERT_RUNTIME_TEST__){
#define ASSERT_END   }

#define ASSERT_SET(TYPE,VAR,VAL) TYPE VAR = VAL;

#define ASSERT_URANGE(VAL,MAX) \
    if(MAX < VAL ){\
        ERROR_MESSAGE("Invalid ASSERT : " << VAL << " < " << MAX);\
    }

#define ASSERT_RANGE(VAL,MIN,MAX) \
    if(VAL < MIN && MAX < VAL ){\
        ERROR_MESSAGE("Invalid ASSERT : " << MIN << " < " << VAL << " < " << MAX);\
    }

#define ASSERT_EQ(VAL1,VAL2) \
    if((int64_t)(VAL1) != (int64_t)(VAL2)){ \
        ERROR_MESSAGE("Invalid ASSERT : " << (int64_t)(VAL1) \
                << " != " << (int64_t)(VAL2)); \
    }

#define ASSERT_STR_EQ(VAL1,VAL2)\
    if(VAL1.compare(VAL2) != 0) {\
        ERROR_MESSAGE("Invalid ASSERT : " << VAL1 << " != " << VAL2);\
    }

#define ASSERT_FALSE() \
    ERROR_MESSAGE("Invalid ASSERT : should be false. ");\


#endif
