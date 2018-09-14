EXEC=bot.out
WFLAGS= -g -std=gnu++0x -Wall -Wextra -Waddress -Wchar-subscripts \
		-Wcomment -Wformat -Wmain -Wmissing-braces\
		-Wnonnull -Wparentheses -Wreturn-type -Wsequence-point\
		-Wsign-compare -Wstrict-aliasing -Wstrict-overflow=1 -Wswitch -Wtrigraphs\
		-Wuninitialized -Wunknown-pragmas -Wunused-function -Wunused-label\
		-Wunused-value -Wunused-variable -Wvolatile-register-var -Wclobbered\
		-Wempty-body  -Wignored-qualifiers -Wmissing-field-initializers\
		-Wsign-compare -Wtype-limits -Wuninitialized -Wunused-parameter\
		-Wunused-but-set-parameter -Wfloat-equal -Wwrite-strings -Wpointer-arith\
		-Wcast-qual -Wcast-align -Wconversion -Wshadow -Wredundant-decls\
		-Wdouble-promotion -Winit-self -Wswitch-default -Wswitch-enum -Wundef\
		-Wlogical-op -Winline -Wfatal-errors
CFLAGS=
#-Ilib/program-execution-manager-auto/trunk/src/
LDFLAGS= -lm 
#-Llib/ 
CC=g++

objects=$(patsubst %.cpp,%.o,$(wildcard *.cpp))

all:
	make dependance
	make do


do: $(objects)
	$(CC) -o $(EXEC) $(objects) $(LDFLAGS)
	@ #rm *.o


%.o:%.cpp
	@ echo "$(CC) -c $< -o $@ --WFLAGS $(CFLAGS) " 
	@ $(CC) -c $< -o $@ $(CFLAGS) $(WFLAGS) $(LDFLAGS) 

run: 
	./$(EXEC) $(args)

valgrind: 
	valgrind --leak-check=full --show-leak-kinds=all ./$(EXEC) $(args)


##############
# DEPENDANCE #
# ############
dependance:

########
# MISC #
# ######

clean :
	@ rm $(EXEC)
	@ rm *.o

