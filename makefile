
# 
# 'make'        build executable file 'mycc'
# 'make clean'  removes all .o and executable files
#

# C++ compiler and options
CC = g++
CFLAGS = -Wall
CFLAGS += -O3
CFLAGS += -g

# INCLUDES = vec3.hpp

# define the C source files
SRCS = outputImageUsingRays.cpp

# define the executable file 
MAIN = ray_tracer_output.out


all:	$(SRCS)
		$(CC) $(CFLAGS) $(INCLUDES) -o $(MAIN) $(SRCS)

clean:
		$(RM) *.o *~ $(MAIN)
