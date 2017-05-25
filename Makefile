ifdef LOCAL
AISDI_DIR = .
CCFLAGS = --std=c++11 -DAISDI_LOCAL
else
AISDI_DIR = /materialy/AISDI/liniowe2015
CCFLAGS = --std=c++11
endif

SOURCES = \
	ListMap.cpp \
	$(AISDI_DIR)/main.cpp \
	$(AISDI_DIR)/tests/tests.cpp

all: linear

linear: ListMap.cpp
	g++ $(CCFLAGS) $(SOURCES) -o linear

validate: linear
	echo "Executing tests"
	./linear

verify: validate
	echo "Verification OK"

clean:
	rm linear

debug: ListMap.cpp
	g++ $(CCFLAGS) -g -O0 $(SOURCES) -o linear_debug
	gdb linear_debug
