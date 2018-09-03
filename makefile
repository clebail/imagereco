CC=g++
CFLAGS=-Wall -std=gnu++11
LDFLAGS=`pkg-config --libs pHash` -lgd
ALL=imagereco

all: $(ALL)

$(ALL): main.o CColor.o CIndividu.o CGenetic.o CGeneticHistogramme.o CHistogramme.o CIndividuHistogramme.o
	$(CC) -o $@ $(LDFLAGS) $^

%.o: %.cpp
	$(CC) -o $@ $(CFLAGS) -c $<

clean:
	rm -f $(ALL)
	rm -f *.o
