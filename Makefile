all::

TARGET := gig
EXECUTABLE_SUFFIX :=

CFLAGS = -g -Wall
LDFLAGS =

CC = cc
RM = rm -f

LIB_H += commands.h

PREFIX = src
COMMAND_PREFIX = $(PREFIX)/commands

BUILD_PREFIX = build
COMMAND_BUILD_PREFIX = $(BUILD_PREFIX)/commands

all:: $(BUILD_PREFIX)/$(TARGET)$(EXECUTABLE_SUFFIX)

$(BUILD_PREFIX):
	mkdir -p $@

$(BUILD_PREFIX)/%.o: $(PREFIX)/%.c
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $(LDFLAGS) -o $@ $<

$(BUILD_PREFIX)/$(TARGET)$(EXECUTABLE_SUFFIX): $(BUILD_PREFIX)/$(TARGET).o $(addprefix $(COMMAND_BUILD_PREFIX)/,$(COMMAND_OBJS))
	$(CC) $(CFLAGS) $(LDFLAGS) -o $(BUILD_PREFIX)/$(TARGET) $(filter $(BUILD_PREFIX)/%.o,$^)

.PHONY: clean
clean:
	# Erasing all *.o files in $(BUILD_PREFIX)/
	$(RM) $(BUILD_PREFIX)/*.o
	$(RM) $(COMMAND_BUILD_PREFIX)/*.o
	$(RM) $(BUILD_PREFIX)/$(TARGET)$(EXECUTABLE_SUFFIX)