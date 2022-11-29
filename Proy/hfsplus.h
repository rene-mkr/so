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

typedef UInt16 UniChar;
struct HFSUniStr255 {
    UInt16  length;
    UniChar unicode[255];
};
typedef struct HFSUniStr255 HFSUniStr255;
typedef const  HFSUniStr255 *ConstHFSUniStr255Param;

struct HFSPlusBSDInfo {
    UInt32  ownerID;
    UInt32  groupID;
    UInt8   adminFlags;
    UInt8   ownerFlags;
    UInt16  fileMode;
    union {
        UInt32  iNodeNum;
        UInt32  linkCount;
        UInt32  rawDevice;
    } special;
};
typedef struct HFSPlusBSDInfo HFSPlusBSDInfo;

#define S_ISUID 0004000     /* set user id on execution */
#define S_ISGID 0002000     /* set group id on execution */
// #define S_ISTXT 0001000     /* sticky bit */

#define S_IRWXU 0000700     /* RWX mask for owner */
#define S_IRUSR 0000400     /* R for owner */
#define S_IWUSR 0000200     /* W for owner */
#define S_IXUSR 0000100     /* X for owner */

#define S_IRWXG 0000070     /* RWX mask for group */
#define S_IRGRP 0000040     /* R for group */
#define S_IWGRP 0000020     /* W for group */
#define S_IXGRP 0000010     /* X for group */

#define S_IRWXO 0000007     /* RWX mask for other */
#define S_IROTH 0000004     /* R for other */
#define S_IWOTH 0000002     /* W for other */
#define S_IXOTH 0000001     /* X for other */

#define S_IFMT   0170000    /* type of file mask */
#define S_IFIFO  0010000    /* named pipe (fifo) */
#define S_IFCHR  0020000    /* character special */
#define S_IFDIR  0040000    /* directory */
#define S_IFBLK  0060000    /* block special */
#define S_IFREG  0100000    /* regular */
#define S_IFLNK  0120000    /* symbolic link */
#define S_IFSOCK 0140000    /* socket */
#define S_IFWHT  0160000    /* whiteout */


struct HFSPlusExtentDescriptor {
    UInt32                  startBlock;
    UInt32                  blockCount;
};
typedef struct HFSPlusExtentDescriptor HFSPlusExtentDescriptor;

typedef HFSPlusExtentDescriptor HFSPlusExtentRecord[8];

struct HFSPlusForkData {
    UInt64                  logicalSize;
    UInt32                  clumpSize;
    UInt32                  totalBlocks;
    HFSPlusExtentRecord     extents;
};
typedef struct HFSPlusForkData HFSPlusForkData;

typedef UInt32 HFSCatalogNodeID;

struct HFSPlusVolumeHeader {
    UInt16              signature;
    UInt16              version;
    UInt32              attributes;
    UInt32              lastMountedVersion;
    UInt32              journalInfoBlock;
 
    UInt32              createDate;
    UInt32              modifyDate;
    UInt32              backupDate;
    UInt32              checkedDate;
 
    UInt32              fileCount;
    UInt32              folderCount;
 
    UInt32              blockSize;
    UInt32              totalBlocks;
    UInt32              freeBlocks;
 
    UInt32              nextAllocation;
    UInt32              rsrcClumpSize;
    UInt32              dataClumpSize;
    HFSCatalogNodeID    nextCatalogID;
 
    UInt32              writeCount;
    UInt64              encodingsBitmap;
 
    UInt32              finderInfo[8];
 
    HFSPlusForkData     allocationFile;
    HFSPlusForkData     extentsFile;
    HFSPlusForkData     catalogFile;
    HFSPlusForkData     attributesFile;
    HFSPlusForkData     startupFile;
};
typedef struct HFSPlusVolumeHeader HFSPlusVolumeHeader;

enum {
    /* Bits 0-6 are reserved */
    kHFSVolumeHardwareLockBit       =  7,
    kHFSVolumeUnmountedBit          =  8,
    kHFSVolumeSparedBlocksBit       =  9,
    kHFSVolumeNoCacheRequiredBit    = 10,
    kHFSBootVolumeInconsistentBit   = 11,
    kHFSCatalogNodeIDsReusedBit     = 12,
    kHFSVolumeJournaledBit          = 13,
    /* Bit 14 is reserved */
    kHFSVolumeSoftwareLockBit       = 15
    /* Bits 16-31 are reserved */
};

struct BTNodeDescriptor {
    UInt32    fLink;
    UInt32    bLink;
    SInt8     kind;
    UInt8     height;
    UInt16    numRecords;
    UInt16    reserved;
};
typedef struct BTNodeDescriptor BTNodeDescriptor;

enum {
    kBTLeafNode       = -1,
    kBTIndexNode      =  0,
    kBTHeaderNode     =  1,
    kBTMapNode        =  2
};

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

enum BTreeTypes{
    kHFSBTreeType           =   0,      // control file
    kUserBTreeType          = 128,      // user btree type starts from 128
    kReservedBTreeType      = 255
};

enum {
    kBTBadCloseMask           = 0x00000001,
    kBTBigKeysMask            = 0x00000002,
    kBTVariableIndexKeysMask  = 0x00000004
};

enum {
    kHFSRootParentID            = 1,
    kHFSRootFolderID            = 2,
    kHFSExtentsFileID           = 3,
    kHFSCatalogFileID           = 4,
    kHFSBadBlockFileID          = 5,
    kHFSAllocationFileID        = 6,
    kHFSStartupFileID           = 7,
    kHFSAttributesFileID        = 8,
    kHFSRepairCatalogFileID     = 14,
    kHFSBogusExtentFileID       = 15,
    kHFSFirstUserCatalogNodeID  = 16
};

struct HFSPlusCatalogKey {
    UInt16              keyLength;
    HFSCatalogNodeID    parentID;
    HFSUniStr255        nodeName;
};
typedef struct HFSPlusCatalogKey HFSPlusCatalogKey;

enum {
    kHFSPlusFolderRecord        = 0x0001,
    kHFSPlusFileRecord          = 0x0002,
    kHFSPlusFolderThreadRecord  = 0x0003,
    kHFSPlusFileThreadRecord    = 0x0004
};

enum {
    kHFSFolderRecord            = 0x0100,
    kHFSFileRecord              = 0x0200,
    kHFSFolderThreadRecord      = 0x0300,
    kHFSFileThreadRecord        = 0x0400
};

struct HFSPlusCatalogFolder {
    SInt16              recordType;
    UInt16              flags;
    UInt32              valence;
    HFSCatalogNodeID    folderID;
    UInt32              createDate;
    UInt32              contentModDate;
    UInt32              attributeModDate;
    UInt32              accessDate;
    UInt32              backupDate;
    HFSPlusBSDInfo      permissions;
    FolderInfo          userInfo;
    ExtendedFolderInfo  finderInfo;
    UInt32              textEncoding;
    UInt32              reserved;
};
typedef struct HFSPlusCatalogFolder HFSPlusCatalogFolder;
 
 struct HFSPlusCatalogFile {
    SInt16              recordType;
    UInt16              flags;
    UInt32              reserved1;
    HFSCatalogNodeID    fileID;
    UInt32              createDate;
    UInt32              contentModDate;
    UInt32              attributeModDate;
    UInt32              accessDate;
    UInt32              backupDate;
    HFSPlusBSDInfo      permissions;
    FileInfo            userInfo;
    ExtendedFileInfo    finderInfo;
    UInt32              textEncoding;
    UInt32              reserved2;
 
    HFSPlusForkData     dataFork;
    HFSPlusForkData     resourceFork;
};
typedef struct HFSPlusCatalogFile HFSPlusCatalogFile;
 
 enum {
    kHFSFileLockedBit       = 0x0000,
    kHFSFileLockedMask      = 0x0001,
    kHFSThreadExistsBit     = 0x0001,
    kHFSThreadExistsMask    = 0x0002
};

struct HFSPlusCatalogThread {
    SInt16              recordType;
    SInt16              reserved;
    HFSCatalogNodeID    parentID;
    HFSUniStr255        nodeName;
};
typedef struct HFSPlusCatalogThread HFSPlusCatalogThread;

struct HFSPlusExtentKey {
    UInt16              keyLength;
    UInt8               forkType;
    UInt8               pad;
    HFSCatalogNodeID    fileID;
    UInt32              startBlock;
};
typedef struct HFSPlusExtentKey HFSPlusExtentKey;

static bool IsAllocationBlockUsed(UInt32 thisAllocationBlock,
                                     UInt8 *allocationFileContents)
{
    UInt8 thisByte;

    thisByte = allocationFileContents[thisAllocationBlock / 8];
    return (thisByte & (1 << (7 - (thisAllocationBlock % 8)))) != 0;
}

enum {
    kHFSPlusAttrInlineData  = 0x10,
    kHFSPlusAttrForkData    = 0x20,
    kHFSPlusAttrExtents     = 0x30
};

struct HFSPlusAttrForkData {
    UInt32          recordType;
    UInt32          reserved;
    HFSPlusForkData theFork;
};
typedef struct HFSPlusAttrForkData HFSPlusAttrForkData;

struct HFSPlusAttrExtents {
    UInt32                  recordType;
    UInt32                  reserved;
    HFSPlusExtentRecord     extents;
};
typedef struct HFSPlusAttrExtents HFSPlusAttrExtents;
typedef HFSPlusExtentDescriptor HFSPlusExtentRecord[8];

enum {
    kHardLinkFileType = 0x686C6E6B,  /* 'hlnk' */
    kHFSPlusCreator   = 0x6866732B   /* 'hfs+' */
};

enum {
    kSymLinkFileType  = 0x736C6E6B, /* 'slnk' */
    kSymLinkCreator   = 0x72686170  /* 'rhap' */
};

#pragma pack(pop)


