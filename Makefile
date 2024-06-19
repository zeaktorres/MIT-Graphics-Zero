INCFLAGS  = -I /usr/include/GL
INCFLAGS += -I /home/zeak/Projects/MIT-Computer-Graphics-Linux/zero/include
INCFLAGS += -I /usr/include/vecmath/ 
	
LINKFLAGS += -L"C:\Users\torre\Desktop\MIT-Graphics-Zero\vecmath\"
CFLAGS    = -O0 -fpermissive -g
CC        = g++
SRCS      = main.cpp ColorPicker.cpp KeyboardEvents.cpp LightPicker.cpp
OBJS      = $(SRCS:.cpp=.o)
PROG      = a0

all: $(SRCS) $(PROG)

$(PROG): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $@ $(INCFLAGS) $(LINKFLAGS) -lglut -lGL -lGLU

.cpp.o:
	$(CC) $(CFLAGS) $< -c -o $@ $(INCFLAGS)

depend:
	makedepend $(INCFLAGS) -Y $(SRCS)

windows: $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $@ $(INCFLAGS) $(LINKFLAGS) -lfreeglut -lopengl32 -lglu32 
clean:
	rm $(OBJS) $(PROG)

