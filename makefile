CC=g++
CFLAGS=-Wall -std=gnu++11 `pkg-config --cflags pHash`
LDFLAGS=`pkg-config --libs pHash` -lgd
ALL=imagereco

all: $(ALL)

$(ALL): main.o CIndividu.o CGenetic.o CGeneticHistogramme.o CGeneticHistogramme2.o CHistogramme.o CIndividuHistogramme.o CIndividuHistogramme2.o CIndividuDigest.o CGeneticDigest.o
	$(CC) -o $@ $(LDFLAGS) $^

%.o: %.cpp
	$(CC) -o $@ $(CFLAGS) -c $<

clean:
	rm -f $(ALL)
	rm -f *.o
