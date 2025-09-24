#ifdef CHANGED

#include "copyright.h"
#include "utility.h"
#include "console.h"
#include "synch.h"
#include "consoledriver.h"

extern Console *console;
extern Semaphore *readAvail;
extern Semaphore *writeDone;

// Écrit un caractère sur la console (comme putchar)
void PutChar(int ch)
{
    if (ch == EOF) return;

    // on doit savoir si on implemente un PutChar qui termin s'il lue  'q' 
    /*
    if (ch == 'q') {
        printf("Au revoir !\n");
    }
    */

    /*
    // encadrer le caractère comme dans ConsoleTest CHANGED
    if (ch != '\n') {
        console->TX('<'); 
        writeDone->P();

        console->TX(ch); 
        writeDone->P();

        console->TX('>'); 
        writeDone->P();
    } else {
        console->TX(ch); writeDone->P();
    }

   */


   console->TX(ch); 
   writeDone->P();

}

// Lit un caractère depuis la console (comme getchar)
int GetChar()
{
    char ch;
    readAvail->P();       // attend qu'un caractère soit disponible
    ch = console->RX();   // lit le caractère

    if (ch == EOF) return EOF;
    return ch;
}

#endif // CHANGED