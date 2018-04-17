/*
This source code file is licensed under the GNU GPL Version 2.0 Licence by the following copyright holder:
Crown Copyright Commonwealth of Australia (Geoscience Australia) 2015.
The GNU GPL 2.0 licence is available at: http://www.gnu.org/licenses/gpl-2.0.html. If you require a paper copy of the GNU GPL 2.0 Licence, please write to Free Software Foundation, Inc. 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.

Author: Ross C. Brodie, Geoscience Australia.
*/

#include <cstdlib>
#include <cstring>
#include <iostream>

#if defined _WIN32
#include <sys/types.h>	
#include <sys/stat.h>	
#include <io.h>	
#else
#include <dirent.h>
#include <sys/types.h>	
#include <sys/stat.h>	
#include <unistd.h>	
#endif

#include "general_utils.h"
#include "file_utils.h"

#define MAXFNAMELEN 256

int renameifpermission( const std::string name, const std::string newname );

int main(int argc, char* argv[])
{     		
	std::string search;
	std::string replace;	
	
	// READ RUN STRING AND INTERPRET//////////////////////////////////////////////////////////////////

	// CHECK FOR TOO FEW / TOO MANY ARGUMENTS
	if(argc<3){
		std::cout <<"usage: "<<argv[0]<<" [-i] [-start] [-end] file_search_pattern file_replace_pattern\n\n";				
		std::cout << "\nThis program is renames files/directories/links, in the CURRENT DIRECTORY, the names of which contain the SEARCH PATTERN, to the corrosponding name containing the REPLACE PATTERN.\n\n";
		std::cout << "The USER MUST have WRITE permission\n\n";
		std::cout << "-i          - prompts for confirmation\n\n";
		std::cout << "-start      - only at the start of the filename\n";
		std::cout << "-end        - only at the end of the filename\n";
		std::cout << "-start -end - either at the start or end of the filename\n";
		std::cout << "\n\tDo NOT use the * character as a wildcard\n";
		exit(0);
	}

	// CHECK FOR INTERACTIVE CONFIRMATION
	int nopt=0;
	bool confirm=false;
	bool start=false;
	bool end=false;	
	for(size_t i=1; i<(size_t)argc; i++){	
		std::string tmp = argv[i];
		if(tmp == "-i"){
			confirm = true;
			nopt++;
		}
		if(tmp == "-start"){
			start = true;
			nopt++;
		}
		if(tmp == "-end"){
			end = true;
			nopt++;
		}		
	}		
	search  = argv[1+nopt];
	replace = argv[2+nopt];
	
	cDirectoryAccess d;
	std::string searchpattern = "*" + search + "*";	 
	std::vector<std::string> list = d.getfilelist(searchpattern);	 
	// GET DIRECTORY ENTRIES
	for(size_t i=0; i<list.size(); i++){
		std::string file=list[i];

		std::string newfile = file;
		int numch=0;
		size_t pos = newfile.find(search);
		while(pos != std::string::npos){ 					
			if(start==true && end==true){
				if(pos!=0 && pos!=newfile.size()-search.size())break;
			}
			if(start==true  && end==false && pos>0) break;
			if(start==false && end==true  && pos!=newfile.size()-search.size()) break;					
			newfile.replace(pos,search.size(),replace);
			pos = newfile.find(search);
			numch++;
		};
		
		// IF NECESSARY RENAME FILE
		if(numch>0){			
			if(confirm){
				char yesno = 'y';
				std::cout << "RENAME " << file << " TO " << newfile << " (y/n): ";
				std::cin >> yesno;
				if(yesno == 'y' || yesno == 'Y'){
					renameifpermission(file,newfile);
				}
			}
			else{			
				renameifpermission(file,newfile);
			}
		}

	}  	
	return 0;
}

//////////////////////////////////////////////////////////////////////////////////

//   ROUTINE TO RENAME FILE AND GIVE WARNINGS
//   RETURNS 0 ON SUCCESS
int renameifpermission( const std::string name, const std::string newname )
{

	struct stat filestat;
	char yesno;

	// CHECK FOR WRITE PERMISSION
#if defined _WIN32
	if(_access(name.c_str(),02)){
#else
	if(access(name.c_str(),02)){
#endif
		std::cout << name << " - NO WRITE PERMISSION \n";
		return(-1);
	}

	// CHECK IF NEW FILE ALREADY EXISTS
#if defined _WIN32
	if(!_access(newname.c_str(),00)){
#else
	if(!access(newname.c_str(),00)){
#endif     
		std::cout << newname << " ALREADY EXISTS - OVERWRITE WITH " << name << " (y/n): ";
		std::cin >> yesno;
		if(yesno == 'n' || yesno == 'N'){
			return(-1);
		}
		else{
			if(remove( newname.c_str() )){
				perror( newname.c_str() );
				return -1;
			}
		}		
	}

	// CAN STATUS BE READ
	if(stat(name.c_str(),&filestat) != 0 ) {
		perror(name.c_str());
		std::cout << name << " - CANNOT READ PERMISSION STATUS: \n";
		return(-1);
	}

	// CHECK FOR DIRECTORY
	if(filestat.st_mode & S_IFDIR) {
		std::cout << name << " IS A DIRECTORY - RENAME (y/n): ";
		std::cin >> yesno;
		if(yesno == 'n' || yesno == 'N') return(-1);
	}

	// RENAME
	if(rename(name.c_str(),newname.c_str())){
		perror(newname.c_str());
		return(-1);
	}
	else{
		std::cout << name << " RENAMED " << newname << "\n";
		return(0);
	}

}

