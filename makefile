CC=clang
CFLAGS=-g
LDLIBS=-lbluetooth

ALL: local_scan port_connect README.html

README.html: README.md
	markdown README.md > README.html

clean:
	rm -f README.html
	rm -f local_scan
	rm -f port_connect
