INCFLAGS  = -I /usr/include/GL
INCFLAGS += -I /home/zeak/Projects/MIT-Computer-Graphics-Linux/zero 

LINKFLAGS  = -lglut -lGL -lGLU
LINKFLAGS += -L /mit/6.837/public/lib -lvecmath
LINKFLAGS += -L /usr/lib -lhscpp

CFLAGS    = -O0 -fpermissive -g
CC        = g++
SRCS      = Main.cpp Printer.cpp
OBJS      = $(SRCS:.cpp=.o)
PROG      = a0

all: $(SRCS) $(PROG)

$(PROG): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $@ $(INCFLAGS) $(LINKFLAGS)

.cpp.o:
	$(CC) $(CFLAGS) $< -c -o $@ $(INCFLAGS)

depend:
	makedepend $(INCFLAGS) -Y $(SRCS)

clean:
	rm $(OBJS) $(PROG)

