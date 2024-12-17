#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

void print_help(int argc, char* argv[])
{
	printf("Usage: %s infile outfile width height channels\n", argv[0]);
}

int main(int argc, char* argv[])
{
	char* dumpf;
	char* outf;
	int width,height, chan;
	FILE *ifd, *ofd;
	unsigned char* img;
	int npix;
	int n;

	if (argc < 6) {
		print_help(argc,argv);
		return -1;
	}

	dumpf  = argv[1];
	outf   = argv[2];
	width  = strtol(argv[3],NULL,10);
	if ((!width && errno == EINVAL) || (errno == ERANGE)){
		fprintf(stderr, "Invalid width: %s\n", argv[3]);
		return -1;
	}

	height = strtol(argv[4],NULL,10);
	if ((!height && errno == EINVAL) || (errno == ERANGE)){
		fprintf(stderr, "Invalid height: %s\n", argv[3]);
		return -1;
	}

	chan   = strtol(argv[5],NULL,10);
	if ((!chan && errno == EINVAL) || (errno == ERANGE)){
		fprintf(stderr, "Invalid channels: %s\n", argv[3]);
		return -1;
	}

	if (chan != 1 && chan != 3){
		fprintf(stderr, "Only 1 or 3 channels supported\n");
		return -1;
	}

	npix = width * height;

	if ((ifd = fopen(dumpf,"rb")) == NULL){
		fprintf(stderr, "Error opening file %s: %s\n", dumpf, strerror(errno));
		return -1;
	}
	
	if ((img = malloc(npix * chan)) == NULL){
		perror(NULL);
		return -1;
	}

	printf("Reading from dump file: %d x %d pixels of %d channles\n", width, height, chan);

	if ((n = (int) fread(img, 1, npix * chan, ifd)) != npix * chan){
		fprintf(stderr, "Not enough pixels in dumpfile, read %d bytes, expected %d\n", n, npix * chan);
		return -1;
	}

	if ((ofd = fopen(outf,"wb")) == NULL){
		fprintf(stderr, "Error opening file %s: %s\n", outf, strerror(errno));
		return -1;
	}

	if (chan == 1)
		fprintf(ofd, "P5\n"); //magic number
	else
		fprintf(ofd, "P6\n"); //magic number
	fprintf(ofd, "%d %d\n", width, height);
	fprintf(ofd, "255\n"); //max value
	fwrite(img, 1, npix * chan, ofd);
	fclose(ofd);
	free(img);

	return 0;
}

