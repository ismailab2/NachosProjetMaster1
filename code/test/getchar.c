#ifdef CHANGED;

#include "syscall.h"

void echo(int n)
{
    #if 1
        int i;
        char c;
        while (i < n) {
            c = GetChar();
            PutChar(c);
            i++;
        }
    #endif
    }
    
    int
    main()
    {
        echo(10);
        return 0;
    }

#endif //   CHANGED