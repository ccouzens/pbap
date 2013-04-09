CC=clang
CFLAGS=-g
LDLIBS=-lbluetooth

ALL: local_scan README.html

README.html: README.md
	markdown README.md > README.html

clean:
	rm -f README.html
	rm -f local_scan
