#ifndef PROTO_H
#define PROTO_H

#include <stdint.h>

typedef union _HeaderFlags {
    uint32_t u32;
    struct _S{
        uint32_t Flag1: 1;
        uint32_t Flag2: 1;
        uint32_t Reserved: 30;
    } S;
} HeaderFlags;

constexpr uint32_t HeaderLength = sizeof(uint32_t) + sizeof(uint32_t) + sizeof(HeaderFlags);
constexpr uint32_t DataLength = 1024;
constexpr uint32_t PackageLength = HeaderLength + DataLength;

// typedef struct _S{
//     uint32_t Preamble;
//     uint32_t Length = PackageLength;
//     // HeaderFlags Flags;
// } S;

typedef union _Header {
    uint8_t u8[HeaderLength];
    uint32_t u32[HeaderLength/4];
    // S s;
    // struct {
    //     uint32_t Preamble;
    //     uint32_t Length = PackageLength;
    //     // HeaderFlags Flags;
    // };
} Header;

typedef union _Data {
    uint8_t u8[DataLength];
    uint32_t u32[DataLength/4];
} Data;

typedef struct _S{
    Header header;
    Data data;
} S;

typedef union _Package {
    uint8_t u8[PackageLength];
    // S s;
} Package;

#endif

