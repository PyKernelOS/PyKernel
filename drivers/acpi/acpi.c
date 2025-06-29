#include "acpi.h"
#include <string.h>
#include <stddef.h>

static struct RSDPDescriptor* rsdp = NULL;
static struct SDTHeader* xsdt = NULL;
static struct FADT* fadt = NULL;

void* acpi_find_rsdp() {
    for (uint64_t addr = 0x000E0000; addr < 0x00100000; addr += 16) {
        if (memcmp((char*)addr, "RSD PTR ", 8) == 0) {
            rsdp = (struct RSDPDescriptor*)addr;
            return rsdp;
        }
    }
    return NULL;
}

static struct SDTHeader* acpi_find_table(const char* sig) {
    if (!rsdp) acpi_find_rsdp();
    xsdt = (struct SDTHeader*)(uintptr_t)rsdp->XsdtAddress;
    uint32_t entries = (xsdt->Length - sizeof(struct SDTHeader)) / 8;
    uint64_t* table_ptrs = (uint64_t*)(xsdt + 1);
    for (uint32_t i = 0; i < entries; i++) {
        struct SDTHeader* hdr = (struct SDTHeader*)(uintptr_t)table_ptrs[i];
        if (memcmp(hdr->Signature, sig, 4) == 0) {
            return hdr;
        }
    }
    return NULL;
}

void acpi_parse_xsdt() {
    fadt = (struct FADT*)acpi_find_table("FACP");
}

void acpi_shutdown() {
    if (!fadt) acpi_parse_xsdt();
    uint8_t* dsdt = (uint8_t*)(uintptr_t)fadt->Dsdt;
    uint32_t dsdt_len = ((struct SDTHeader*)dsdt)->Length;

    for (uint32_t i = 0; i < dsdt_len - 4; i++) {
        if (memcmp(dsdt + i, "_S5_", 4) == 0) {
            if (dsdt[i - 1] == 0x08 || dsdt[i - 2] == 0x08) {
                uint8_t slp_typa = dsdt[i+5] & 0x7;
                uint8_t slp_typb = dsdt[i+6] & 0x7;
                uint16_t SLP_EN = 1 << 13;

                outw(fadt->PM1a_CNT_BLK, (slp_typa << 10) | SLP_EN);
                while (1) __asm__ volatile("hlt");
            }
        }
    }
}