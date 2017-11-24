TARGET	:= snake
SUBDIRS	:= main fun draw
OBJS	:= main/built-in.o fun/built-in.o draw/built-in.o

all: compile $(OBJS)
	$(CC) $(OBJS) -g -o $(TARGET) -lcurses

compile:
	@for dir in $(SUBDIRS); do \
	make -C $$dir || exit $?; \
	done

clean:
	@for dir in $(SUBDIRS); do \
	make -C $$dir clean; \
	done
	rm -rf *.o *.i *.s $(TARGET)

