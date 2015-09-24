LDFLAGS = -lasound

all: play record

play: lplay.o sndwav_common.o wav_parser.o
	cc -o play lplay.o sndwav_common.o wav_parser.o $(LDFLAGS)

record: lrecord.o sndwav_common.o wav_parser.o
	cc -o record lrecord.o sndwav_common.o wav_parser.o $(LDFLAGS)

clean:
	rm -rf play record *.o
