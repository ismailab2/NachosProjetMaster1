#ifdef CHANGED;

#include "syscall.h"

    void
    print(char* string){
        int i;
        for(i=0; string[i]!='\0'; i++){
            PutChar(string[i]);
        }
    }

    int
    main()
    {
        char string[255];
        GetString(string,10);
        print(string);
        Halt();
    }

#endif //   CHANGED