#ifndef __MESSAGE_HPP__
#define __MESSAGE_HPP__

/*
Message format:
                 1       2       3
 0       8       6       4       2
+---------------------------------+
| Message length [ FROM  [ TO     |
+---------------------------------+
|  Type  [ MISC  [    FUTURE      |
+---------------------------------+
| Your message only composed by   | \
| printable letters               | | Max 65535 bytes
| ASCII code [32,126] (SPACE to ~)| |
| ...                             | /
+---------------------------------+

With :

- Len
    - represent the size of the MSG (without FROM/TO/TYPE/MISC/FUTURE section)

- FROM - TO - Type (Combinaison signification, 'n' -> BotN, 'X' -> BotN/Game)
   - 255     __0       0   0 : not ok     \  Status message // NOT USED
   - 255     __0       0   1 : oK         |  No data       // NOT USED
   - 255     __0       0   2 : play       |  No data       // NOT USED
    ==== LOG section ====
   -   X     __0       0  10 : log primary       // NOT USED
   -   X     __0       0  11 : log info          // NOT USED
   -   X     __0       0  12 : log warning       // NOT USED
   -   X     __0       0  13 : log error         // NOT USED
   -   X     __0       0  14 : log state         // NOT USED
   -   0     __0       0  18 : set log in binary // NOT USED
   -   0     __0       0  19 : set lob in text   // NOT USED
    ==== STATUS ANNOUNCEMENT section ====
   -   0     __0       0  20 : bot[n] concede      // NOT USED
   -   0     __0       0  21 : bot[n] lost         // NOT USED
   -   0     __0       0  22 : bot[n] win          // NOT USED
   -   0     __0       0  23 : bot/GAME crash      // NOT USED
    ==== STATUS REQUEST section ====
   -   0     __0       0  30 : game ended /  No data       // NOT USED
   - 255     __0       0 131 : Game finished       // NOT USED
   - 255     __0       0  39 : close ASAP          // NOT USED
    ...
   -   n       0 [1-255] [0-255] : Basic message BOT  to GAME
   -   0 [0-254] [1-255] [0-255] : Basic message GAME to BOT
   -   0     255 [1-255] [0-255] : Broadcast message from Game

- MSG
    - can be empty
    - request to GM depend of the Entity.
        - GAME, message TO field must be set   '0'.
        - BOT , message TO field must be set '255'.
    - GM always set the FROM field to '255' when send a message.

- All unspecified case are INVALID
- BOT/GAME that emit an invalid message will be close.

*/

#define ID_GAME          0
#define ID_GAME_MANAGER 255

#define TYPE_OK         0
#define TYPE_TEST      10

#define MISC_TEST       1

#define HEADER_SIZE           8 //bytes
#define HEADER_PRINT_SIZE     23 //bytes max

#include <string>
#include <cstring>
#include <iostream>
#include <boost/algorithm/string.hpp>

#include <unistd.h>
#include <arpa/inet.h>

#include "conversion.h"
#include "error.h"
#include "assert.h"

class Message{
    public:
        Message();
        virtual ~Message();

        void init();

        void allocate(size_t size);

        size_t length();
        size_t from();
        size_t to();
        size_t type();
        size_t misc();
        char*  payload();
        char* get();

        void length (size_t size);
        void from   (size_t f   );
        void to     (size_t t   );
        void type   (size_t t   );
        void misc   (size_t m   );
        void payload(const char*  str, size_t si );
        void get(int fd);

        void format(size_t f, size_t t, size_t ty, size_t misc);

        bool equal(Message& m);
        bool equal(char* p0, size_t s0, char* p1, size_t s1);

        size_t parseStringToULInt(char* str, char delim, size_t& pos);


        bool isTest();
        void test(size_t fro, size_t t,
                size_t typ, size_t misc, const char* payload, size_t sizStr);
        void testResponse();

        unsigned int responseSize();

        void append(char c);
        void append(const char* c, size_t si);

        std::string printVersion();
        void printVersion(int fd, const char* str);
        void send(int fd);

    private:
        char* rcv_msg;
        size_t capacity;

};

#endif

