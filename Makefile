CXX = g++
IDIR = -I. -I.. -I./src -I/usr/local/include -I/usr/include -I/usr/local/include/mysql++ -I/usr/include/mysql++ -I/usr/local/include/mysql -I/usr/include/mysql
LDIR = -L. -L/usr/lib -L/usr/local/lib
LIB = -lpqxx -lpthread -lconfig++ /usr/lib/libcgi.a -lcgi -lhl++ -lcurl
#-lpqxx -lmysqlpp
FLAGS = -pipe -Wall -O2 -DPOSTGRESQL
# FLAGS = -pipe -O2 -ggdb -DMYSQL
#FLAGS = -march=prescott -mtune=prescott -pipe -Wall -O3 -DPOSTGRESQL
DESTDIR = out
DEPLOY_DIR = <Your dir>

INSTALL = install
INSTALL_PROGRAM = ${INSTALL}
INSTALL_DATA = ${INSTALL} -m 644

COMPRESS_DATA = java -jar tools/yuicompressor-2.3.5.jar

all: index.cgi scrape.cgi

src/config.o: src/config.cpp src/config.hpp
	$(CXX) -c src/config.cpp -o src/config.o $(FLAGS) $(IDIR)

src/main.o: src/main.cpp src/main.hpp src/config.hpp
	$(CXX) -c src/main.cpp -o src/main.o $(FLAGS) $(IDIR)
	
src/index.o: src/index.cpp src/config.hpp
	$(CXX) -c src/index.cpp -o src/index.o $(FLAGS) $(IDIR)
	
# sql.o: db/MySQL.cpp config.hpp
# 	$(CXX) -c db/MySQL.cpp -o sql.o $(FLAGS) $(IDIR)

src/sql.o: src/db/PostgreSQL.cpp src/config.hpp
	$(CXX) -c src/db/PostgreSQL.cpp -o src/sql.o $(FLAGS) $(IDIR)

index.cgi: src/main.o src/index.o src/sql.o src/config.o
	$(CXX) src/config.o src/main.o src/index.o src/sql.o -o src/index.cgi $(FLAGS) $(LIB) $(LDIR)

src/scrape/bencode.o: src/scrape/bencode.cpp src/scrape/bencode.hpp src/scrape/config.hpp
	$(CXX) -c src/scrape/bencode.cpp -o src/scrape/bencode.o $(FLAGS) $(IDIR)

src/scrape/scrape.o: src/scrape/scrape.cpp src/scrape/config.hpp
	$(CXX) -c src/scrape/scrape.cpp -o src/scrape/scrape.o $(FLAGS) $(IDIR)

scrape.cgi: src/scrape/scrape.o src/scrape/bencode.o
	$(CXX) src/scrape/scrape.o src/scrape/bencode.o -o src/scrape/scrape.cgi $(FLAGS) $(LIB) $(LDIR)
	
clean:
	rm -f src/*.o
	rm -f src/scrape/*.o
	rm -f src/index.cgi
	rm -f src/scrape/scrape.cgi
	rm -rf out

install:
	mkdir -p $(DESTDIR)/{bin,www/cgi,template,tmp}
	chmod 777 $(DESTDIR)/tmp
	
	for i in cgi/*.cgi; \
		do $(INSTALL_PROGRAM) $$i $(DESTDIR)/www/cgi; \
	done
	
	$(INSTALL_PROGRAM) src/index.cgi  $(DESTDIR)/bin/site
	$(INSTALL_PROGRAM) src/scrape/scrape.cgi  $(DESTDIR)/bin/scrape
	
	# Install static data
	$(INSTALL_DATA) static/.htaccess $(DESTDIR)/www
	$(INSTALL_DATA) static/500.xhtml $(DESTDIR)/www
	$(INSTALL_DATA) static/robots.txt $(DESTDIR)/www
	$(INSTALL_DATA) static/config.cfg $(DESTDIR)
	
	# Install template
	$(INSTALL_DATA) static/content.xsl $(DESTDIR)/template
	$(INSTALL_DATA) static/xsl.xsl $(DESTDIR)/template
	$(INSTALL_DATA) static/rss.xsl $(DESTDIR)/template
	
	# Compress CSS
	$(INSTALL_DATA) static/style.css $(DESTDIR)/www
	echo Compressing style.css with YUI Compress
	$(COMPRESS_DATA) static/style.css -o $(DESTDIR)/www/style.css
	echo Compressing style.css with gzip
	gzip -c static/style.css  > $(DESTDIR)/www/style.css.gz
	
	# Compress JavaScript
	cp -R static/js $(DESTDIR)/www
	cd $(DESTDIR)/www && for i in `find js -iname '*.js'`; \
		do \
			echo "Compressing" $$i "with YUI Compress"; \
			java -jar ../../tools/yuicompressor-2.3.5.jar `pwd`/$$i -o `pwd`/$$i; \
			echo "Compressing" $$i "with gzip"; \
			gzip -c `pwd`/$$i  > `pwd`/$$i.gz; \
		done

	ln -sf ../../images $(DESTDIR)/www/images
	
	# Install site
	cp -pR out/* $(DEPLOY_DIR)
