
#ifdef CHANGED

#include "syscall.h"
    
    int
    main()
    {
        char test[] = "bonjour";
        PutString(test);
        Halt();
    }

    #endif //   CHANGED