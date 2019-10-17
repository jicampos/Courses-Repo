/*
 * CS302/ECE46810
 * Author: Javier Campos
 * Assignment 3
 * Date: 4/1/2019
 *
 * Hw3.c is a simple scheduler program that implements three different algorithms:
 *
 * 0. FCFS: First Come First Served
 * 1. SJF: Shortest Job First
 * 2. LJF: Longest Job First
 *
 * The algorithm can be specified in the command line. Once started the program will launch instances of
 * the "computeProgram_64.exe" with the parameters taken from the command line. The order they will be launch
 * is determine by this program (Hw.c).
 */
#include <windows.h>
#include <stdio.h>


typedef struct processor_data {
   int affinityMask;                /* affinity mask of this processor (just one bit set) */
   PROCESS_INFORMATION processInfo; /* process currently running on this processor */
   int running;                     /* 1 when this processor is running a task, 0 otherwise */
} ProcessorData;


/* function prototypes */
void printError(char* functionName);
void selectionSort(int *arr[], int n, int type);
void swap(int *xp, int *yp);
void printBinary(int n); // For Debugging Purposes

int main(int argc, char *argv[])
{
   int processorCount = 0;       /* the number of allocated processors */
   ProcessorData *processorPool; /* an array of ProcessorData structures */
   HANDLE *processHandles;       /* an array of handles to processes */

    int i;
    int create;
    char *processTime[argc-2][5];
    int *sortTime[argc-2];

    STARTUPINFO startInfo; // [input]
    ZeroMemory(&startInfo, sizeof(startInfo));
    startInfo.cb = sizeof(startInfo);

    PROCESS_INFORMATION processInfo; // [output]

   if (argc < 3)
   {
      fprintf(stderr, "usage, %s  SCHEDULE_TYPE  SECONDS...\n", argv[0]);
      fprintf(stderr, "Where: SCHEDULE_TYPE = 0 means \"first come first serve\"\n");
      fprintf(stderr, "       SCHEDULE_TYPE = 1 means \"shortest job first\"\n");
      fprintf(stderr, "       SCHEDULE_TYPE = 2 means \"longest job first\"\n");
      return 0;
   }


   /* read the job duration times off the command-line */
    for(i=2; i < argc; i=i+1)  {
        sortTime[i-2] = (int)atoi(argv[i]);
    }

    if(atoi(argv[1]) == 1)
        selectionSort(sortTime, argc-2, 1);
    if(atoi(argv[1]) == 2)
        selectionSort(sortTime, argc-2, 2);

    printf("Scheduling job duration times:");
    for(i=0; i < argc-2; i=i+1)  {
        sprintf(processTime[i], " %d", sortTime[i]);
        printf("%s",processTime[i]);
    }
    printf("\n");

   /* get the processor affinity mask for this process */
    DWORD_PTR processAffinityMask;   // a memory location that can hold a value
    DWORD_PTR  systemAffinityMask;   // a memory location that can hold a value
    if(GetProcessAffinityMask(GetCurrentProcess(), &processAffinityMask, &systemAffinityMask) == 0) {
        printError("GetProcessAffinityMask");
    }

   /* count the number of processors set in the affinity mask */
    unsigned char k;

    unsigned char totalBits=sizeof(processAffinityMask)*8;

    for(k=0; k < totalBits; k = k+1) {
        if( processAffinityMask & (1<< k) )
            processorCount = processorCount + 1;
    }

   /* create, and then initialize, the processor pool data structure */
    processorPool = malloc(processorCount * sizeof(ProcessorData));
    processHandles = malloc(processorCount * sizeof(HANDLE));
    int j = 0;

    for(k=0; k < totalBits; k=k+1) {
        int mask;
        if(mask = processAffinityMask & (1<< k)) {
            processorPool[j].affinityMask = mask;
            processorPool[j].running = 0;
            j=j+1;
        }
    }

   /* start the first group of processes */

    if (processorCount < argc-2)
        create = processorCount;
    else
        create = argc-2;


    for(i=0; i < create; i=i+1) {
        if (!CreateProcessA(
                    "computeProgram_64.exe",                                // name of the module to be exec. : default search is cur directory
                    processTime[i],                                        // command line to be executed
                    NULL,                                                 // default security
                    NULL,                                                // default security
                    FALSE,                                              // output flags
                    CREATE_NEW_CONSOLE|CREATE_SUSPENDED,               // dwCreationFlags = 0x00000010 - new console instead of inheriting
                    NULL,                                             // pass env vars to a child process
                    NULL,                                            //
                    &startInfo,                                     // [input] lpStartupInfo
                    &processInfo                                   // [output] process information
                    ))
        {
            printError("CreateProcessA");
        }

        printf("launched%s second job on processor with mask 0x%x\n", processTime[i], processorPool[i].affinityMask);

        processorPool[i].processInfo = processInfo; // Update data structure info
        processHandles[i] = processInfo.hThread; // Update process handle

        if(!SetProcessAffinityMask(processInfo.hProcess, processorPool[i].affinityMask)) // Set the core to run on
            printError("SetProcessAffinityMask");

        if(ResumeThread(processInfo.hThread) > 1) // start the process
            printError("ResumeThread");

        processorPool[i].running = 1;

    }

    DWORD handleCount = processorCount;
      if(argc-2 < processorCount)
         handleCount = argc-2;

   /* Repeatedly wait for a process to finish and then,
      if there are more jobs to run, run a new job on
      the processor that just became free. */

   while (1)
   {
      DWORD result;

      /* check that there are still processes running, if not, quit */

      if(create == argc-2){

        //printf("Started all processes\n");

        HANDLE *newHandle = malloc(handleCount * sizeof(HANDLE));

        j = 0;
        for(i=0;i<processorCount;i++){
            if(processorPool[i].running==1) {
                newHandle[j]=processorPool[i].processInfo.hThread;
                j=j+1;
            }
        }

        if (WAIT_FAILED == (result = WaitForMultipleObjects(handleCount, newHandle, TRUE, INFINITE)))
            printError("WaitForMultipleObjects");

        return 0;

      }

      /* wait for one of the running processes to end */

      if (WAIT_FAILED == (result = WaitForMultipleObjects(handleCount, processHandles, FALSE, INFINITE)))
         printError("WaitForMultipleObjects");

      /* close the handles of the finished process and update the processorPool array */
      CloseHandle(processorPool[result].processInfo.hProcess);
      CloseHandle(processHandles[result]);
      processorPool[result].running=0;

      /* check if there is another process to run on the processor that just became free */

      if(create < argc-2) {

          if (!CreateProcessA(
                        "computeProgram_64.exe",                                // name of the module to be exec. : default search is cur directory
                        processTime[create],                                   // command line to be executed
                        NULL,                                                 // default security
                        NULL,                                                // default security
                        FALSE,                                              // output flags
                        CREATE_NEW_CONSOLE|CREATE_SUSPENDED,               // dwCreationFlags = 0x00000010 - new console instead of inheriting
                        NULL,                                             // pass env vars to a child process
                        NULL,                                            //
                        &startInfo,                                     // [input] lpStartupInfo
                        &processInfo                                   // [output] process information
                        ))
            {
                printError("CreateProcessA");
            }

            printf("launched%s second job on processor with mask 0x%x\n", processTime[create], processorPool[result].affinityMask);

            processorPool[result].processInfo = processInfo; // Update data structure info
            processHandles[result] = processInfo.hThread; // Update process handle

            if(!SetProcessAffinityMask(processInfo.hProcess, processorPool[result].affinityMask)) // Set the core to run on
                printError("SetProcessAffinityMask");

            if(ResumeThread(processInfo.hThread) > 1) // start the process
                printError("ResumeThread");

            processorPool[result].running = 1;

            create=create+1;
      }
   }
   return 0;
}



/****************************************************************
   The following function can be used to print out "meaningful"
   error messages. If you call a Windows function and it returns
   with an error condition, then call this function right away and
   pass it a string containing the name of the Windows function that
   failed. This function will print out a reasonable text message
   explaining the error.
*/
void printError(char* functionName)
{
   LPVOID lpMsgBuf;
   int error_no;
   error_no = GetLastError();
   FormatMessage(
         FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM,
         NULL,
         error_no,
         MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), /* default language */
         (LPTSTR) &lpMsgBuf,
         0,
         NULL
   );
   /* Display the string. */
   fprintf(stderr, "\n%s failed on error %d: ", functionName, error_no);
   fprintf(stderr, (const char*)lpMsgBuf);
   /* Free the buffer. */
   LocalFree( lpMsgBuf );
}

void swap(int *xp, int *yp) {
    int temp = *xp;
    *xp = *yp;
    *yp = temp;
}

void selectionSort(int *arr[], int n, int type) {
    int i, j, idx;

    // One by one move boundary of unsorted subarray
    for (i = 0; i < n-1; i++) {
        // Find the minimum or maximum element in unsorted array
        idx = i;
        for (j = i+1; j < n; j++) {
          if(type == 1) {
            if (arr[j] < arr[idx])
                idx = j;
          }
          else {
              if (arr[j] > arr[idx])
                    idx = j;
          }
        }

        // Swap the found minimum element with the first element
        swap(&arr[idx], &arr[i]);
    }
}
