/*
This source code file is licensed under the GNU GPL Version 2.0 Licence by the following copyright holder:
Crown Copyright Commonwealth of Australia (Geoscience Australia) 2015.
The GNU GPL 2.0 licence is available at: http://www.gnu.org/licenses/gpl-2.0.html. If you require a paper copy of the GNU GPL 2.0 Licence, please write to Free Software Foundation, Inc. 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.

Author: Ross C. Brodie, Geoscience Australia.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>
#include <io.h>

//---------------------------------------------------------------------------
int main(int argc, char* argv[])
{
     struct stat file_stat,*filestat;
     long loc,length,numch,k;
     FILE *fp,*fq;
     char search[200] ,replace[200] ,
          temp[200] ,*tempfile ,tempname[200];

     filestat=&file_stat;

     if(argc<4){
       printf("usage: %s input_file search_pattern replace_pattern \n",argv[0]);
       printf("       use the character ~ to represent spaces in strings\n");
         exit(1);
      }

      if ((fp =fopen(argv[1],"r+b"))==NULL) {
         printf("***WARNING*** cannot open file: %s \n",argv[1]);
         exit(1);
      }
       if ( stat(argv[1],filestat) != 0 ) {
         printf("***WARNING*** cannot read status on file: %s \n",argv[1]);
         exit(1);
      }

      char* inputtext = new char[filestat->st_size+1];
      for(length=0 ; !feof(fp) ; length++) {
          fread(&inputtext[length],1,1,fp);
      }

      strcpy(search,argv[2]);
      strcpy(replace,argv[3]);
      numch=0;
      if(fseek(fp, 0, SEEK_SET)) {
        printf("seek error ");
        delete []inputtext;
        exit(1);
      }

      strcpy(tempname,argv[1]);
      strcat(tempname,".CHANGETEXT.TMP");
      tempfile=tempname;

      if ((fq =fopen(tempfile,"w+b"))==NULL) {
         printf("***WARNING*** cannot open file: %s \n",tempfile);
         delete []inputtext;
         exit(1);
      }

      for(k=0 ; k<(int)strlen(search) ; k++) if(search[k]=='~')search[k]=' ';
      for(k=0 ; k<(int)strlen(replace) ; k++) if(replace[k]=='~')replace[k]=' ';

      for(loc=0 ; loc <(length-1) ; loc++){
         for(k=0 ; k<(int)strlen(search) ; k++){
             temp[k]=inputtext[k+loc];
         }
         if(!strcmp(search,temp)){
            fwrite(replace,strlen(replace),1,fq);
            numch++;
            loc=loc+strlen(search)-1;
         }
         else fwrite(temp,1,1,fq);
      }

      fclose(fp);
      fclose(fq);
      remove(argv[1]);
      rename(tempfile,argv[1]);
      _chmod(argv[1],filestat->st_mode);

      if(numch==0)printf("***WARNING*** FILE %s :search std::string %s not found\n",
                                argv[1],search);
      else printf("FILE %s :%s replaced by %s %5d times\n",
                                argv[1],search,replace,numch);

      delete []inputtext;
      return 0;
}
