typedef unsigned char BYTE;
typedef unsigned short int WORD;
typedef unsigned int DWORD;
typedef unsigned long long LONGLONG;

typedef WORD UInt16;
typedef DWORD UInt32;
typedef LONGLONG UInt64;

typedef UInt32 HFSCatalogNodeID;

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

