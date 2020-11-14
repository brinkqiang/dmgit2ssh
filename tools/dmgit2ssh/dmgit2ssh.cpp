
#include "execute.h"

int main( int argc, char* argv[] )
{
    Iexecute* execute = executeGetModule();

    if (NULL != execute)
    {
        execute->exec("echo cmd");
    }

    return 0;
}
