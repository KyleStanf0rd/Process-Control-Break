#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
int main(){
    FILE *outFile;
    FILE *inFile;
    float CalcGross(float, float);
    float CalcFica(float, float);
    void NewPage(float,float,float,int,int, FILE*);
    char resp = 'Y';
    char fileInName[20];//Lab2Readfile.txt
    char fileOut[20];

    //Name of input file
    printf("Enter the name and path of the input file[Max 25 characters]: ");
    scanf("%s", fileInName);
    inFile=fopen(fileInName, "r"); //open file to read
    //Checking to ensure file exists
    if(inFile == NULL){
        printf("Input file DNE! Program Terminating.");
        exit(1);
    }

    //Name of Output file
    printf("Enter the name and path of the output file to hold Report : ");
    scanf("%s", fileOut);
    //Checking if the File is already made.
    if((outFile = fopen(fileOut, "r"))!= NULL){
        printf("\nA file by name %s exists.\n", fileOut);
        printf("Do you wish to overwrite with a new entry? (Y or N): ");
        scanf("%*c %c", &resp);
        //If you don't want to overwrite, file terminates
        if((resp == 'n') || (resp == 'N')){
            fclose(outFile);
            printf("\nProgram aborted to prevent overwrite!");
            exit(1);
        }
    }

    //Opening Boutput File!!
    outFile = fopen(fileOut, "w");
    if(outFile == NULL){
        printf("Could not create the output file! Program terminating.");
        exit(1);
    }
//Printing cover page/////////////////////////////////////////////////////////////////////////////////////////////
    fprintf(outFile, "%58s%68s", "\t\t   ACME Sports Inc.\n", "\t\t  We are the best, you use the best!\n");
    fprintf(outFile,"%42s%s%s%s%s%13s%12s%s%s", "\t\t\tACME\n", "Emp.No.\t", "Given\t", "\tSurname\t", "Dept.\t", "YTD ($)\t", "Gross ($)\t", "FICA Tax\t", "Net\t\n\n" );

    int LK = 0;
    int pgnum = 0;
    int maxLines = 4;
    float PagegTotal = 0.0;
    float PagefTotal = 0.0;
    float PagenetTotal = 0.0;
    int recProcessed = 0;
    float Rgross = 0.0;
    float Rfica = 0.0;
    float Rnet = 0.0;
    char SaveKey[20];
    char RecKey;
    float DepGTotal = 0.0;
    float DepFTotal = 0.0;
    float DepNetTotal = 0.0;
    //Things I need for the scan
    int empNum;
    char Given[15];//Max First Name limit is 15
    char surname[20];//Max Surname limit is 20
    char department[20];
    float ytd;
    float payrate;
    float hourswkd;
    float Tgross = 0.0;
    float Tnet = 0.0;
    float netTotal = 0.0;
    float TFica = 0.0;
    while((fscanf(inFile, "%i%s", &empNum, surname)) != EOF){
        fscanf(inFile, "%s", Given);
        fscanf(inFile, "%s", department);
        fscanf(inFile, "%f", &ytd);
        fscanf(inFile, "%f", &payrate);
        fscanf(inFile, "%f", &hourswkd);
        //CALCULATE PAYROLL//////////////
        if(pgnum == 0){
        float gross = 0.0;
        strcpy(SaveKey, department);
        pgnum = 1;
        }
        float gross = CalcGross(hourswkd, payrate);
        float Ftax = CalcFica(gross,ytd);
        //Department control break//
        netTotal = gross - Ftax;

        if(strcmp(SaveKey, department) != 0){
        fprintf(outFile, "\n%71s%9.2f %12.2f %13.2f\n\n", "Department Totals: ", DepGTotal, DepFTotal, DepNetTotal);
            DepFTotal = 0.0;
            DepGTotal = 0.0;
            DepNetTotal = 0.0;
            strcpy(SaveKey, department);
            }
        DepFTotal += Ftax;
        DepGTotal += gross;
        DepNetTotal += netTotal;
        //NEW PAGE//
        if(LK >= maxLines){
        NewPage(PagegTotal, PagefTotal, PagenetTotal, pgnum, LK, outFile);
        LK = 0;
        pgnum = pgnum+1;
        PagegTotal = 0.0;
        PagefTotal = 0.0;
        PagenetTotal = 0.0;
        }
        ytd = netTotal + ytd;
        fprintf(outFile, "%3i %18s %14s %12s %15.2f %13.2f \t%8.2f %13.2f\n",empNum, Given, surname, department, ytd, gross, Ftax, netTotal);
        //Getting totals on Fica Tax and Gross($)
        PagegTotal += gross;
        PagefTotal += Ftax;
        PagenetTotal += netTotal;
        recProcessed = recProcessed+1;
        LK= LK+1;
        //Getting overall TOTALS
        Tgross += gross;
        Tnet += netTotal;
        TFica += Ftax;

    }

fprintf(outFile, "\n%71s%9.2f %12.2f %13.2f\n\n", "Department Totals: ", DepGTotal, DepFTotal, DepNetTotal);
fprintf(outFile, "\n%65s%15.2f %12.2f %13.2f\n", "Page Totals: ", PagegTotal, PagefTotal, PagenetTotal);
fprintf(outFile,"\n\n\n\n\n\n\n\n\n%110s%i\n%s\n","Page ", pgnum, "---------------------------------------------------------------------------------------------------------------");

//Report Summary////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
pgnum = pgnum + 1;
fprintf(outFile,"\n\n\t\t%54s\n\n%s%d\n%s%0.2f\n%s%0.2f\n%s%0.2f", "Report Summary", "Records Processed : ", recProcessed, "Total Gross:  $", Tgross, "Total Net :  $", Tnet, "Total Fica :  $", TFica);
fprintf(outFile,"\n\n\n\n\n\n\n%110s%i\n\n","Page ", pgnum);
//Closing Files
fclose(inFile);
fclose(outFile);
return 0;
}
