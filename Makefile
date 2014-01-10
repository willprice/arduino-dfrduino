SOURCES=DFRduino.cpp DFRduino.h

doc: Doxygen $(SOURCES)
	doxygen Doxygen

.PHONY: doc
