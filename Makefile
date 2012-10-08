SOURCES = test/dsm2_tx-test.cpp \
          libraries/dsm2_tx/dsm2_tx.cpp \
          arduino/WMath.cpp

OBJECTS := $(addsuffix .o, $(addprefix .build/, $(basename $(SOURCES))))
DEPFILES := $(subst .o,.dep, $(subst .build/,.deps/, $(OBJECTS)))
TESTCPPFLAGS = -D_TEST_ -Ilibraries/dsm2_tx -Itest -Iarduino
CPPDEPFLAGS = -MMD -MP -MF .deps/$(basename $<).dep
RUNTEST := $(if $(COMSPEC), runtest.exe, runtest)

all: runtest

.build/%.o: %.cpp
	mkdir -p .deps/$(dir $<)
	mkdir -p .build/$(dir $<)
	$(COMPILE.cpp) $(TESTCPPFLAGS) $(CPPDEPFLAGS) -o $@ $<

runtest: $(OBJECTS)
	$(CC) $(OBJECTS) -lstdc++ -o $@

clean:
	@rm -rf .deps/ .build/ $(RUNTEST)

.PHONY: meh
meh:
	@echo $(DEPFILES)

-include $(DEPFILES)
