/*
This source code file is licensed under the GNU GPL Version 2.0 Licence by the following copyright holder:
Crown Copyright Commonwealth of Australia (Geoscience Australia) 2015.
The GNU GPL 2.0 licence is available at: http://www.gnu.org/licenses/gpl-2.0.html. If you require a paper copy of the GNU GPL 2.0 Licence, please write to Free Software Foundation, Inc. 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.

Author: Ross C. Brodie, Geoscience Australia.
*/

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <sys/stat.h>	

#include "general_utils.h"

#if defined _WIN32
#include <io.h>
#else		
#define _chmod chmod
#endif

#define MAXSIZE 200000000

void interpretcontrolcharcters(char* input, char* output);
class cLogger glog; //The global instance of the log file manager

int main(int argc, char* argv[])
{
	struct stat file_stat;// , * filestat;
	size_t loc, length, numch;
	FILE* fp, * fq;

	char tempfilename[500];

	//filestat=&file_stat;

	if (argc < 4) {
		printf("usage: %s input_file search_pattern replace_pattern \n", argv[0]);
		printf("       You need to enclose strings with embedded spaces with \" \" marks\n");
		printf("       /t represents tab\n");
		printf("       /r carriage return\n");
		printf("       /n new line\n");
		exit(1);
	}

	if ((fp = fopen(argv[1], "r+b")) == NULL) {
		printf("***WARNING*** cannot open file: %s \n", argv[1]);
		exit(1);
	}
	if (stat(argv[1], &file_stat) != 0) {
		printf("***WARNING*** cannot read status on file: %s \n", argv[1]);
		exit(1);
	}
	if (file_stat.st_size > MAXSIZE) {
		printf("***WARNING*** file larger then MAXSIZE bytes : %s \n", argv[1]);
		exit(1);
	}

	char* inputtext = new char[MAXSIZE];
	char* search = new char[100000];
	char* searchstring = new char[100000];
	char* replace = new char[100000];
	char* replacestring = new char[100000];


	for (length = 0; !feof(fp); length++) {
		fread(&inputtext[length], 1, 1, fp);
	}

	strcpy(search, argv[2]);
	strcpy(replace, argv[3]);
	numch = 0;
	if (fseek(fp, 0, SEEK_SET)) {
		printf("seek error ");
		exit(1);
	}

	strcpy(tempfilename, argv[1]);
	strcat(tempfilename, ".CHANGETEXT.TMP");

	if ((fq = fopen(tempfilename, "w+b")) == NULL) {
		printf("***WARNING*** cannot open file: %s \n", tempfilename);
		exit(1);
	}

	//Check for control characters	  
	interpretcontrolcharcters(search, searchstring);
	interpretcontrolcharcters(replace, replacestring);

	size_t len_searchstring = strlen(searchstring);
	size_t len_replacestring = strlen(replacestring);
	for (loc = 0; loc < (length - 1); loc++) {

		if (strncmp(searchstring, &(inputtext[loc]), len_searchstring) == 0) {
			fwrite(replacestring, len_replacestring, 1, fq);
			numch++;
			loc = loc + len_searchstring - 1;
		}
		else fwrite(&(inputtext[loc]), 1, 1, fq);
	}

	fclose(fp);
	fclose(fq);
	remove(argv[1]);
	rename(tempfilename, argv[1]);
	_chmod(argv[1], file_stat.st_mode);



	if (numch == 0)printf("***WARNING: %s *** FILE %s :search std::string %s not found\n", argv[0], argv[1], search);
	else printf("FILE %s :%s replaced by %s %5zd times\n", argv[1], search, replace, numch);

	delete[]inputtext;
	delete[]search;
	delete[]searchstring;
	delete[]replace;
	delete[]replacestring;

	return 0;
}


void interpretcontrolcharcters(char* input, char* output)
{
	size_t len_input = strlen(input);
	output[0] = '\0';

	for (size_t k = 0; k < len_input; k++) {
		if (k < len_input - 1 && strncmp(&(input[k]), "/t", 2) == 0) {
			strcat(output, "\t");
			k++;
		}
		else if (k < len_input - 1 && strncmp(&(input[k]), "/r", 2) == 0) {
			strcat(output, "\r");
			k++;
		}
		else if (k < len_input - 1 && strncmp(&(input[k]), "/n", 2) == 0) {
			strcat(output, "\n");
			k++;
		}
		else {
			strcat(output, &(input[k]));
		}
	}
}