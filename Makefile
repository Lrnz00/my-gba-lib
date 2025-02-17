CC		:=	gcc
CC_PREFIX	:=	arm-none-eabi-
ARCH		:=	-mthumb -mthumb-interwork
CFLAGS		:= 	-g -Wall -O2\
			-mcpu=arm7tdmi -mtune=arm7tdmi\
			$(ARCH)

BIN_NAME 	:=	mygbalib
DIR_BIN		:=	bin
DIR_BUILD	:=	build
DIR_SOURCES	:=	src
DIR_HEADERS	:=	include

SOURCES		:=	$(wildcard $(DIR_SOURCES)/*.c)
HEADERS		:=	$(wildcard $(DIR_HEADERS)/*.h)
OBJECTS		:=	$(patsubst $(DIR_SOURCES)/%.c,$(DIR_BUILD)/%.o,$(SOURCES))


all: $(DIR_BIN)/$(BIN_NAME)

$(DIR_BIN)/$(BIN_NAME): $(DIR_BUILD)/$(OBJ_FILES)
	mkdir $(DIR_BIN)
	rm -f $@
	ar -crs $@.a $(OBJECTS)

$(DIR_BUILD)/$(OBJ_FILES): $(SOURCES) $(HEADERS)
	mkdir $(DIR_BUILD)
	$(CC_PREFIX)$(CC) $(CFLAGS) -I$(DIR_HEADERS) $(SOURCES) -c
	mv *.o $(DIR_BUILD)

clean:
	rm -rf $(DIR_BUILD)/ $(DIR_BIN)/
