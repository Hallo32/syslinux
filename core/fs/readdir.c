#include <stdio.h>
#include <string.h>
#include <sys/dirent.h>
#include "fs.h"
#include "core.h"

/* 
 * Open a directory
 */
DIR *opendir(const char *path)
{
    int rv;

    rv = searchdir(path);
    if (rv < 0)
	return NULL;

    /* XXX: check for a directory handle here */
    return (DIR *)handle_to_file(rv);
}

/*
 * Read one directory entry at one time. 
 */
struct dirent *readdir(DIR *dir)
{
    static struct dirent buf;
    struct dirent *de = NULL;
    struct file *dd_dir = (struct file *)dir;
    
    if (dd_dir)
	de = dd_dir->fs->fs_ops->readdir(dd_dir);
    
    if (de) {
	memcpy(&buf, de, sizeof *de);
	free(de);
	return &buf;
    } else {
	return NULL;
    }
}

/*
 * Close a directory
 */
int closedir(DIR *dir)
{
    struct file *dd_dir = (struct file *)dir;
    _close_file(dd_dir);
    return 0;
}

