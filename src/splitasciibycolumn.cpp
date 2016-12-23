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

#define BUFFERLEN 10000000

int main(int argc, char* argv[])
{
	FILE *fp_in = (FILE*)NULL;
	FILE *fp_out = (FILE*)NULL;


	if (argc<3){
		printf("usage: %s input_file column_number [headerlines]\n", argv[0]);		
		exit(1);
	}

	if ((fp_in = fopen(argv[1], "r")) == NULL) {
		printf("***WARNING*** cannot open file: %s \n", argv[1]);
		exit(1);
	}

	size_t column = 0;
	if (sscanf(argv[2], "%lu", &column) != 1){
		printf("Invalid column number %s\n", argv[2]);
		exit(1);
	}
	column = column - 1;//user use 1 rather than 0 based indexing

	size_t headerlines = 0;
	if (argc == 4){
		if (sscanf(argv[3], "%lu", &headerlines) != 1){
			printf("Invalid number of header lines %s\n", argv[2]);
			exit(1);
		}
	}

	std::vector<char> buf(BUFFERLEN + 1);
	char* buffer = &(buf[0]);
	bool endoffile = false;
	std::string oldid = "";

	for (size_t i = 0; i<headerlines; i++){
		fgets(buffer, BUFFERLEN, fp_in);
	}

	size_t record = headerlines;
	do{
		buffer[0] = 0;
		if (fgets(buffer, BUFFERLEN, fp_in) == NULL){
			if (feof(fp_in) || buffer[0] == 0){
				printf("End of input\n");
				endoffile = true;
				if (fp_in != NULL){
					fclose(fp_in);
					fp_in = (FILE*)NULL;
				}
				if (fp_out != NULL){
					fclose(fp_out);
					fp_out = (FILE*)NULL;
				}
			}
			else{
				printf("read error\n");
				exit(1);
			}
		}
		else{
			record++;
			
			if (buffer[0] == '\n' || buffer[0] == '\r'){
				printf("Skipping blank record %lu\n", record);
				continue;
			}

			std::vector<std::string> fields = fieldparsestring(buffer, " ");

			if (fields.size() < column+1){
				printf("Skipping record %lu - not enough columns\n", record);
				continue;
			}

			std::string id = trim(fields[column]);
						
			if (id.size() == 0){
				printf("Skipping record %lu - invalid id\n", record);
				continue;
			}

			if (id[0] == '"'){
				printf("Skipping record %lu id=%s\n", record, id.c_str());
				continue;
			}

			if (id != oldid){
				if (fp_out != NULL){
					fclose(fp_out);
				}

				std::string outname = strprint("%s.asc", id.c_str());
				if ((fp_out = fopen(outname.c_str(), "a+")) == NULL) {
					printf("***WARNING*** cannot open file: %s \n", outname.c_str());
					exit(1);
				}
				printf("Identifer: %s  File: %s\n", id.c_str(), outname.c_str());
				oldid = id;
			}
			
			if (fputs(&(buffer[0]), fp_out) == EOF) {
				printf("write error\n");
				exit(1);
			}

		}
	} while (endoffile == 0);

	if (fp_in  != NULL)fclose(fp_in);
	if (fp_out != NULL)fclose(fp_out);
	return 0;
}
