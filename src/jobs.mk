
# compiler include search paths
INCS = \
	-I../../boost/boost1_72 \
	-I../../raven-set \
	-I../../entityDB/src \
	-I../../windex/include

WEXLIBS = \
	-lstdc++fs -lgdiplus -lgdi32 -lcomdlg32

SDIR = ../../src
ODIR = ../obj

OPT = -g
CCflags = -std=c++17 $(OPT)
STATLibs = -static-libstdc++ -static-libgcc -static

### OBJECT FILES

OBJ = $(ODIR)/jobs.o $(ODIR)/entitydb.o \
	$(ODIR)/raven_sqlite.o $(ODIR)/sqlite3.o

### COMPILE

$(ODIR)/jobs.o : jobs.cpp
	g++ -o  $@ -c jobs.cpp $(INCS) $(CCflags)

$(ODIR)/entitydb.o :
	g++ -o  $@ -c ../../entityDB/src/entitydb.cpp $(INCS) $(CCflags)

$(ODIR)/raven_sqlite.o :
	g++ -o  $@ -c ../../raven-set/raven_sqlite.cpp $(INCS) $(CCflags)

$(ODIR)/sqlite3.o : 
	gcc	 -o $@ -c ../../sqlite/sqlite3.c

#### LINKS

jobs : $(OBJ)
	g++ -o ../bin/jobs.exe \
		$(OBJ) $(WEXLIBS) $(STATLibs) $(OPT)

### CLEAN

.PHONY: clean
clean:
	del /q ..\obj