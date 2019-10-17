/*
     CS302/ECE46810
     Author: Javier Campos
     Assignment: 4
     Date: 4/26/2019
*/
/*
     This program accepts commands that cause it to perform virtual memory
     operations. The commands are read from standard input, but it is better
     to put the commands in a "script file" and use the operating system's
     command line to redirect the script file to this program's standard input
     (as in "C:\VMdriver < VMcmds.txt").

     The commands that this program accepts are of the form

     time, vmOp, vmAddress, units, access

     The five parameters have the following meaning:

     time - Seconds to wait after reading the command before performing the VM operation.
     vmOp - Code that represents the VM operation to perform.
     vmAddress - virtual memory address (in hex) where the VM operation is to be performed
     units - The number of units to use in the VM operation.
             For reserving memory, each unit represents 65536 bytes of memory.
             For committing memory, each unit represents 4096 bytes of memory.
     access - Code that represents the access protection.

     The vmOp codes and their meanings are:
     1 - Reserve a region of virtual memory.
     2 - Commit a block of pages.
     3 - Touch pages in a block.
     4 - Lock a block of pages.
     5 - Unlock a block of pages.
     6 - Create a guard page.
     7 - Decommit a block of pages.
     8 - Release a region.

     The access codes and their meaning are:
     1 - PAGE_READONLY
     2 - PAGE_READWRITE
     3 - PAGE_EXECUTE
     4 - PAGE_EXECUTE_READ
     5 - PAGE_EXECUTE_READWRITE
     6 - PAGE_NOACCESS

     Most of the commands are described in the file
        "Virtual Memory from 'Beginning Windows NT Programming' by Julian Templeman.pdf".
     The only command not mentioned there is the "Touch pages in a block" command. This means
     that you should access (read) a memory location from each page in a specified block.

     Be absolutely sure that you check for any errors created by the VM operations
     since you will be trying to cause errors.

     This program should create a process that runs the program VMmapper.exe so that
     you can observe the memory operations as they happen. The program VMmapper takes
     a PID on its command line and then it repeatedly maps and displays (once a second)
     the virtual memory space of the process with that PID. This program should pass on
     the command line its own PID to the VMmapper program.

     When this program has completed all of its operations, it goes into an infinite
     loop.
*/
#include <windows.h>
#include <stdio.h>
#include <string.h>

// prototype for the function, defined below, that prints err messages
void printError(char* functionName);

int main(int argc, char *argv[])
{
   int time, vmOp, units, access;
   LPVOID vmAddress;

   SIZE_T reserve = 65536;
   SIZE_T release = 4096;
   int i;

   STARTUPINFO startInfo; // [input]
   ZeroMemory(&startInfo, sizeof(startInfo));
   startInfo.cb = sizeof(startInfo);
   PROCESS_INFORMATION processInfo; // [output]

   // Get Process ID
   LPSTR ProcPID = GetCurrentProcessId();
   char cmdLine[256];
   sprintf(cmdLine, " %d", ProcPID);

   // Create process
   if( !CreateProcess("VMMapper.exe", cmdLine, NULL, NULL, TRUE,
                      NORMAL_PRIORITY_CLASS | CREATE_NEW_CONSOLE,
                      NULL, NULL, &startInfo, &processInfo)) {
       printError("CreateProcess");
   }

   Sleep(5000);  // give VMmapper.exe time to start

   // Process loop
   printf("next VM command: ");
   while(scanf("%d%d%p%d%d", &time, &vmOp, &vmAddress, &units, &access) != EOF)
   {
      // wait until it is time to execute the command
      Sleep(time*1000);

      DWORD flProtect;

      // Determine memory protection from access in VMcmds.txt
      if(access == 1){
        flProtect = PAGE_READONLY;
      } else if(access == 2) {
        flProtect = PAGE_READWRITE;
      } else if(access == 3) {
        flProtect = PAGE_EXECUTE;
      } else if(access == 4) {
        flProtect = PAGE_EXECUTE_READ;
      } else if(access == 5) {
        flProtect = PAGE_EXECUTE_READWRITE;
      } else {
        flProtect = PAGE_NOACCESS;
      }

      // Parse the command and execute it
      switch (vmOp)
      {
         case 1:  // Reserve a region
            VirtualAlloc(vmAddress, reserve, MEM_RESERVE, flProtect);
            break;
         case 2:  // Commit a block of pages
            VirtualAlloc(vmAddress, units, MEM_COMMIT, flProtect);
            break;
         case 3:  // Touch pages in a block
             for (i = 0; i < units; i++){
                 printf("Touching 0x%p\n", (char *)vmAddress + 4096 * i);
             }
            break;
         case 4:  // Lock a block of pages
            VirtualLock(vmAddress, units);
            break;
         case 5:  // Unlock a block of pages
            VirtualUnlock(vmAddress, units);
            break;
         case 6:  // Create a guard page
            VirtualAlloc(vmAddress, units, PAGE_GUARD, flProtect);
            break;
         case 7:  // Decommit a block of pages
            VirtualFree(vmAddress, units, MEM_DECOMMIT);
            break;
         case 8:  // Release a region
            VirtualFree(vmAddress, release, MEM_RELEASE);
            break;
      }//switch
      printf("Processed %d %d 0x%p %d %d\n", time, vmOp, vmAddress, units, access);
      printf("next VM command: ");
   }//while

   while (1) Sleep(1000); // spin until killed

   return 0;
}//main()



void printError(char* functionName)
{   LPVOID lpMsgBuf;
    int error_no;
    error_no = GetLastError();
    FormatMessage(
         FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM,
         NULL,
         error_no,
         MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), // Default language
         (LPTSTR) &lpMsgBuf,
         0,
         NULL
    );
    // Display the string.
    fprintf(stderr, "\n%s failed on error %d: ", functionName, error_no);
    fprintf(stderr, lpMsgBuf);
    MessageBox(NULL, lpMsgBuf, "Error", MB_OK);
    // Free the buffer.
    LocalFree( lpMsgBuf );
}//printError()
