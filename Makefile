SOURCES = test/dsm2_tx.test.cpp libraries/dsm2_tx/dsm2_tx.cpp ../../arduino-1.0.1/hardware/arduino/cores/arduino/WMath.cpp
CPPFLAGS = -Ilibraries/dsm2_tx -Itest -D_TEST_ -I../../arduino-1.0.1/hardware/arduino/cores/arduino
OBJECTS := $(addsuffix .o, $(basename $(SOURCES)))

all: runtest

$(OBJECTS): $(SOURCES)
runtest: $(OBJECTS)
	$(CC) $(OBJECTS) -lstdc++ -o $@
