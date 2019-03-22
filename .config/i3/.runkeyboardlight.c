#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
	char fpath[]="/sys/class/leds/asus::kbd_backlight/brightness";
	FILE *fp;
	int brightness=0;	//brightness level
	int sel=0;			//0 for inc, 1 for decrease
	uid_t uid;


	if (argc < 1) {
		fprintf(stderr, "Insert an argument: inc or dec");
		exit(-1);
	}

	if (strncmp(argv[1], "inc", 3)==0) {
		sel=0;
	} else if (strncmp(argv[1], "dec", 3)==0) {
		sel=1;
	} else {
		fprintf(stderr, "Error input format, insert: inc or dec");
		exit(-1);
	}


	fp=fopen (fpath, "r") ;
	if (fp==NULL) {
		fprintf(stderr, "Failing open file in path read");
		exit(-1);
	}

	if (fscanf(fp, "%d", &brightness)==0) {
		fprintf(stderr, "Error in reading the file");
		exit(-1);
	}

	fclose(fp);

	if (sel==0 && brightness<4) {
		//inc
		brightness++;
	} else if (sel==1 && brightness>0) {
		//dec
		brightness--;
	}

	uid = getuid();

	if (setuid(0)==-1) {
		fprintf(stderr, "Error failing getting privilages");
		exit(-1);
	}

	fp=fopen (fpath, "w") ;
	if (fp==NULL) {
		fprintf(stderr, "Failing open file in path write");
		exit(-1);
	}

	if (fprintf(fp, "%d", brightness)==0) {
		fprintf(stderr, "Error in writing the file");
		exit(-1);
	}

	fclose(fp);
	if (setuid(uid)) {
		fprintf(stderr, "Error failing dropping privilages");
		exit(-1);
	}

	return 0;
 }
