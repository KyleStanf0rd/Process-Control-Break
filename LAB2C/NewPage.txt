#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

//NEWPAGE FUNCTION
void NewPage(float PagegTotal, float PagefTotal, float PagenetTotal, int pgnum, int LK, FILE *outFile){
    fprintf(outFile, "\n%65s%15.2f %12.2f %13.2f\n", "Page Totals: ", PagegTotal, PagefTotal, PagenetTotal);
    fprintf(outFile,"\n\n\n\n\n\n\n\n\n%110s%i\n%s\n","Page ", pgnum, "---------------------------------------------------------------------------------------------------------------");
    fprintf(outFile,"%42s%s%s%7s%s%13s%12s%s%s", "\t\t\tACME\n", "Emp.No.\t", "Given\t", "\tSurname\t", "Dept.\t", "YTD ($)\t", "Gross ($)\t", "FICA Tax\t", "Net\t\n\n" );
    //*LK = 0;
    //*pgnum = *pgnum+1;
    //*PagegTotal = 0.0;
    //*PagefTotal = 0.0;
    //*PagenetTotal = 0.0;
}
