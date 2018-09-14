#ifndef __ERROR_H__
#define __ERROR_H__

#include <iostream>
#include <limits>

#define ERROR_MESSAGE(X) \
	std::cerr << "[error] " << __FILE__ \
<< ", function " << __FUNCTION__ \
<< ", line " << __LINE__ \
<< ", message : "  << X << std::endl; \
exit(-2);

#define ERROR_MESSAGE_WITH_CALLER(CALLER,X) \
	std::cerr << "[error] " << __FILE__ \
<< ", function " << __FUNCTION__ \
<< ", line " << __LINE__ \
<< ", caller " << CALLER \
<< ", message : "  << X << std::endl; \
exit(-1);

#define WARNING_MESSAGE(X) \
	std::cerr << "[warning] " << __FILE__ \
<< ", function " << __FUNCTION__ \
<< ", line " << __LINE__ \
<< ", message : "  << X << std::endl; \

#define ASSERTION_ERROR_MESSAGE(X) \
	std::cerr << "[error][assertion] " << __FILE__ \
<< ", function " << __FUNCTION__ \
<< ", line " << __LINE__ \
<< ", message : "  << X << std::endl; \
exit(-1);

#define SIZE_T_ERROR (std::numeric_limits<size_t>::max())

#endif
