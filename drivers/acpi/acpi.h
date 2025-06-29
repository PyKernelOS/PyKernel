#pragma once
#include <stdint.h>

struct RSDPDescriptor {
    char Signature[8];     // "RSD PTR "
    uint8_t Checksum;
    char OEMID[6];
    uint8_t Revision;
    uint32_t RsdtAddress;
    uint32_t Length;
    uint64_t XsdtAddress;
    uint8_t ExtendedChecksum;
    uint8_t reserved[3];
} __attribute__((packed));

struct SDTHeader {
    char Signature[4];
    uint32_t Length;
    uint8_t Revision;
    uint8_t Checksum;
    char OEMID[6];
    char OEMTableID[8];
    uint32_t OEMRevision;
    uint32_t CreatorID;
    uint32_t CreatorRevision;
} __attribute__((packed));

struct FADT {
    struct SDTHeader h;
    uint32_t FirmwareCtrl;
    uint32_t Dsdt;
    // ... shortened for brevity
    uint8_t PM1a_CNT_BLK_space_id;
    uint32_t PM1a_CNT_BLK;
    // ...
} __attribute__((packed));

void* acpi_find_rsdp();
void acpi_parse_xsdt();
void acpi_shutdown();