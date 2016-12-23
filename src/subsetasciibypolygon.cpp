/*
This source code file is licensed under the GNU GPL Version 2.0 Licence by the following copyright holder:
Crown Copyright Commonwealth of Australia (Geoscience Australia) 2015.
The GNU GPL 2.0 licence is available at: http://www.gnu.org/licenses/gpl-2.0.html. If you require a paper copy of the GNU GPL 2.0 Licence, please write to Free Software Foundation, Inc. 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.

Author: Ross C. Brodie, Geoscience Australia.
*/

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <vector>
using namespace std;

#include "general_utils.h"
#include "file_utils.h"
#include "asciicolumnfile.h"
#include "polygon.h"

int main(int argc, char* argv[])
{	
	FILE *outfile = (FILE*) NULL;
	size_t colx,coly,subsamplerate;	
			
	if(argc != 7){
		printf("usage: %s input_file output_file polygon_file x_column y_column subsample_rate\n",argv[0]);		
		exit(1);
	}

	//Parse args
	std::string infilename = argv[1];
			
	if ((outfile =fileopen(argv[2],"w"))==NULL) {
		printf("***WARNING*** cannot open output file: %s \n",argv[2]);
		exit(1);
	}
					
	cPolygon poly(argv[3]);	
	colx = (size_t)atoi(argv[4]);
	coly = (size_t)atoi(argv[5]);
	subsamplerate = (size_t)atoi(argv[6]);
	
	colx = colx - 1;//User uses 1 based indexing
	coly = coly - 1;//User uses 1 based indexing
	////////////////////////////////////////////////////////////////
	cPoint p;
	cAsciiColumnFile asc(infilename);
	size_t k = 0;
	while(asc.readnextrecord()){	
		if (k%subsamplerate == 0){
			asc.parserecord();
			asc.getcolumn(colx, p.x);
			asc.getcolumn(coly, p.y);
			if (poly.isinside(p)){
				fputs(asc.currentrecordstring(), outfile);
				fputs("\n", outfile);
			};
		}
		k++;
	}
	if(outfile!=NULL)fclose(outfile);		
	return 0;
}