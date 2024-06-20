INCFLAGS  = -I /usr/include/GL
INCFLAGS += -I /home/zeak/Projects/MIT-Computer-Graphics-Linux/zero/include
INCFLAGS += -I /usr/include/vecmath/ 
CFLAGS    = -O0 -fpermissive -g
CC        = g++
SRCS      = main.cpp ColorPicker.cpp KeyboardEvents.cpp LightPicker.cpp vecmath/vector3f.cpp vecmath/vector2f.cpp
OBJS      = $(SRCS:.cpp=.o)
PROG      = a0

all: $(SRCS) $(PROG)

$(PROG): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $@ $(INCFLAGS) $(LINKFLAGS) -lglut -lGL -lGLU  -lGLEW -DFREEGLUT_STATIC -DGLEW_STATIC

.cpp.o:
	$(CC) $(CFLAGS) $< -c -o $@ $(INCFLAGS)

depend:
	makedepend $(INCFLAGS) -Y $(SRCS)

windows: $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $@ $(INCFLAGS) -I "C:\Users\torre\Desktop\MIT-Graphics-Zero\vecmath" $(LINKFLAGS) -lfreeglut -lopengl32 -lglu32 
clean:
	rm $(OBJS) $(PROG)

