/*
This source code file is licensed under the GNU GPL Version 2.0 Licence by the following copyright holder:
Crown Copyright Commonwealth of Australia (Geoscience Australia) 2015.
The GNU GPL 2.0 licence is available at: http://www.gnu.org/licenses/gpl-2.0.html. If you require a paper copy of the GNU GPL 2.0 Licence, please write to Free Software Foundation, Inc. 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.

Author: Ross C. Brodie, Geoscience Australia.
*/

#include <cstdio>
#include <cstdlib>
#include <cstring>
using namespace std;

#include "general_utils.h"

#define BUFFERLEN 1000000

int main(int argc, char* argv[])
{
	FILE *infile = (FILE*)NULL;
	FILE *outfile = (FILE*)NULL;

	if (argc != 4){
		printf("usage: %s input_file output_file subsample_rate\n", argv[0]);
		exit(1);
	}

	if ((infile = fopen(argv[1], "r")) == NULL) {
		printf("***WARNING*** cannot open file: %s \n", argv[1]);
		exit(1);
	}

	if ((outfile = fopen(argv[2], "w")) == NULL) {
		printf("***WARNING*** cannot open file: %s \n", argv[2]);
		exit(1);
	}

	size_t subsamplerate;
	size_t record = 0;
		
	subsamplerate = (size_t) atoi(argv[3]);

	std::vector<char> buf(BUFFERLEN + 1);
	char* buffer = &(buf[0]);
	bool keepgoing = true;
	do{
		if (fgets(buffer, BUFFERLEN, infile) == NULL){
			if (feof(infile)){
				keepgoing = false;
			}
			else{
				printf("read error\n");
				keepgoing = false;
			}
		}
		else{
			record++;
			if (record%subsamplerate != 1)continue;
			if (fputs(buffer, outfile) == EOF){
				printf("write error\n");
				keepgoing = false;
			}
		}
	} while (keepgoing);

	if (infile != NULL)fclose(infile);
	if (outfile != NULL)fclose(outfile);
	return 0;
}
