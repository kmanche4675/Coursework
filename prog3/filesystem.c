#include "filesystem.h"
#include "softwaredisk.h"

#define NUM_BLOCKS 8192 // Define NUM_BLOCKS here
#define NUM_INODES 128
#define ROOT_INODE 0

FSError fserror;

// Bitmap for free blocks and inodes
uint8_t block_bitmap[NUM_BLOCKS / 8];
uint8_t inode_bitmap[NUM_INODES / 8];

// Inode structure
typedef struct {
    char name[256];
    uint16_t direct_blocks[13];
    uint16_t indirect_block;
    uint32_t size;
    bool is_directory;
} Inode;

// Inode table
Inode inode_table[NUM_INODES];

struct FileInternals {
    char name[256];
    FileMode mode;
    Inode *inode;  // Pointer to Inode, not an index
    uint64_t position;
    uint64_t size;
};

File open_file(char *name, FileMode mode) {
    // Check if the file exists
    if (!file_exists(name)) {
        fserror = FS_FILE_NOT_FOUND;
        return NULL;
    }

    // Open the file and set the file position to 0
    File file = malloc(sizeof(struct FileInternals));
    if (!file) {
        fserror = FS_IO_ERROR;
        return NULL;
    }

    strcpy(file->name, name);
    file->mode = mode;
    file->position = 0;

    // Retrieve inode information and set it in file->inode
    int inode_index = -1;
    for (int i = 0; i < NUM_INODES; i++) {
        if (strcmp(inode_table[i].name, name) == 0) {
            inode_index = i;
            break;
        }
    }

    if (inode_index == -1) {
        fserror = FS_FILE_NOT_FOUND;
        free(file);
        return NULL;
    }

    file->inode = &inode_table[inode_index];  // Set the inode pointer

    fserror = FS_NONE;
    return file;
}

File create_file(char *name) {
    // Check if the file already exists
    if (file_exists(name)) {
        fserror = FS_FILE_ALREADY_EXISTS;
        return NULL;
    }

    // Find a free inode
    int inode_index = -1;
    for (int i = 0; i < NUM_INODES; i++) {
        if ((inode_bitmap[i / 8] & (1 << (i % 8))) == 0) {
            inode_index = i;
            break;
        }
    }

    if (inode_index == -1) {
        fserror = FS_OUT_OF_SPACE;
        return NULL;
    }

    // Mark the inode as used
    inode_bitmap[inode_index / 8] |= (1 << (inode_index % 8));

    // Initialize the inode
    Inode *inode = &inode_table[inode_index];
    strcpy(inode->name, name);
    inode->size = 0;
    inode->is_directory = false;
    memset(inode->direct_blocks, 0, sizeof(inode->direct_blocks));
    inode->indirect_block = 0;

    // Create the file structure
    File file = malloc(sizeof(struct FileInternals));
    if (!file) {
        fserror = FS_IO_ERROR;
        return NULL;
    }

    strcpy(file->name, name);
    file->mode = READ_WRITE;
    file->position = 0;
    file->size = 0;
    file->inode = inode;  // Set the inode pointer

    fserror = FS_NONE;
    return file;
}

void close_file(File file) {
    if (!file) {
        fserror = FS_FILE_NOT_OPEN;
        return;
    }

    // Update any necessary metadata
    free(file);
    fserror = FS_NONE;
}

uint64_t read_file(File file, void *buf, uint64_t numbytes) {
    if (!file || file->mode == READ_WRITE) {
        fserror = FS_FILE_NOT_OPEN;
        return 0;
    }

    uint64_t bytes_read = 0;
    uint16_t block_num;
    uint64_t block_offset;
    uint64_t bytes_to_read;
    uint8_t block_buf[SOFTWARE_DISK_BLOCK_SIZE];

    while (bytes_read < numbytes) {
        block_num = file->position / SOFTWARE_DISK_BLOCK_SIZE;
        block_offset = file->position % SOFTWARE_DISK_BLOCK_SIZE;
        bytes_to_read = SOFTWARE_DISK_BLOCK_SIZE - block_offset;

        if (bytes_to_read > numbytes - bytes_read) {
            bytes_to_read = numbytes - bytes_read;
        }

        if (block_num < 13) {
            if (file->inode->direct_blocks[block_num] == 0) {
                // No data to read
                break;
            }

            // Read the block into the buffer
            read_sd_block(block_buf, file->inode->direct_blocks[block_num]);

            // Copy the data to the output buffer
            memcpy(buf + bytes_read, block_buf + block_offset, bytes_to_read);
        } else {
            // Handle indirect blocks (not implemented in this example)
        }

        file->position += bytes_to_read;
        bytes_read += bytes_to_read;
    }

    fserror = FS_NONE;
    return bytes_read;
}

uint64_t write_file(File file, void *buf, uint64_t numbytes) {
    if (!file || file->mode == READ_ONLY) {
        fserror = FS_FILE_READ_ONLY;
        return 0;
    }

    uint64_t bytes_written = 0;
    uint16_t block_num;
    uint64_t block_offset;
    uint64_t bytes_to_write;
    uint8_t block_buf[SOFTWARE_DISK_BLOCK_SIZE];

    while (bytes_written < numbytes) {
        block_num = file->position / SOFTWARE_DISK_BLOCK_SIZE;
        block_offset = file->position % SOFTWARE_DISK_BLOCK_SIZE;
        bytes_to_write = SOFTWARE_DISK_BLOCK_SIZE - block_offset;

        if (bytes_to_write > numbytes - bytes_written) {
            bytes_to_write = numbytes - bytes_written;
        }

        if (block_num < 13) {
            if (file->inode->direct_blocks[block_num] == 0) {
                // Allocate a new block
                int free_block = -1;
                for (int i = 0; i < NUM_BLOCKS; i++) {
                    if ((block_bitmap[i / 8] & (1 << (i % 8))) == 0) {
                        free_block = i;
                        block_bitmap[i / 8] |= (1 << (i % 8));
                        break;
                    }
                }

                if (free_block == -1) {
                    fserror = FS_OUT_OF_SPACE;
                    return bytes_written;
                }

                file->inode->direct_blocks[block_num] = free_block;
            }

            // Read the block into the buffer
            read_sd_block(block_buf, file->inode->direct_blocks[block_num]);

            // Write the data to the buffer
            memcpy(block_buf + block_offset, buf + bytes_written, bytes_to_write);

            // Write the buffer back to the disk
            write_sd_block(block_buf, file->inode->direct_blocks[block_num]);
        } else {
            // Handle indirect blocks (not implemented in this example)
        }

        file->position += bytes_to_write;
        bytes_written += bytes_to_write;
    }

    file->size += bytes_written;
    fserror = FS_NONE;
    return bytes_written;
}

bool seek_file(File file, uint64_t bytepos) {
    if (!file) {
        fserror = FS_FILE_NOT_OPEN;
        return false;
    }

    // Set the current file position to bytepos
    file->position = bytepos;

    fserror = FS_NONE;
    return true;
}

uint64_t file_length(File file) {
    if (!file) {
        fserror = FS_FILE_NOT_OPEN;
        return 0;
    }

    // Return the current length of the file
    return file->size;
}

bool delete_file(char *name) {
    // Locate the file's inode
    int inode_index = -1;
    for (int i = 0; i < NUM_INODES; i++) {
        if (inode_table[i].is_directory == false && strcmp(inode_table[i].name, name) == 0) {
            inode_index = i;
            break;
        }
    }

    if (inode_index == -1) {
        fserror = FS_FILE_NOT_FOUND;
        return false;
    }

    // Mark the inode and its blocks as free
    inode_bitmap[inode_index / 8] &= ~(1 << (inode_index % 8));
    for (int i = 0; i < 13; i++) {
        if (inode_table[inode_index].direct_blocks[i] != 0) {
            block_bitmap[inode_table[inode_index].direct_blocks[i] / 8] &= ~(1 << (inode_table[inode_index].direct_blocks[i] % 8));
        }
    }

    // Clear the inode
    memset(&inode_table[inode_index], 0, sizeof(Inode));

    fserror = FS_NONE;
    return true;
}

bool file_exists(char *name) {
    printf("Checking if file exists: %s\n", name); // Debugging output
        for (int i = 0; i < NUM_INODES; i++) {
        if (inode_table[i].is_directory == false && strcmp(inode_table[i].name, name) == 0) {
            fserror = FS_NONE;
            return true;
        }
    }
    printf("File not found: %s\n", name); // Debugging output
    fserror = FS_FILE_NOT_FOUND;
    return false;
}

void fs_print_error(void) {
    switch (fserror) {
        case FS_NONE:
            printf("FS: No error.\n");
            break;
        case FS_OUT_OF_SPACE:
            printf("FS: Out of space.\n");
            break;
        case FS_FILE_NOT_OPEN:
            printf("FS: File not open.\n");
            break;
        case FS_FILE_OPEN:
            printf("FS: File already open.\n");
            break;
        case FS_FILE_NOT_FOUND:
            printf("FS: File not found.\n");
            break;
        case FS_FILE_READ_ONLY:
            printf("FS: File is read-only.\n");
            break;
        case FS_FILE_ALREADY_EXISTS:
            printf("FS: File already exists.\n");
            break;
        case FS_EXCEEDS_MAX_FILE_SIZE:
            printf("FS: Exceeds max file size.\n");
            break;
        case FS_ILLEGAL_FILENAME:
            printf("FS: Illegal filename.\n");
            break;
        case FS_IO_ERROR:
            printf("FS: I/O error.\n");
            break;
        default:
            printf("FS: Unknown error code %d.\n", fserror);
    }
}

bool initialize_filesystem() {
    // Initialize the software disk
    if (!init_software_disk()) {
        fserror = FS_IO_ERROR;
        return false;
    }

    // Initialize bitmaps
    memset(block_bitmap, 0, sizeof(block_bitmap));
    memset(inode_bitmap, 0, sizeof(inode_bitmap));

    // Mark the root inode as used
    inode_bitmap[ROOT_INODE / 8] |= (1 << (ROOT_INODE % 8));

    // Initialize the root inode
    Inode root_inode = { .size = 0, .is_directory = true };
    memset(root_inode.direct_blocks, 0, sizeof(root_inode.direct_blocks));
    root_inode.indirect_block = 0;
    inode_table[ROOT_INODE] = root_inode;

    // Write bitmaps and inode table to disk
    if (!write_sd_block(block_bitmap, 0) || !write_sd_block(inode_bitmap, 1)) {
        fserror = FS_IO_ERROR;
        return false;
    }

    for (int i = 0; i < (sizeof(inode_table) / SOFTWARE_DISK_BLOCK_SIZE); i++) {
        if (!write_sd_block(((uint8_t*)inode_table) + i * SOFTWARE_DISK_BLOCK_SIZE, 2 + i)) {
            fserror = FS_IO_ERROR;
            return false;
        }
    }

    return true;
}

