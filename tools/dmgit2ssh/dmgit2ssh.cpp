
#include "execute.h"

int main( int argc, char* argv[] )
{
    Iexecute* execute = executeGetModule();

    if (NULL != execute)
    {
        std::string strGit = execute->exec("git remote -v");
    }

    return 0;
}
