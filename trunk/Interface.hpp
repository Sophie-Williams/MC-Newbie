#ifndef __INTERFACE_HPP__
#define __INTERFACE_HPP__

#include "Message.hpp"

#define FUNC_INTERFACE std::function<void(Message& m)>

class Interface{
    private:
        Message m;
        FUNC_INTERFACE handler;
    public:
        Interface(FUNC_INTERFACE h){ handler = h; }

        void loop();
        void handle();

};

#include "Interface.tpp"

#endif
