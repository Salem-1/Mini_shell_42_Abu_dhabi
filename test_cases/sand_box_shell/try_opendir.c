#include <dirent.h>
#include <stdio.h>

int main()
{
	DIR *current_dir;
	struct dirent *de;

	//call opendir with the path of the desired driectory
	current_dir = opendir(".");
	if (current_dir == NULL)
		return (0);
	//this will list all the files and subdirectories in our
	//opened dir
	while ((de = readdir(current_dir)) != NULL)
		printf("%s\n", de->d_name); //accessubg tge directory entry
		//struct to get the name of sub directory members
	closedir(current_dir);
	return (0);
}



/***
refs and declartion of the GNU manual
struct dirent {
    ino_t          d_ino;       /* inode number *
    off_t          d_off;       /* offset to the next dirent /
    unsigned short d_reclen;    /* length of this record 
    unsigned char  d_type;      /* type of file; not supported
                                   by all file system types 
    char           d_name[256]; /* filename 
};


***/