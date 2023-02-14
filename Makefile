
# TODO: cross compile!
#
#
#CC=g++
CFLAGS=-g -static

all: build_dir udp_server fs

build_dir:
	mkdir -p build

udp_server: src/udp_server.cpp
	$(CC) -o build/udp_server $^ $(CFLAGS)

fs:
	rm -rf image
	mkdir image
	cp src/init.sh  image/init
	chmod +x image/init
	mkdir image/bin
	cp build/* image/bin
	tar cvfz image.tar.gz -C image .

clean:
	rm -f *.o *.so *.d
	rm -rf build image

.PHONY: all clean
