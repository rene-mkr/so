#include <stdint.h>

///
/// MBR Partition Entry
///

// No hagas cosas raras (en aras de optimizar)

#pragma pack(push,1)

typedef struct {
   uint8_t         BootIndicator;
   uint8_t         StartHead;
   uint8_t         StartSector;
   uint8_t         StartTrack;
   uint8_t         OSIndicator;
   uint8_t         EndHead;
   uint8_t         EndSector;
   uint8_t         EndTrack;
   uint32_t         StartingLBA;
   uint32_t         SizeInLBA;
}    MBR_PARTITION_RECORD;

///
/// MBR Partition Table
///
typedef struct {
   uint8_t         BootStrapCode[440];
   uint8_t         UniqueMbrSignature[4];
   uint8_t         Unknown[2];
   MBR_PARTITION_RECORD Partition[4];
   uint16_t        Signature;
} MASTER_BOOT_RECORD;

#pragma pack(pop)
