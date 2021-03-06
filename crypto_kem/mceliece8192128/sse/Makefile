# This Makefile can be used with GNU Make or BSD Make

LIB = libmceliece8192128_sse.a

SOURCES = aes256ctr.c benes.c bm.c controlbits.c decrypt.c encrypt.c fft.c \
		  fft_tr.c gf.c operations.c pk_gen.c sk_gen.c util.c vec128.c \
		  consts.S syndrome_asm.S transpose_64x128_sp_asm.S update_asm.S \
		  vec128_mul_asm.S vec_reduce_asm.S

HEADERS = aes256ctr.h api.h benes.h bm.h controlbits.h crypto_hash.h \
		  decrypt.h encrypt.h fft.h fft_tr.h gf.h params.h \
		  pk_gen.h sk_gen.h transpose.h util.h vec128.h \
		  consts.inc scalars_2x.inc scalars_4x.inc powers.inc

OBJECTS = aes256ctr.o benes.o bm.o controlbits.o decrypt.o encrypt.o fft.o \
		  fft_tr.o gf.o operations.o pk_gen.o sk_gen.o util.o vec128.o \
		  consts.o syndrome_asm.o transpose_64x128_sp_asm.o \
		  update_asm.o vec128_mul_asm.o vec_reduce_asm.o

CFLAGS  = -O3 -std=c99 -mpopcnt -msse4.1 -Wall -Wextra -pedantic -Werror -Wpedantic \
		  -Wredundant-decls -Wvla -Wcast-align -Wmissing-prototypes \
		  -I../../../common/ $(EXTRAFLAGS)

all: $(LIB)

%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS)   -c -o $@ $<

%.o: %.S
	$(CC) -c -o $@ $<

$(LIB): $(OBJECTS)
	$(AR) -r $@ $(OBJECTS)

clean:
	$(RM) $(OBJECTS)
	$(RM) $(LIB)
