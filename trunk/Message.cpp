#include "Message.hpp"

Message :: Message(){
    init();
}

void Message :: init(){
    capacity = HEADER_SIZE+100;
    rcv_msg = (char*)malloc(capacity*sizeof(char));
    memset(rcv_msg, 0, capacity);
}

Message :: ~Message(){
    free(rcv_msg);
}

size_t Message :: length(){
    return *((unsigned short*)rcv_msg);
        //((safe::cast<unsigned char, size_t>(rcv_msg[0]) << 8)
        //+ safe::cast<unsigned char, size_t>(rcv_msg[1]));
}

size_t Message :: from(){
    return static_cast<unsigned char>(rcv_msg[2]);
}

size_t Message :: to(){
    return static_cast<unsigned char>(rcv_msg[3]);
}

size_t Message :: type(){
    return static_cast<unsigned char>(rcv_msg[4]);
}

size_t Message :: misc(){
    return static_cast<unsigned char>(rcv_msg[5]);
}

char*    Message :: payload(){
    return &rcv_msg[HEADER_SIZE];
}


void Message :: length (size_t size){
    ASSERT_URANGE(size, 65535);
    unsigned short siz = safe::cast<size_t,unsigned short>(size);
    ASSERT_EQ(size, siz);
    allocate(siz);
    //rcv_msg[0] = safe::cast<unsigned int, unsigned char>(siz >> 8);
    //rcv_msg[1] = safe::cast<unsigned int, unsigned char>(siz & 255);
    rcv_msg[siz+HEADER_SIZE]= '\0';
    *((unsigned short*)rcv_msg) = siz;
    ASSERT_EQ(siz, length());
}


void Message :: allocate(size_t size){
    if((size+HEADER_SIZE+1) > capacity){
        capacity = size+HEADER_SIZE+500;
        rcv_msg = (char*)realloc(rcv_msg, capacity);
    }
}

void Message :: from   (size_t f   ){
    ASSERT_URANGE(f, 256);
    rcv_msg[2] = safe::cast<size_t,char>(f);
    ASSERT_EQ(from(), f);
}
void Message :: to     (size_t t   ){
    ASSERT_URANGE(t, 256);
    rcv_msg[3] = safe::cast<size_t,unsigned char>(t);
    ASSERT_EQ(to(), t);
}

void Message :: type   (size_t t   ){
    ASSERT_URANGE(t, 256);
    rcv_msg[4] = safe::cast<size_t, unsigned char>(t);
    ASSERT_EQ(type(), t);
}

void Message :: misc   (size_t m   ){
    ASSERT_URANGE(m, 256);
    rcv_msg[5] = safe::cast<size_t, unsigned char>(m);
    ASSERT_EQ(misc(), m);
}

void Message :: payload(const char*    str, size_t si){
    length(0);
    append(str, si);
}

void Message :: get(int fd){
    unsigned short size;
    read(fd, &size, 2);
    length(size);
    //size = safe::cast<int,unsigned short>(((size & 255) << 8) + ((size) >> 8));
    read(fd,(void*)&(get()[2]), HEADER_SIZE+size-2);
}

char* Message :: get(){
    return rcv_msg;
}

bool Message :: equal(char* p0, size_t s0, char* p1, size_t s1){
    if(s1 != s0) return false;
    for(size_t a=0; a < s0; a+=1){
        if(p0[a] != p1[a]){
            return false;
        }
    }
    return true;
}

bool Message :: equal(Message& m){
    return m.from() == from()
        && m.to()   == to()
        && m.type() == type()
        && m.misc() == misc()
        && equal(m.payload(), m.length(), payload(), length());
}

void Message :: append(char c){
    allocate(length()+1);
    rcv_msg[HEADER_SIZE+length()] = c;
    length  (length()+1);
}

void Message :: append(const char* c, size_t si){
    allocate(length()+si);
    for(size_t a = 0; a < si; a+=1){
        rcv_msg[HEADER_SIZE+length()+a]= c[a];
    }
    rcv_msg[HEADER_SIZE+length()+si]= '\0';
    length(length()+si);
}

bool Message :: isTest(){
    return from() == ID_GAME_MANAGER
        && type() == TYPE_TEST
        && misc() == MISC_TEST
        ;
}

void Message :: test(size_t fro, size_t t,
        size_t typ, size_t mi, const char* pl, size_t sizStr){
    //*
    from(ID_GAME_MANAGER);
    type(TYPE_TEST);
    misc(MISC_TEST);
    allocate(sizStr+HEADER_PRINT_SIZE);
    int nbW = sprintf(&(rcv_msg[HEADER_SIZE]),
            "%zd:%zd:%zd:%zd:%zd:", sizStr, fro, t, typ, mi);
    length(nbW);
    append(pl, sizStr);

    ASSERT_EQ(type(), TYPE_TEST);
    ASSERT_EQ(from(), ID_GAME_MANAGER);
    ASSERT_EQ(misc(), MISC_TEST);
    //*/
}

size_t Message :: parseStringToULInt(char* str, char delim, size_t& pos){
    size_t result = 0;
    for(; str[pos] != delim; pos+=1){
        result = result*10 + (str[pos]-'0');
    }
    pos+=1;
    return result;
}

void Message :: testResponse(){
    size_t pos =0;
    size_t l=parseStringToULInt(&(rcv_msg[HEADER_SIZE]), ':', pos);
    allocate(l);
    from  (parseStringToULInt(&(rcv_msg[HEADER_SIZE]), ':', pos));
    to    (parseStringToULInt(&(rcv_msg[HEADER_SIZE]), ':', pos));
    type  (parseStringToULInt(&(rcv_msg[HEADER_SIZE]), ':', pos));
    misc  (parseStringToULInt(&(rcv_msg[HEADER_SIZE]), ':', pos));
    for(size_t a=0; a<l; a+=1){
        rcv_msg[HEADER_SIZE+a] = rcv_msg[HEADER_SIZE+pos+a];
    }
    length(l);


}

void Message :: send(int fd){
    size_t a = write(fd, rcv_msg, HEADER_SIZE+length());
    ASSERT_EQ(a, HEADER_SIZE+length());
}

std::string Message :: printVersion(){
    std::string result;
    result = "" + std::to_string(length())
        + " " + std::to_string(from())
        + " " + std::to_string(to())
        + " " + std::to_string(type())
        + " " + std::to_string(misc())
        + " " + std::string(payload(), length());
    ;
    return result;
}

void Message :: printVersion(int fd, const char* str){
    size_t l = length();
    dprintf(fd, "%s%zd %zd %zd %zd %zd", str, l, from(), to(), type(), misc());
    write(fd, payload(), l);
}


void Message :: format(size_t f, size_t t, size_t ty, size_t mi){
    from(f);
    to(t);
    type(ty);
    misc(mi);
    payload("", 0);
}

