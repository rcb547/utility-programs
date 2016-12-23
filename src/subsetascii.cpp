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

//---------------------------------------------------------------------------
#define BUFFERLEN 1000000
//---------------------------------------------------------------------------

int main(int argc, char* argv[])
{
	FILE *infile  = (FILE*) NULL;
	FILE *outfile = (FILE*) NULL;
	
	if(argc<9){
		printf("usage: %s input_file output_file x_column y_column x_low x_high y_low y_high [subsample] [headerlines]\n",argv[0]);		
		exit(1);
	}

	size_t xcol = (size_t)atoi(argv[3]);
	size_t ycol = (size_t)atoi(argv[4]);	
	xcol = xcol - 1;//User uses 1 based indexing
	ycol = ycol - 1;//User uses 1 based indexing

	double xlow;
	if(sscanf(argv[5],"%lf",&xlow) !=1 ){
		printf("Invalid x_low number %s\n",argv[5]);
		exit(1);
	}
	double xhigh;
	if(sscanf(argv[6],"%lf",&xhigh) !=1 ){
		printf("Invalid x_high number %s\n",argv[6]);
		exit(1);
	}
	double ylow;
	if(sscanf(argv[7],"%lf",&ylow) !=1 ){
		printf("Invalid x_low number %s\n",argv[7]);
		exit(1);
	}
	double yhigh;
	if(sscanf(argv[8],"%lf",&yhigh) !=1 ){
		printf("Invalid x_high number %s\n",argv[8]);
		exit(1);
	}

	size_t subsample=1;
	if(argc>=10){
		subsample = (size_t)atoi(argv[9]);
		if(subsample < 1){
			printf("Invalid subsample rate %s\n",argv[9]);
			exit(1);
		}
	}

	int headerlines=0;
	if(argc>=11){
		headerlines = atoi(argv[10]);
		if(headerlines < 0){
			printf("Invalid number of header lines %s\n",argv[10]);
			exit(1);
		}
	}
	
	if ((infile=fopen(argv[1],"r"))==NULL) {
		printf("***WARNING*** cannot open file: %s \n",argv[1]);
		exit(1);
	}

	if ((outfile=fopen(argv[2],"w"))==NULL) {
		printf("***WARNING*** cannot open file: %s \n",argv[2]);
		exit(1);
	}

	std::vector<char> buf(BUFFERLEN+1);
	char* buffer   = &(buf[0]);
	
	for(int i=0;i<headerlines;i++){
		fgets(buffer,BUFFERLEN,infile);
	}

	//size_t record=headerlines;
	size_t k=0;
	while(fgets(buffer,BUFFERLEN,infile) != NULL){
		k++;
		//record++;
		if (k%subsample == 0){
			double x, y;
			std::vector<std::string> fields = fieldparsestring(buffer, " ");
			sscanf(fields[xcol].c_str(), "%lf", &x);
			sscanf(fields[ycol].c_str(), "%lf", &y);

			if (x<xlow || x>xhigh || y<ylow || y>yhigh)continue;

			if (fputs(buffer, outfile) == EOF) {
				printf("write error\n");
				exit(1);
			}
		}
	}      
	if(infile!=NULL)fclose(infile);
	if(outfile!=NULL)fclose(outfile);	
	return 0;
}
