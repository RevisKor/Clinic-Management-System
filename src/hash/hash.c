#include "../../include/hash/hash.h"

// SHA-256 internal bit-manipulation macros. Kept private to this file since
// nothing outside Hash_Password needs them.
#define CH(x, y, z) (((x) & (y)) ^ (~(x) & (z)))
#define MAJ(x, y, z) (((x) & (y)) ^ ((x) & (z)) ^ ((y) & (z)))
#define ROTR(x, n) (((x) >> (n)) | ((x) << (32 - (n))))
#define SIG0(x) (ROTR(x, 2) ^ ROTR(x, 13) ^ ROTR(x, 22))
#define SIG1(x) (ROTR(x, 6) ^ ROTR(x, 11) ^ ROTR(x, 25))
#define sig0(x) (ROTR(x, 7) ^ ROTR(x, 18) ^ ((x) >> 3))
#define sig1(x) (ROTR(x, 17) ^ ROTR(x, 19) ^ ((x) >> 10))

// Standard SHA-256 round constants.
static const uint32_t RoundConstants[64] = {
    0x428a2f98, 0x71374491, 0xb5c0fbcf, 0xe9b5dba5, 0x3956c25b, 0x59f111f1, 0x923f82a4, 0xab1c5ed5,
    0xd807aa98, 0x12835b01, 0x243185be, 0x550c7dc3, 0x72be5d74, 0x80deb1fe, 0x9bdc06a7, 0xc19bf174,
    0xe49b69c1, 0xefbe4786, 0x0fc19dc6, 0x240ca1cc, 0x2de92c6f, 0x4a7484aa, 0x5cb0a9dc, 0x76f988da,
    0x983e5152, 0xa831c66d, 0xb00327c8, 0xbf597fc7, 0xc6e00bf3, 0xd5a79147, 0x06ca6351, 0x14292967,
    0x27b70a85, 0x2e1b2138, 0x4d2c6dfc, 0x53380d13, 0x650a7354, 0x766a0abb, 0x81c2c92e, 0x92722c85,
    0xa2bfe8a1, 0xa81a664b, 0xc24b8b70, 0xc76c51a3, 0xd192e819, 0xd6990624, 0xf40e3585, 0x106aa070,
    0x19a4c116, 0x1e376c08, 0x2748774c, 0x34b0bcb5, 0x391c0cb3, 0x4ed8aa4a, 0x5b9cca4f, 0x682e6ff3,
    0x748f82ee, 0x78a5636f, 0x84c87814, 0x8cc70208, 0x90befffa, 0xa4506ceb, 0xbef9a3f7, 0xc67178f2
};

void Hash_Password(const u8* password, u8* outputHash) {
    // NOTE: h0-h7, a-h, t1, t2, W[] and RoundConstants stay uint32_t (not u32)
    // on purpose. SHA-256 needs true 32-bit wraparound arithmetic, and u32 is
    // "unsigned long int" - 8 bytes on this platform, not 4 - so using it here
    // would silently change every hash this function produces.
    uint32_t h0 = 0x6a09e667, h1 = 0xbb67ae85, h2 = 0x3c6ef372, h3 = 0xa54ff53a;
    uint32_t h4 = 0x510e527f, h5 = 0x9b05688c, h6 = 0x1f83d9ab, h7 = 0x5be0cd19;

    u64 passwordLength = strlen((const char*) password);
    u64 bitLength = passwordLength * 8;

    // Single-block message schedule: fine here because every password this
    // project accepts (max 16 chars, see Validate_CheckInputLength) fits in
    // one 512-bit SHA-256 block with room to spare for padding.
    u8 message[128] = {0};
    memcpy(message, password, passwordLength);

    // Pad the message per the SHA-256 specification.
    message[passwordLength] = 0x80;
    message[63] = (u8) bitLength;
    message[62] = (u8) (bitLength >> 8);

    uint32_t messageSchedule[64];
    for (s32 t = 0; t < 16; t++) {
        messageSchedule[t] = ((uint32_t) message[t * 4] << 24)
                            | ((uint32_t) message[t * 4 + 1] << 16)
                            | ((uint32_t) message[t * 4 + 2] << 8)
                            | ((uint32_t) message[t * 4 + 3]);
    }
    for (s32 t = 16; t < 64; t++) {
        messageSchedule[t] = sig1(messageSchedule[t - 2]) + messageSchedule[t - 7]
                            + sig0(messageSchedule[t - 15]) + messageSchedule[t - 16];
    }

    uint32_t a = h0, b = h1, c = h2, d = h3, e = h4, f = h5, g = h6, h = h7;

    for (s32 t = 0; t < 64; t++) {
        uint32_t t1 = h + SIG1(e) + CH(e, f, g) + RoundConstants[t] + messageSchedule[t];
        uint32_t t2 = SIG0(a) + MAJ(a, b, c);
        h = g; g = f; f = e; e = d + t1; d = c; c = b; b = a; a = t1 + t2;
    }

    h0 += a; h1 += b; h2 += c; h3 += d; h4 += e; h5 += f; h6 += g; h7 += h;

    // Render the eight 32-bit words as a 64-character lowercase hex string.
    sprintf((char*) outputHash, "%08x%08x%08x%08x%08x%08x%08x%08x", h0, h1, h2, h3, h4, h5, h6, h7);
}
