ALL: pbap_client README.html

README.html: README.md
	markdown README.md > README.html
