#include "sha2.h"

#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <inttypes.h>

const unsigned char plaintext[113] = "abcdefghbcdefghicdefghijdefghijkefghijklfghijklmghijklmnhijklmnoijklmnopjklmnopqklmnopqrlmnopqrsmnopqrstnopqrstu";

const unsigned char plaintext2[128] = {
    0xfd, 0x22, 0x03, 0xe4, 0x67, 0x57, 0x4e, 0x83, 0x4a, 0xb0, 0x7c, 0x90,
    0x97, 0xae, 0x16, 0x45, 0x32, 0xf2, 0x4b, 0xe1, 0xeb, 0x5d, 0x88, 0xf1,
    0xaf, 0x77, 0x48, 0xce, 0xff, 0x0d, 0x2c, 0x67, 0xa2, 0x1f, 0x4e, 0x40,
    0x97, 0xf9, 0xd3, 0xbb, 0x4e, 0x9f, 0xbf, 0x97, 0x18, 0x6e, 0x0d, 0xb6,
    0xdb, 0x01, 0x00, 0x23, 0x0a, 0x52, 0xb4, 0x53, 0xd4, 0x21, 0xf8, 0xab,
    0x9c, 0x9a, 0x60, 0x43, 0xaa, 0x32, 0x95, 0xea, 0x20, 0xd2, 0xf0, 0x6a,
    0x2f, 0x37, 0x47, 0x0d, 0x8a, 0x99, 0x07, 0x5f, 0x1b, 0x8a, 0x83, 0x36,
    0xf6, 0x22, 0x8c, 0xf0, 0x8b, 0x59, 0x42, 0xfc, 0x1f, 0xb4, 0x29, 0x9c,
    0x7d, 0x24, 0x80, 0xe8, 0xe8, 0x2b, 0xce, 0x17, 0x55, 0x40, 0xbd, 0xfa,
    0xd7, 0x75, 0x2b, 0xc9, 0x5b, 0x57, 0x7f, 0x22, 0x95, 0x15, 0x39, 0x4f,
    0x3a, 0xe5, 0xce, 0xc8, 0x70, 0xa4, 0xb2, 0xf8
};

const unsigned char expected_224[28] = {
    0xc9, 0x7c, 0xa9, 0xa5, 0x59, 0x85, 0x0c, 0xe9, 0x7a, 0x04, 0xa9, 0x6d,
    0xef, 0x6d, 0x99, 0xa9, 0xe0, 0xe0, 0xe2, 0xab, 0x14, 0xe6, 0xb8, 0xdf,
    0x26, 0x5f, 0xc0, 0xb3
};

const unsigned char expected_256[32] = {
    0xcf, 0x5b, 0x16, 0xa7, 0x78, 0xaf, 0x83, 0x80, 0x03, 0x6c, 0xe5, 0x9e,
    0x7b, 0x04, 0x92, 0x37, 0x0b, 0x24, 0x9b, 0x11, 0xe8, 0xf0, 0x7a, 0x51,
    0xaf, 0xac, 0x45, 0x03, 0x7a, 0xfe, 0xe9, 0xd1
};

const unsigned char expected_384[48] = {
    0x09, 0x33, 0x0c, 0x33, 0xf7, 0x11, 0x47, 0xe8, 0x3d, 0x19, 0x2f, 0xc7,
    0x82, 0xcd, 0x1b, 0x47, 0x53, 0x11, 0x1b, 0x17, 0x3b, 0x3b, 0x05, 0xd2,
    0x2f, 0xa0, 0x80, 0x86, 0xe3, 0xb0, 0xf7, 0x12, 0xfc, 0xc7, 0xc7, 0x1a,
    0x55, 0x7e, 0x2d, 0xb9, 0x66, 0xc3, 0xe9, 0xfa, 0x91, 0x74, 0x60, 0x39
};

const unsigned char expected_512[64] = {
    0x8e, 0x95, 0x9b, 0x75, 0xda, 0xe3, 0x13, 0xda, 0x8c, 0xf4, 0xf7, 0x28,
    0x14, 0xfc, 0x14, 0x3f, 0x8f, 0x77, 0x79, 0xc6, 0xeb, 0x9f, 0x7f, 0xa1,
    0x72, 0x99, 0xae, 0xad, 0xb6, 0x88, 0x90, 0x18, 0x50, 0x1d, 0x28, 0x9e,
    0x49, 0x00, 0xf7, 0xe4, 0x33, 0x1b, 0x99, 0xde, 0xc4, 0xb5, 0x43, 0x3a,
    0xc7, 0xd3, 0x29, 0xee, 0xb6, 0xdd, 0x26, 0x54, 0x5e, 0x96, 0xe5, 0x5b,
    0x87, 0x4b, 0xe9, 0x09
};
const unsigned char expected_512_2[64] = {
    0xa2, 0x1b, 0x10, 0x77, 0xd5, 0x2b, 0x27, 0xac, 0x54, 0x5a, 0xf6, 0x3b,
    0x32, 0x74, 0x6c, 0x6e, 0x3c, 0x51, 0xcb, 0x0c, 0xb9, 0xf2, 0x81, 0xeb,
    0x9f, 0x35, 0x80, 0xa6, 0xd4, 0x99, 0x6d, 0x5c, 0x99, 0x17, 0xd2, 0xa6,
    0xe4, 0x84, 0x62, 0x7a, 0x9d, 0x5a, 0x06, 0xfa, 0x1b, 0x25, 0x32, 0x7a,
    0x9d, 0x71, 0x0e, 0x02, 0x73, 0x87, 0xfc, 0x3e, 0x07, 0xd7, 0xc4, 0xd1,
    0x4c, 0x60, 0x86, 0xcc
};

static int test_sha256_incremental(void) {
    unsigned char output[32];
    sha256ctx state;
    int i = 0;

    sha256_inc_init(&state);
    sha256_inc_blocks(&state, plaintext, 1);
    sha256_inc_finalize(output, &state, plaintext + 64, 112 - 64);

    if (memcmp(expected_256, output, 32) != 0) {
        printf("ERROR sha256 incremental did not match sha256.\n");
        printf("  Expected: ");
        for (i = 0; i < 32; i++) {
            printf("%02X", expected_256[i]);
        }
        printf("\n");
        printf("  Received: ");
        for (i = 0; i < 32; i++) {
            printf("%02X", output[i]);
        }
        printf("\n");
        return 1;
    }

    return 0;
}

static int test_sha512_incremental(void) {
    unsigned char output[64];
    sha512ctx state;
    int i = 0;

    sha512_inc_init(&state);
    sha512_inc_blocks(&state, plaintext2, 1);
    sha512_inc_finalize(output, &state, NULL, 0);
    if (memcmp(expected_512_2, output, 64) != 0) {
        printf("ERROR sha512 incremental output did not match test vector.\n");
        printf("Expected: ");
        for (i = 0; i < 64; i++) {
            printf("%02X", expected_512[i]);
        }
        printf("\n");
        printf("Received: ");
        for (i = 0; i < 64; i++) {
            printf("%02X", output[i]);
        }
        printf("\n");
        return 1;
    }
    return 0;
}

static int test_sha224(void) {
    unsigned char output[28];
    int i = 0;

    sha224(output, plaintext, 112);

    if (memcmp(expected_224, output, 28) != 0) {
        printf("ERROR sha224 output did not match test vector.\n");
        printf("Expected: ");
        for (i = 0; i < 28; i++) {
            printf("%02X", expected_224[i]);
        }
        printf("\n");
        printf("Received: ");
        for (i = 0; i < 28; i++) {
            printf("%02X", output[i]);
        }
        printf("\n");
        return 1;
    }

    return 0;
}

static int test_sha256(void) {
    unsigned char output[32];
    int i = 0;

    sha256(output, plaintext, 112);

    if (memcmp(expected_256, output, 32) != 0) {
        printf("ERROR sha256 output did not match test vector.\n");
        printf("Expected: ");
        for (i = 0; i < 32; i++) {
            printf("%02X", expected_256[i]);
        }
        printf("\n");
        printf("Received: ");
        for (i = 0; i < 32; i++) {
            printf("%02X", output[i]);
        }
        printf("\n");
        return 1;
    }

    return 0;
}

static int test_sha384(void) {
    unsigned char output[48];
    int i = 0;

    sha384(output, plaintext, 112);

    if (memcmp(expected_384, output, 48) != 0) {
        printf("ERROR sha384 output did not match test vector.\n");
        printf("Expected: ");
        for (i = 0; i < 48; i++) {
            printf("%02X", expected_384[i]);
        }
        printf("\n");
        printf("Received: ");
        for (i = 0; i < 48; i++) {
            printf("%02X", output[i]);
        }
        printf("\n");
        return 1;
    }

    return 0;
}

static int test_sha512(void) {
    unsigned char output[64];
    int i = 0;

    sha512(output, plaintext, 112);

    if (memcmp(expected_512, output, 64) != 0) {
        printf("ERROR sha512 output did not match test vector.\n");
        printf("Expected: ");
        for (i = 0; i < 64; i++) {
            printf("%02X", expected_512[i]);
        }
        printf("\n");
        printf("Received: ");
        for (i = 0; i < 64; i++) {
            printf("%02X", output[i]);
        }
        printf("\n");
        return 1;
    }

    return 0;
}

int main(void) {
    int result = 0;
    result += test_sha224();
    result += test_sha256();
    result += test_sha256_incremental();
    result += test_sha384();
    result += test_sha512();
    result += test_sha512_incremental();

    if (result != 0) {
        puts("Errors occurred");
    }
    return result;
}
