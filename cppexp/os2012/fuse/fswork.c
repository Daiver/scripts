#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <errno.h>

#include "fswork.h"
#include "log.h"

void initFileSystem(void)  
{
    struct filestruct *nodes = malloc(sizeof(struct filestruct)*MAX_NODES);
    memset(nodes, 0, sizeof(struct filestruct)*MAX_NODES);
    FILE *output;
    if((output=fopen(FS_FILE_PATH, "wb")) == NULL)
    {
        puts ("Can't open fs's file.");
        exit(-1);
    }
    fwrite(nodes, 1, sizeof(struct filestruct)*MAX_NODES, output);
    fclose(output);
    addLog("New fs was created");
}

struct filestruct *getNodes()
{
    struct filestruct *nodes = malloc(sizeof(struct filestruct)*MAX_NODES);
    FILE *input;
    int i;
    if((input=fopen(FS_FILE_PATH, "rb")) == NULL)
    {
        puts ("Can't open fs's file.");
        exit(-1);
    }
    //addLog("file opens");
    fread(nodes, sizeof(struct filestruct), MAX_NODES, input);
    fclose(input);
    return nodes;
}

int getNumByPath(const char *path, struct filestruct *nodes)
{
    int i;
    for (i = 0; i < MAX_NODES; i++)
    {
        //const char *tmppath = path + 1;
        if ((nodes[i].exists) && (strcmp(path, nodes[i].path) == 0)) 
        {
            return i;
        }
    }
    return -1;
}

void writeNode(struct filestruct node, int pos)
{
    FILE *fl;
    int i;
    if((fl=fopen(FS_FILE_PATH, "rb+")) == NULL)
    {
        puts ("Can't open fs's file.");
        exit(-1);
    }
    fseek(fl, pos*sizeof(struct filestruct), 0);
    fwrite(&node, 1, sizeof(struct filestruct), fl);
    fclose(fl);
}

int Rename(const char *path, const char *newpath)
{
    struct filestruct *nodes = getNodes();
    int ind = getNumByPath(path, nodes);
    if (ind < 0) return -ENOENT;
    long pdir = -1;
    int i;
    int strl = strlen(newpath);
    for (i = strl-1; i > 0; i--)
    {
        if (newpath[i] == '/')
        {
            if (i > 0)
            {
                char *pdpath = malloc(i+1);
                int j;
                for (j = 0; j < i; j++)
                {
                    pdpath[j] = newpath[j];
                }
                pdpath[i] = '\0';
                pdir = getNumByPath(pdpath, nodes);
                if ((pdir > -1) && (nodes[pdir].type != 1))
                    return -ENOENT;
                break;
            }
        }
    }

    nodes[ind].parentdir = pdir;
    strcpy(nodes[ind].path, newpath);
    writeNode(nodes[ind], ind);
    return 0;
}

int createNode(const char *path, mode_t mode, char type, const char *link)
{
    char sbuf[1024];
    sprintf(sbuf, "Before creating %s", path);
    addLog(sbuf);
    struct filestruct *nodes = getNodes();
    int ind = getNumByPath(path, nodes);

    //searching parents dirs
    int strl = strlen(path);
    int i, res;
    long pdir = -1;
    for (i = strl-1; i > 0; i--)
    {
        if (path[i] == '/')
        {
            if (i > 0)
            {
                char *pdpath = malloc(i+1);
                int j;
                for (j = 0; j < i; j++)
                {
                    pdpath[j] = path[j];
                }
                pdpath[i] = '\0';
                pdir = getNumByPath(pdpath, nodes);
                if ((pdir > -1) && (nodes[pdir].type != 1))
                    return -ENOENT;
                break;
            }
        }
    }

    if (ind > -1)
    {
        return -EEXIST;
    }
    for (i = 0; i < MAX_NODES; i++)
    {
        if (nodes[i].exists == 0)
        {
            res = i;
            break;
        }
    }
    i = res;
    strcpy(nodes[i].path, path);
    nodes[i].type = type;
    nodes[i].mode = mode;

    if (type == 0)
    {
        FILE *bfs = fopen(FS_FILE_PATH, "a+");
        fseek(bfs, 0L, SEEK_END);
        int noffset = ftell(bfs);
        nodes[i].offset = noffset;
        fclose(bfs);
    }
    if (type == 1)
    {
        nodes[i].mode = S_IFDIR | mode;
    }
    if (type == 2)
    {
        addLog("Creating symlink");
        strcpy(nodes[i].link, link);
    }

    nodes[i].uid = 0;
    nodes[i].gid = 0;
    nodes[i].atime = time(NULL);
    nodes[i].mtime = time(NULL);
    nodes[i].ctime = time(NULL);
    nodes[i].exists = 1;
    nodes[i].size = 0;//BLOCK_SIZE
    nodes[i].n_link = 1;
    nodes[i].parentdir = pdir;
    writeNode(nodes[i], i);
    sprintf(sbuf, "create file %s noffset %ld, nsize %ld", path, nodes[i].offset, nodes[i].size);
    addLog(sbuf);
    return 0;
}

char isNodeLast(struct filestruct node)
{
    FILE *fp;
    if((fp=fopen(FS_FILE_PATH, "rb")) == NULL)
    {
        puts ("Can't open fs's file.");
        exit(-1);
    }
    fseek(fp, 0L, SEEK_END);
    int sz = ftell(fp);
    fclose(fp);
    return node.size + node.offset == sz;
}

long writeFile(struct filestruct node, void *buf, long offset, long size, int nodenum)
{
    char sbuf[1024];
    sprintf(sbuf, "before write name %s  noffset %ld nsize %ld, offset %ld size %ld\n", node.path, node.offset, node.size, offset, size);
    addLog(sbuf);
    if (offset + size > node.size)
    {
        if (!isNodeLast(node))
        {
           node.offset = copyFileToEnd(node);
        }
        node.size = size + offset;
    }
    FILE *fl;
    int i;
    if((fl=fopen(FS_FILE_PATH, "rb+")) == NULL)
    {
        puts ("Can't open fs's file.");
        exit(-1);
    }
    fseek(fl, node.offset + offset, 0);
    size = fwrite(buf, 1, size, fl);
    //node.size += size;
    
    fclose(fl);
    writeNode(node, nodenum);
    sprintf(sbuf, "after write name %s  noffset %ld nsize %ld, offset %ld size %ld\n", node.path, node.offset, node.size, offset, size);
    addLog(sbuf);
    return size;
}

long readFile(struct filestruct node, char *buf, long offset, long size)
{
    FILE *fl;
    int i;
    char sbuf[1024];
    sprintf(sbuf, "before read name %s  noffset %ld nsize %ld, offset %ld size %ld\n", node.path, node.offset, node.size, offset, size);
    addLog(sbuf);
    if (offset + size > node.size)
    {
        size = node.size - offset;
    }
    if((fl=fopen(FS_FILE_PATH, "rb+")) == NULL)
    {
        puts ("Can't open fs's file.");
        exit(-1);
    }
    fseek(fl, node.offset + offset, 0);
    size = fread(buf, 1, size, fl);
    fclose(fl);
    return size;
}

int copyFileToEnd(struct filestruct node)
{
    FILE *fl;
    int i;
    if((fl=fopen(FS_FILE_PATH, "rb+")) == NULL)
    {
        puts ("Can't open fs's file.");
        exit(-1);
    }
    char *buf = malloc(node.size);
    fseek(fl, node.offset, 0);
    fread(buf, 1, node.size, fl);
    fseek(fl, 0L, SEEK_END);
    long offset = ftell(fl);
    fwrite(buf, 1, node.size, fl);
    fclose(fl);
    char sbuf[1024];
    sprintf(sbuf, "after copy to end name %s  noffset %ld nsize %ld, offset %ld \n", node.path, node.offset, node.size, offset);
    addLog(sbuf);
    return offset;
}

struct filestruct readNode(int pos)
{
    struct filestruct res;
    FILE *fl;
    int i;
    if((fl=fopen(FS_FILE_PATH, "rb+")) == NULL)
    {
        puts ("Can't open fs's file.");
        exit(-1);
    }
    fseek(fl, pos*sizeof(struct filestruct), 0);
    fread(&res, 1, sizeof(struct filestruct), fl);
    fclose(fl);

    return res;
}
