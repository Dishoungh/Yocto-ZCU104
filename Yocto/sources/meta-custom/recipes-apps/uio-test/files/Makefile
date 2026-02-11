APP = uio-test

# Add any other object files to this list below
APP_OBJS = uio-test.o

all: build

# Add external libraries here

build: $(APP)

$(APP): $(APP_OBJS)
	$(CC) -o $@ $(APP_OBJS) $(LDFLAGS) $(LDLIBS)
clean:
	rm -f $(APP) *.o

