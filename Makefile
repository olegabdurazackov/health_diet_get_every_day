TARGET = diet
CHILD  = int3char
LIB    = charint
ESCP   = escape
DB     = kkal.db
CC     = g++
$(TARGET): $(ESCP).h $(LIB).h $(LIB).cpp $(CHILD).h $(CHILD).cpp main.cpp
	$(CC) -o $(TARGET) $(ESCP).h $(LIB).h $(LIB).cpp $(CHILD).h $(CHILD).cpp main.cpp -lsqlite3

install: $(TARGET)
	mkdir /usr/local/share/$(TARGET)/
	cp $(TARGET) /usr/local/bin/
	cp $(DB) /usr/local/share/$(TARGET)/

uninstall: $(TARGET)
	rm /usr/local/bin/$(TARGET)
	rm /usr/local/share/$(TARGET)/$(DB)
	rmdir /usr/local/share/$(TARGET)/
clear:
	rm *.o
	
