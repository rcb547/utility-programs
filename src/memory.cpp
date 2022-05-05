/*
This source code file is licensed under the GNU GPL Version 2.0 Licence by the following copyright holder:
Crown Copyright Commonwealth of Australia (Geoscience Australia) 2015.
The GNU GPL 2.0 licence is available at: http://www.gnu.org/licenses/gpl-2.0.html. If you require a paper copy of the GNU GPL 2.0 Licence, please write to Free Software Foundation, Inc. 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.

Author: Ross C. Brodie, Geoscience Australia.
*/

#include "stdio.h"
#include "windows.h"
#include "general_utils.h"

class cLogger glog; //The global instance of the log file manager

int main()
{
  MEMORYSTATUS memstatus;
  GlobalMemoryStatus(&memstatus);

  printf("Total physical memory: %d Mb\n",memstatus.dwTotalPhys/1000000);  	
  printf("Total page file memory: %d Mb\n",memstatus.dwTotalPageFile/1000000);  	
  printf("Total virtual memory: %d Mb\n",memstatus.dwTotalVirtual/1000000);  	
  printf("\n");  	

  printf("Available physical memory: %d Mb\n",memstatus.dwAvailPhys/1000000);  	
  printf("Available page file memory: %d Mb\n",memstatus.dwAvailPageFile/1000000);  	
  printf("Available virtual memory: %d Mb\n",memstatus.dwAvailVirtual/1000000);  	
  printf("\n");  	
  
  printf("Used physical memory: %d Mb\n",(memstatus.dwTotalPhys-memstatus.dwAvailPhys)/1000000);  	
  printf("Used page file memory: %d Mb\n",(memstatus.dwTotalPageFile-memstatus.dwAvailPageFile)/1000000);  	
  printf("Used virtual memory: %d Mb\n",(memstatus.dwTotalVirtual-memstatus.dwAvailVirtual)/1000000);  	
  printf("\n");  	

  printf("Memory used: %d%%\n",memstatus.dwMemoryLoad);  	

  prompttocontinue();
  
  return (int)memstatus.dwMemoryLoad;
 
}
