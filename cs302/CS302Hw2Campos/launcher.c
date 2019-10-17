/*
 * CS302/ECE46810
 * Author: Javier Campos
 * Assignment: 2
 * Date: 2/18/2019
 *
 * launcher.c uses the environmental variables and common functions in Windows to run several programs.
 * This launcher program repeatedly asks users to create processes from the following programs:
 *
 * 1. Notepad
 * 2. Wordpad
 * 3. CMD Shell
 * 4. Calculator
 * 5. Explorer
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

// function prototype
void printError(char* functionName);

int main()
{
    int input = 1;

    #define NUMBER_OF_PROCESSES 5
    //LPSTR lpCommandLine;
    char *lpCommandLine[NUMBER_OF_PROCESSES][256];

    PROCESS_INFORMATION processInfo; // [output]

    STARTUPINFO startInfo; // [input]
    ZeroMemory(&startInfo, sizeof(startInfo));
    startInfo.cb = sizeof(startInfo);

    // set lpCommandLine based on environmental variables
    sprintf(lpCommandLine[0], "%s\\system32\\notepad.exe", getenv("SystemRoot"));
    sprintf(lpCommandLine[1], "%s\\Windows NT\\Accessories\\wordpad.exe", getenv("ProgramFiles"));
    sprintf(lpCommandLine[2], "%s /t:f9", getenv("COMSPEC"));
    sprintf(lpCommandLine[3], "%s\\system32\\calc.exe", getenv("SystemRoot"));
    sprintf(lpCommandLine[4], "%s\\explorer.exe", getenv("SystemRoot"));

    do {

        printf("Please make a choice from the following list.\n");
        printf(" 0: Quit\n");
        printf(" 1: Run Notepad\n");
        printf(" 2: Run Wordpad\n");
        printf("*3: Run cmd shell\n");
        printf(" 4: Run Calculator\n");
        printf(" 5: Run Explorer\n");
        printf("Enter your choice now: ");
        scanf("%d",&input);


        if(input == 0) { return 0; }
        if(input == 3)
        {
            startInfo.lpTitle = "What is your command?";
            // if not specified dwX, dwY and dwFillAttribute is ignored
            startInfo.dwFlags = STARTF_USEPOSITION; // | STARTF_USEFILLATTRIBUTE;
            startInfo.dwX = 0;
            startInfo.dwY = 0;
            // startInfo.dwFillAttribute = FOREGROUND_INTENSITY| FOREGROUND_BLUE| BACKGROUND_INTENSITY| BACKGROUND_RED| BACKGROUND_GREEN| BACKGROUND_BLUE; <---- same command can be done through terminal inputs
            /*
            * Modifies the environment of the running process (not parent)
            * Affects the future, when the process ends it goes back to the past environment that it came from
            */
            if(_putenv("PROMPT=Speak to me$G"))
            {
                printf("Error accessing environment variable: PROMPT\n");
            }
        }

        if (!CreateProcessA(
                    NULL,                          // name of the module to be exec. : default search is cur dir
                    lpCommandLine[input -1],      // command line to be executed
                    NULL,                        // default security
                    NULL,                       // default security
                    FALSE,                     // output flags
                    CREATE_NEW_CONSOLE | NORMAL_PRIORITY_CLASS, // dwCreationFlags = 0x00000010 - new console instead of inheriting
                    NULL,                                      // pass env vars to a child process
                    NULL,                                     //
                    &startInfo,                              // [input] lpStartupInfo
                    &processInfo                            // [output] process information
                    ))
        {
            printError("CreateProcess");
        }
        else
        {
            printf("Started program %d with pid = %d \n", input, (int)processInfo.dwProcessId);
        }

        if(input == 3)
        {
            printf("  waiting for program 3 to terminate...\n");
            if(WaitForSingleObject(processInfo.hProcess, INFINITE))
            {
                printf("  Error while waiting for Process Handle\n");
            }

            PDWORD exitCode;
            if(GetExitCodeProcess(processInfo.hProcess, exitCode))
            {
                printf("  program 3 exited with return value %d\n", (int)exitCode);
                // close the handles since we do not need them
                CloseHandle(processInfo.hThread);
                CloseHandle(processInfo.hProcess);
            }
        }

        // reset startInfo
        ZeroMemory(&startInfo, sizeof(startInfo));
        startInfo.cb = sizeof(startInfo);

        printf("\n");

    } while(1);

    return 0;
}


void printError(char* functionName)
{
   LPVOID lpMsgBuf;
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
    fprintf(stderr, (const char*)lpMsgBuf);
    // Free the buffer.
    LocalFree( lpMsgBuf );
    //ExitProcess(1);  // terminate the program
}//printError
