CC=gcc
INCDIR=-I/usr/local/include -Iinclude -I/usr/include
LIBDIR=-L/usr/local/lib
GLFLAGS=-framework GLUT -framework OpenGL # -lm -lX11 -lXaw -lXt -lXmu -lXdmcp -lXext -lXi
CFLAGS=$(INCDIR)
TARGET=assign2
FILES=assign2.c AsteroidImplementation.c ShipImplementation.c \
	PolygonImplementation.c BulletImplementation.c \
	PlayerImplementation.c GameImplementation.c \
	HiScoreImplementation.c \
	CollisionImplementation.c TextImplementation.c
	
FINAL_OBJS = ${FILES:.c=.o}

all: ${FINAL_OBJS}
	$(CC) -o $(TARGET) $(FINAL_OBJS) $(LIBDIR) $(GLFLAGS)

.c.o:
	$(CC) $(CFLAGS) $(INCDIR) -c $<
	
clean:
	rm -f *.o
	rm -f *~
	rm -f $(TARGET)
	rm -f core
	rm -f include/*~

