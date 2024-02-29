PRJ = HyperLCA
CC = icpx

SRCS  = Main_Compresor_HW.cpp HyperLCA_Transform_Operations.cpp
OBJS = $(SRCS:.c=.o)


CFLAGS += -g -Wall -O1
CPPFLAGS += -fopenmp
LDFLAGS += -D VERBOSE -D BLOCK_DBG=1 


all : $(PRJ)

%.o : %.c
	$(CC) $(CFLAGS) $(CPPFLAGS) -c $^

$(PRJ): $(OBJS)
	$(CC) $(CPPFLAGS) $(LDFLAGS) $^ -o $@

mission.bin:
	megadl 'https://mega.nz/file/Z5JUkSoI#boptGx0TD4YU1FGz5WxVkxgB0-fav1sQiVVCk2lz_CA'

run: $(PRJ) mission.bin
	./$(PRJ)


clean:
	$(RM) -rf $(PRJ) *~ *.o compressedBitstream.bin output

cleanall: clean
	$(RM) -rf mission.bin
