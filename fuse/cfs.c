/*
  FUSE: Filesystem in Userspace
  Copyright (C) 2001-2007  Miklos Szeredi <miklos@szeredi.hu>

  This program can be distributed under the terms of the GNU GPL.
  See the file COPYING.

  gcc -Wall hello.c `pkg-config fuse --cflags --libs` -o hello
*/

#define FUSE_USE_VERSION 26

#include <fuse.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <fcntl.h>
#include <stdlib.h>

#include "log.h"
#include "fswork.h"

static int cfs_getattr(const char *path, struct stat *stbuf)
{
	int res = 0;

	memset(stbuf, 0, sizeof(struct stat));
	if (strcmp(path, "/") == 0) {
		stbuf->st_mode = S_IFDIR | 0755;
		stbuf->st_nlink = 2;
        return res;
	}     

    int i;
    struct filestruct *nodes = getNodes();
    int nd = getNumByPath(path, nodes); 
    if (nd != -1)
    { 
        stbuf->st_ino = nd;
        //stbuf->st_mode = n.di_mode;    /* protection */
        //stbuf->st_nlink = n.di_nlink;   /* number of hard links */
        stbuf->st_uid = nodes[nd].uid;
        stbuf->st_gid =  nodes[nd].gid;
        stbuf->st_atime = nodes[nd].atime;
        stbuf->st_mtime = nodes[nd].mtime;
        stbuf->st_ctime = nodes[nd].ctime;

        stbuf->st_mode = nodes[nd].mode;//S_IFREG | 0777;
        stbuf->st_nlink = nodes[nd].n_link;
        stbuf->st_size = nodes[nd].size;//strlen(hello_str);
        //addLog("path exists");
        return res;

    }
	res = -ENOENT;
	return res;
}

static int cfs_readdir(const char *path, void *buf, fuse_fill_dir_t filler,
			 off_t offset, struct fuse_file_info *fi)
{
	(void) offset;
	(void) fi;

	//if (strcmp(path, "/") != 0)
	//	return -ENOENT;

    //add selflink 
	filler(buf, ".", NULL, 0);
    //add parent link
	filler(buf, "..", NULL, 0);

    //cut my arms :)
    struct filestruct *nodes = getNodes();
    int i;
    long pd = 0;
    char sbuf[1024];
    sprintf(sbuf, "reading dir path %s", path);
    addLog(sbuf);
    if (strcmp("/", path) == 0)
    {
        pd = -1;
    }
    else
    {
        pd = getNumByPath(path, nodes);
        if (pd == -1)
        {
            return -ENOENT;
        }
    }
    for (i = 0 ; i < MAX_NODES; i++)
    {
        if (nodes[i].exists && nodes[i].parentdir == pd)
        {
            struct stat *stbuf = malloc(sizeof(struct stat));
            memset(stbuf, 0, sizeof(struct stat));
            if (strlen(path) >= strlen(nodes[i].path))
            {
                continue;
            }
            const char *tmppath = nodes[i].path + strlen(path);
            if (tmppath[0] == '/')
                tmppath += 1;

            /*int j;
            for (j = 0; j < strlen(nodes[i].path) ; j++)
            {
                if (path[j] == '/')
                {
                    tmppath = nodes[i].path + j + 1;
                    sprintf(sbuf, "calc new path %s old %s place of / %d len of old path %d req path %s", tmppath, nodes[i].path, j, (int)strlen(nodes[i].path), path);
                    addLog(sbuf);
                }
            }*/
            stbuf->st_ino = i;
            stbuf->st_uid = nodes[i].uid;
            stbuf->st_gid =  nodes[i].gid;
            stbuf->st_atime = nodes[i].atime;
            stbuf->st_mtime = nodes[i].mtime;
            stbuf->st_ctime = nodes[i].ctime;

            stbuf->st_mode = nodes[i].mode;//S_IFREG | 0777;
            stbuf->st_nlink = nodes[i].n_link;
            stbuf->st_size = nodes[i].size;//strlen(hello_str);

            filler(buf, tmppath, stbuf, 0);
        }
    }


	return 0;
}

static int cfs_open(const char *path, struct fuse_file_info *fi)
{
    struct filestruct *nodes = getNodes();
    int nd = getNumByPath(path, nodes); 
    fi->fh = nd;
    if (nd > -1)
    {
        return 0;
    }
    return -ENOENT;
}

static int cfs_read(const char *path, char *buf, size_t size, off_t offset,
		      struct fuse_file_info *fi)
{
    //struct filestruct *nodes = getNodes();
    //int nd = getNumByPath(path, nodes); 
    int nd = fi->fh;
    if(nd < 0)
    {
        return -ENOENT;
    }
    
    struct filestruct node = readNode(nd);
    if (!node.exists)
    {
        return -ENOENT;
    }

    if((size = readFile(node, (void *)buf, (long)offset, size)) < 0)
    {
        return -EIO;
    }
    char sbuf[1024];
    sprintf(sbuf, "real read %ld", size);
    addLog(sbuf);
	return size;
}

int cfs_write(const char *path, const char *buf, size_t size, off_t offset, struct fuse_file_info *fi)
{
    //char sbuf[1024];
    //sprintf(sbuf, "read finfo %ld", fi->fh );
    //addLog(sbuf);
    //struct filestruct *nodes = getNodes();
    //int nd = getNumByPath(path, nodes); 
    int nd = fi->fh;
    if(nd < 0)
    {
        return -ENOENT;
    }

    struct filestruct node = readNode(nd);
    if (!node.exists)
    {
        return -ENOENT;
    }

    if((size = writeFile(node, (void *)buf, (long)offset, size, nd)) < 0)
    {
        return -EIO;
    }
    return size;
}

int cfs_rename(const char *path, const char *newpath)
{
    //return 0;
    addLog("Renaming...");
    addLog(newpath);
    return Rename(path, newpath);
}

static void* cfs_init(struct fuse_conn_info *conn)
{
    addLog("Start work");
    //initFileSystem();
}

int cfs_mknod(const char *path, mode_t mode, dev_t dev)
{
    if (S_ISREG(mode))
        return createNode(path, mode, 0, NULL);

    return -EINVAL;
}

int cfs_unlink(const char *path)
{
    struct filestruct *nodes = getNodes();
    int nd = getNumByPath(path, nodes); 
    if (nd == -1)
    {
        return -ENOENT;
    }
    nodes[nd].exists = 0;
    writeNode(nodes[nd], nd);
    return 0;
}

int cfs_symlink(const char *path, const char *link)
{
    createNode(link, S_IFLNK, 2, path);

    return 0;
}


int cfs_mkdir(const char *path, mode_t mode)
{
    return createNode(path, mode, 1, NULL);
}

int cfs_readlink(const char *path, char *buf, size_t size)
{
    struct filestruct *nodes = getNodes();
    int nd = getNumByPath(path, nodes); 
    if (nd == -1)
    {
        return -ENOENT;
    }
    if (nodes[nd].type != 2)
    {
        return -EINVAL;
    }

    strncpy(buf, nodes[nd].link, size);

    return 0;
}

int cfs_rmdir(const char *path)
{
    struct filestruct *nodes = getNodes();
    int nd = getNumByPath(path, nodes); 
    if (nd == -1)
    {
        return -ENOENT;
    }
    if (nodes[nd].type != 1)
    {
        return -EINVAL;
    }

    nodes[nd].exists = 0;
    writeNode(nodes[nd], nd);

    int i;
    for(i = 0; i < MAX_NODES; i++)
    {
        if(nodes[i].parentdir == nd)
        {
            nodes[i].exists = 0;
            writeNode(nodes[i], i);
        }
    }

    return 0;
}


int cfs_flush(const char *path, struct fuse_file_info *info)
{
    struct filestruct *nodes = getNodes();
    int nd = getNumByPath(path, nodes); 
    if (nd == -1)
    {
        return -ENOENT;
    }
    return 0; 
}

//useless?
int cfs_release(const char *path, struct fuse_file_info *info)
{
    struct filestruct *nodes = getNodes();
    int nd = getNumByPath(path, nodes); 
    if (nd == -1)
    {
        return -ENOENT;
    }
    return 0; 
}

int cfs_create(const char *path, mode_t mode, struct fuse_file_info *info)
{
    int res = cfs_mknod(path, mode, 0);
    if (res == -EEXIST || res == -ENOENT || -EINVAL)
        return res;
    return cfs_open(path, info);
}

int cfs_truncate(const char *path, off_t size)
{
    struct filestruct *nodes = getNodes();
    int nd = getNumByPath(path, nodes); 
    if (nd == -1)
    {
        return -ENOENT;
    }
    if (nodes[nd].size <= size)
        return -EINVAL;
    nodes[nd].size = size;
    writeNode(nodes[nd], nd);
    return 0;
}

static struct fuse_operations cfs_oper = {
	.getattr	= cfs_getattr,//
	.readdir	= cfs_readdir,//
	.open		= cfs_open,//
	.read		= cfs_read,//
    .write      = cfs_write,
    .init       = cfs_init,
    .rename     = cfs_rename,
    .mknod      = cfs_mknod,
    .unlink     = cfs_unlink,
    .symlink    = cfs_symlink,
    .mkdir      = cfs_mkdir,
    .readlink   = cfs_readlink,
    .rmdir      = cfs_rmdir,
    .flush      = cfs_flush,
    .release    = cfs_release,
    .truncate   = cfs_truncate,
};

int main(int argc, char *argv[])
{
    //struct filestruct *nodes = getNodes();
	return fuse_main(argc, argv, &cfs_oper, NULL);
}
