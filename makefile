CC=clang
LDLIBS=-lbluetooth

ALL: pbap_client README.html

README.html: README.md
	markdown README.md > README.html

clean:
	rm -f README.html
	rm -f pbap_client
