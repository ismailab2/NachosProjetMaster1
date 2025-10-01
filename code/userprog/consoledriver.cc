#ifdef CHANGED

#include "copyright.h"
#include "system.h"
#include "consoledriver.h"
#include "synch.h"

static Semaphore *readAvail;
static Semaphore *writeDone;

static void ReadAvailHandler(void *arg) { (void) arg; readAvail->V(); }
static void WriteDoneHandler(void *arg) { (void) arg; writeDone->V(); }

ConsoleDriver::ConsoleDriver(const char *in, const char *out)
{
    readAvail = new Semaphore("read avail", 0);
    writeDone = new Semaphore("write done", 0);
    console = new Console (in, out, ReadAvailHandler, WriteDoneHandler, NULL);
}

ConsoleDriver::~ConsoleDriver()
{
    delete console;
    delete writeDone;
    delete readAvail;
}

void ConsoleDriver::PutChar(int ch)
{
    if (ch != '\n') {
        console->TX('<'); 
        writeDone->P();

        console->TX(ch); 
        writeDone->P();

        console->TX('>'); 
        writeDone->P();
    }
}

int ConsoleDriver::GetChar()
{
    int ch = 0;
    readAvail->P ();        // wait for character to arrive
    ch = console->RX ();
    return ch;
}



void ConsoleDriver::PutString(const char *s)
{
    if (s == nullptr) return;

    for (int i =0; s[i] != '\0'; i++){

        PutChar(s[i]); // on reutilise la fonction putchar pour la simplication du code.
    }
}

void ConsoleDriver::GetString(char *s, int n)
{
    if (s == nullptr || n<0) return;

    for (int i=0; i<n; i++){
        s[i] = GetChar();
    }

}


unsigned ConsoleDriver::copyStringFromMachine(int from, char *to, unsigned size)
{
    if (to == nullptr || size == 0) return 0;

    int value ;// ReadMem écrit dans un int
    bool success;
    unsigned i=0;
    for (; i<size-1; i++){
        success = machine->ReadMem(from+i, 1 , &value);

        if(!success){
            break; //erreur de lecture
        }

        to[i]=(char) value;
        if (to[i] == '\0'){
            return i; // fin de chaîne côté utilisateur
        }

    }
    to[i]='\0';
    return i;
}

unsigned ConsoleDriver::copyStringToMachine(char* from, int to, unsigned size)
{
    if (from == nullptr || size == 0) return 0;

    int value ;// ReadMem écrit dans un int
    bool success;
    unsigned i=0;

    for (; i<size-1; i++){

        value = from[i];

        success = machine->WriteMem(to+i,1,value);

        if(!success){
            break;
        }

        if(value == '\0'){
            return i;
        }
    }
    machine->WriteMem(to+i,1,'\0');
    return i;
}




#endif // CHANGED