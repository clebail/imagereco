CC=g++
CFLAGS=-Wall
LDFLAGS=`pkg-config --libs pHash` -lgd
ALL=imagereco

all: $(ALL)

$(ALL): main.o CColor.o CIndividu.o
	$(CC) -o $@ $(LDFLAGS) $^

%.o: %.cpp
	$(CC) -o $@ $(CFLAGS) -c $<

clean:
	rm -f $(ALL)
	rm -f *.o
