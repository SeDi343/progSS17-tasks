#-------------------------------------------------------------

TARGET   = greeter
SOURCES  = greeter_application.c
RESOURCE = greeter_res

#-------------------------------------------------------------

#-------------------------------------------------------------

CXX      = gcc
CXXFLAGS = `pkg-config --cflags --libs gtk+-3.0` -Wall -g
CPPFLAGS = -I.
LDFLAGS  = -lm

#-------------------------------------------------------------
# Rules
#
$(TARGET): $(SOURCES) $(RESOURCE).c
	$(CXX) $(SOURCES) $(RESOURCE).c $(LDFLAGS) $(CXXFLAGS) -o $(TARGET)

$(RESOURCE).c: $(RESOURCE).gresource.xml
	glib-compile-resources --sourcedir=. $(RESOURCE).gresource.xml --generate-source

.PHONY: clean
clean:
	@rm -rf $(OBJECTS) $(TARGET) core *~
	@rm -rf $(RESOURCE).c
