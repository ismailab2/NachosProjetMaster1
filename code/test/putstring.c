
#ifdef CHANGED

#include "syscall.h"

void printstring(char *chaine)
{
    #if 1
        PutString(chaine);
    #endif
    
}
    
    int
    main()
    {
        char test[] = "bonjour";
        printstring(test);
        Halt();
    }

    #endif //   CHANGED