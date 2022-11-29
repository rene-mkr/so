
typedef unsigned char BYTE;
typedef unsigned short int WORD;
typedef unsigned int DWORD;
typedef unsigned long long LONGLONG;

typedef BYTE UInt8;
typedef char SInt8;
typedef short int SInt16;
typedef int SInt32;
typedef WORD UInt16;
typedef DWORD UInt32;
typedef LONGLONG UInt64;

struct Point {
  SInt16              v;
  SInt16              h;
};
typedef struct Point  Point;

struct Rect {
  SInt16              top;
  SInt16              left;
  SInt16              bottom;
  SInt16              right;
};
typedef struct Rect   Rect;

/* OSType is a 32-bit value made by packing four 1-byte characters 
   together. */
typedef UInt32        FourCharCode;
typedef FourCharCode  OSType;

/* Finder flags (finderFlags, fdFlags and frFlags) */
enum {
  kIsOnDesk       = 0x0001,     /* Files and folders (System 6) */
  kColor          = 0x000E,     /* Files and folders */
  kIsShared       = 0x0040,     /* Files only (Applications only) If */
                                /* clear, the application needs */
                                /* to write to its resource fork, */
                                /* and therefore cannot be shared */
                                /* on a server */
  kHasNoINITs     = 0x0080,     /* Files only (Extensions/Control */
                                /* Panels only) */
                                /* This file contains no INIT resource */
  kHasBeenInited  = 0x0100,     /* Files only.  Clear if the file */
                                /* contains desktop database resources */
                                /* ('BNDL', 'FREF', 'open', 'kind'...) */
                                /* that have not been added yet.  Set */
                                /* only by the Finder. */
                                /* Reserved for folders */
  kHasCustomIcon  = 0x0400,     /* Files and folders */
  kIsStationery   = 0x0800,     /* Files only */
  kNameLocked     = 0x1000,     /* Files and folders */
  kHasBundle      = 0x2000,     /* Files only */
  kIsInvisible    = 0x4000,     /* Files and folders */
  kIsAlias        = 0x8000      /* Files only */
};

/* Extended flags (extendedFinderFlags, fdXFlags and frXFlags) */
enum {
  kExtendedFlagsAreInvalid    = 0x8000, /* The other extended flags */
                                        /* should be ignored */
  kExtendedFlagHasCustomBadge = 0x0100, /* The file or folder has a */
                                        /* badge resource */
  kExtendedFlagHasRoutingInfo = 0x0004  /* The file contains routing */
                                        /* info resource */
};

struct FileInfo {
  OSType    fileType;           /* The type of the file */
  OSType    fileCreator;        /* The file's creator */
  UInt16    finderFlags;
  Point     location;           /* File's location in the folder. */
  UInt16    reservedField;
};
typedef struct FileInfo   FileInfo;

struct ExtendedFileInfo {
  SInt16    reserved1[4];
  UInt16    extendedFinderFlags;
  SInt16    reserved2;
  SInt32    putAwayFolderID;
};
typedef struct ExtendedFileInfo   ExtendedFileInfo;

struct FolderInfo {
  Rect      windowBounds;       /* The position and dimension of the */
                                /* folder's window */
  UInt16    finderFlags;
  Point     location;           /* Folder's location in the parent */
                                /* folder. If set to {0, 0}, the Finder */
                                /* will place the item automatically */
  UInt16    reservedField;
};
typedef struct FolderInfo   FolderInfo;

struct ExtendedFolderInfo {
  Point     scrollPosition;     /* Scroll position (for icon views) */
  SInt32    reserved1;
  UInt16    extendedFinderFlags;
  SInt16    reserved2;
  SInt32    putAwayFolderID;
};
typedef struct ExtendedFolderInfo   ExtendedFolderInfo;