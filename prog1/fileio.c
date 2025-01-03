#include "fileio.h"

FSError fserror;

static bool seek_file(File file, SeekAnchor start, long offset) {
    if (!file || (start != BEGINNING_OF_FILE && start != CURRENT_POSITION && start != END_OF_FILE)) {
        return false;
    } else {
        if (!fseek(file->file, offset, start == BEGINNING_OF_FILE ? SEEK_SET : 
                   (start == END_OF_FILE ? SEEK_END : SEEK_CUR))) {
            return true;
        } else {
            return false;
        }
    }
}

File open_file(char *name) {
    FileHandle* fh = (FileHandle*)malloc(sizeof(FileHandle));
    if (!fh) {
        fserror = OPEN_FAILED;
        return NULL; // Memory allocation failed
    }

    fserror = NONE;

    fh->file = fopen(name, "r+");
    if (!fh->file) {
        fh->file = fopen(name, "w+");
        if (!fh->file) {
            fserror = OPEN_FAILED;
            free(fh); // Free memory if opening failed
            return NULL;
        }
    }

    return fh;
}

void close_file(File file) {
    if (file) {
        if (file->file && !fclose(file->file)) {
            fserror = NONE;
        } else {
            fserror = CLOSE_FAILED;
        }
        free(file);
    }
}

unsigned long read_file_from(File file, void *data, unsigned long num_bytes, SeekAnchor start, long offset) {
    unsigned long bytes_read = 0L;

    fserror = NONE;

    if (!file || !seek_file(file, start, offset)) {
        fserror = READ_FAILED;
    } else {
        bytes_read = fread(data, 1, num_bytes, file->file);
        if (ferror(file->file)) {
            fserror = READ_FAILED;
        }
    }

    return bytes_read;
}

unsigned long write_file_at(File file, void *data, unsigned long num_bytes, SeekAnchor start, long offset) {
    unsigned long bytes_written = 0L;
    unsigned char *d = (unsigned char *)data;

    fserror = NONE;

    // Seek to the appropriate position
    if (!file || !seek_file(file, start, offset)) {
        fserror = WRITE_FAILED;
        return bytes_written;
    }

    // Check for illegal writes only if writing at the beginning
    if (offset == 0L && start == BEGINNING_OF_FILE) {
        if (num_bytes >= 4 &&
            (d[0] == 0xFE && d[1] == 0xED && d[2] == 0xFA && 
             (d[3] == 0xCE || d[3] == 0xCF))) {
            fserror = ILLEGAL_MACHO;
            return bytes_written; // Return 0 without writing
        }
    }

    // Perform the write
    bytes_written = fwrite(data, 1, num_bytes, file->file);
    if (bytes_written < num_bytes) {
        fserror = WRITE_FAILED;
    }

    return bytes_written;
}

void fs_print_error(void) {
    printf("FS ERROR: ");
    switch (fserror) {
    case NONE:
        puts("NONE");
        break;
    case OPEN_FAILED:
        puts("OPEN_FAILED");
        break;
    case CLOSE_FAILED:
        puts("CLOSE_FAILED");
        break;
    case READ_FAILED:
        puts("READ_FAILED");
        break;
    case WRITE_FAILED:
        puts("WRITE_FAILED");
        break;
    case ILLEGAL_MACHO:
        puts("ILLEGAL_MACHO: SHAME ON YOU!");
        break;
    default:
        puts("** UNKNOWN ERROR **");
    }
}
