#include "finder_info.h"

#define BIG_ENDIAN_SHORT(n) ((UInt16) (((n & 0xFF) << 8) | \
                                            ((n & 0xFF00) >> 8)))
#define BIG_ENDIAN_LONG(n) ((UInt32) (((n & 0xFF) << 24) | \
                                          ((n & 0xFF00) << 8) | \
                                          ((n & 0xFF0000) >> 8) | \
                                          ((n & 0xFF000000) >> 24)))
#define BIG_ENDIAN_LONGLONG(n) ((UInt64) (BIG_ENDIAN_LONG(n >> 32) | \
                                ((UInt64) BIG_ENDIAN_LONG(n & 0xFFFFFFFF)) << 32))

#pragma pack(push,1)

struct hfs_extent {
	SInt16 block;
	SInt16 count;
};
typedef struct hfs_extent hfs_extent_rec[3];

struct hfs_mdb {
	SInt16 drSigWord;		/* Signature word indicating fs type */
	SInt32 drCrDate;		/* fs creation date/time */
	SInt32 drLsMod;			/* fs modification date/time */
	SInt16 drAtrb;			/* fs attributes */
	SInt16 drNmFls;			/* number of files in root directory */
	SInt16 drVBMSt;			/* location (in 512-byte blocks)
					   of the volume bitmap */
	SInt16 drAllocPtr;		/* location (in allocation blocks)
					   to begin next allocation search */
	SInt16 drNmAlBlks;		/* number of allocation blocks */
	SInt32 drAlBlkSiz;		/* bytes in an allocation block */
	SInt32 drClpSiz;		/* clumpsize, the number of bytes to
					   allocate when extending a file */
	SInt16 drAlBlSt;		/* location (in 512-byte blocks)
					   of the first allocation block */
	SInt32 drNxtCNID;		/* CNID to assign to the next
					   file or directory created */
	SInt16 drFreeBks;		/* number of free allocation blocks */
	char drVN[28];			/* the volume label */
	SInt32 drVolBkUp;		/* fs backup date/time */
	SInt16 drVSeqNum;		/* backup sequence number */
	SInt32 drWrCnt;			/* fs write count */
	SInt32 drXTClpSiz;		/* clumpsize for the extents B-tree */
	SInt32 drCTClpSiz;		/* clumpsize for the catalog B-tree */
	SInt16 drNmRtDirs;		/* number of directories in
					   the root directory */
	SInt32 drFilCnt;		/* number of files in the fs */
	SInt32 drDirCnt;		/* number of directories in the fs */
	SInt32 drFndrInfo[8];		/* data used by the Finder */
	SInt16 drVCSize;		/* size (in blocks) of volume cache */
    SInt16 drVBMCSize;    /* size (in blocks) of volume bitmap cache */
    SInt16 drCtlCSize;    /* size (in blocks) of common volume cache */
	SInt32 drXTFlSize;    /* size of extents overflow file */
    hfs_extent_rec drXTExtRec; /* extent record for extents overflow file */
    SInt32 drCTFlSize;    /* size of catalog file */
    hfs_extent_rec drCTExtRec; /* extent record for catalog file */
};

typedef struct hfs_mdb hfs_mdb;

struct BTNodeDescriptor {
    UInt32    fLink;
    UInt32    bLink;
    SInt8     kind;
    UInt8     height;
    UInt16    numRecords;
    UInt16    reserved;
};
typedef struct BTNodeDescriptor BTNodeDescriptor;

struct BTHeaderRec {
    UInt16    treeDepth;
    UInt32    rootNode;
    UInt32    leafRecords;
    UInt32    firstLeafNode;
    UInt32    lastLeafNode;
    UInt16    nodeSize;
    UInt16    maxKeyLength;
    UInt32    totalNodes;
    UInt32    freeNodes;
    UInt16    reserved1;
    UInt32    clumpSize;      // misaligned
    UInt8     btreeType;
    UInt8     keyCompareType;
    UInt32    attributes;     // long aligned again
    UInt32    reserved3[16];
};
typedef struct BTHeaderRec BTHeaderRec;

#pragma pack(pop)


