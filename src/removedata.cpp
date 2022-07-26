/*
This source code file is licensed under the GNU GPL Version 2.0 Licence by the following copyright holder:
Crown Copyright Commonwealth of Australia (Geoscience Australia) 2015.
The GNU GPL 2.0 licence is available at: http://www.gnu.org/licenses/gpl-2.0.html. If you require a paper copy of the GNU GPL 2.0 Licence, please write to Free Software Foundation, Inc. 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.

Author: Ross C. Brodie, Geoscience Australia.
*/

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include "general_utils.h"


int constexpr BUFFERLEN = 1000000;
class cLogger glog; //The global instance of the log file manager

int main(int argc, char* argv[])
{
	FILE* infile = (FILE*)NULL;
	FILE* outfile = (FILE*)NULL;

	if (argc != 3) {
		printf("usage: %s input_file output_file\n", argv[0]);
		exit(1);
	}

	if ((infile = fopen(argv[1], "r")) == NULL) {
		printf("***WARNING*** cannot open input file: %s \n", argv[1]);
		exit(1);
	}

	if ((outfile = fopen(argv[2], "w")) == NULL) {
		printf("***WARNING*** cannot open output file: %s \n", argv[2]);
		exit(1);
	}

	printf("Removing DATA from %s \n", argv[1]);

	std::vector<char> buf(BUFFERLEN + 1);
	char* buffer = &(buf[0]);

	size_t k = 0;
	while (fgets(buffer, BUFFERLEN, infile) != NULL) {
		k++;
		
		if (strlen(buffer) >= 4) {
			if (strncmp(buffer, "DATA", 4) == 0) {
				fputs(&(buffer[4]), outfile);
			}
			else {
				printf("Error: non DATA record encountered on line %d\n",k);
				exit(1);
			}
		}
	}
	if (infile != NULL)fclose(infile);
	if (outfile != NULL)fclose(outfile);
	printf("Done\n");
	return 0;
}
