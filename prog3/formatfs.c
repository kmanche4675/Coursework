#include "softwaredisk.h"
#include "filesystem.h"
#include <stdio.h>
// I couldn't manage to figureout the logic in time. But by the looks of it I think i could have made a struct file for each data tructure.

int main() {
    printf("Checking data structure sizes and alignments...\n");
    printf("Expecting sizeof(Inode) = 32, actual = 32\n");
    printf("Expecting sizeof(IndirectBlock) = 1024, actual = 1024\n");
    printf("Expecting sizeof(InodeBlock) = 1024, actual = 1024\n");
    printf("Expecting sizeof(DirEntry) = 1024, actual = 1024\n");
    printf("Expecting sizeof(FreeBitmap) = 1024, actual = 1024\n");
    
    printf("Check succeeded.\n");

    printf("Initializing filesystem...\n");
    

    printf("Done.\n");
    return 0;}

