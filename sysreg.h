#include <fcntl.h>
#include <libvirt.h>
#include <poll.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <termios.h>
#include <unistd.h>
#include <errno.h>
#include <libxml/parser.h>
#include <libxml/tree.h>
#include <libxml/xpath.h>
#include <libxml/xpathInternals.h>
#include <sys/sysinfo.h>

#define EXIT_CHECKPOINT_REACHED     0
#define EXIT_SHUTDOWN               1
#define EXIT_ERROR                  2
#define EXIT_NONCONTINUABLE_ERROR   3
#define NUM_STAGES                  3

typedef struct {
    char BootDevice[8];
    char Checkpoint[80];
} stage;

typedef struct {
    int MaxCrashes;
    int Timeout;
    char Filename[255];
    char Name[80];
    char HardDiskImage[255];
    int ImageSize;
    stage Stage[3];
} Settings;

Settings AppSettings;

/* utils.c */
char* ReadFile (const char* filename);
ssize_t safewrite(int fd, const void *buf, size_t count);
void SysregPrintf(const char* format, ...);

/* options.c */
bool LoadSettings(const char* XmlConfig);

/* console.c */	
int ProcessDebugData(const char* tty, int timeout, int stage);  

/* raddr2line.c */
bool GetPackagePath(char* Buffer, int BuffSize, char* Module);
bool ResolveAddressFromFile(char* Buffer, int BuffSize, char* Data);
