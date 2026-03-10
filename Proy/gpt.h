#include <stdint.h>

// No hagas cosas raras (en aras de optimizar)

#pragma pack(push,1)

struct gpt_guid
{
	uint8_t uuid;
};

struct gpt_header {
	uint64_t            signature; /* header identification */
	uint32_t            revision; /* header version */
	uint32_t            size; /* in bytes */
	uint32_t            crc32; /* header CRC checksum */
	uint32_t            reserved1; /* must be 0 */
	uint64_t            my_lba; /* LBA of block that contains this struct (LBA 1) */
	uint64_t            alternative_lba; /* backup GPT header */
	uint64_t            first_usable_lba; /* first usable logical block for partitions */
	uint64_t            last_usable_lba; /* last usable logical block for partitions */
	struct gpt_guid 	disk_guid; /* unique disk identifier */
	uint64_t            partition_entry_lba; /* LBA of start of partition entries array */
	uint32_t            npartition_entries; /* total partition entries - normally 128 */
	uint32_t            sizeof_partition_entry; /* bytes for each GUID pt */
	uint32_t            partition_entry_array_crc32; /* partition CRC checksum */
	uint8_t             reserved2[512 - 92]; /* must all be 0 */
};

///
/// GPT Partition Entry.
///
typedef struct
{
	struct gpt_guid PartitionTypeGUID;
	struct gpt_guid UniquePartitionGUID;
  	uint64_t 	    start;
  	uint64_t 	    end;
  	uint64_t 	    attrib;
	uint16_t        PartitionName[36]; // Nombre en UTF16
} efi_partition_entry;


#pragma pack(pop)
