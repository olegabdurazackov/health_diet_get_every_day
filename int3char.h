#ifndef INT3CHAR_H
#define INT3CHAR_H

class IntChar
{
    public:
        IntChar (int);
        virtual ~IntChar();
        char text[];

    private:
        int integ;
        char txt[];
};

#endif
/* author by olab@email.su
 * usage:

#include <iostream>
#include <string.h>
#include "intchar.h"
#include "intchar.cpp"

int main (int argc, char const* argv[])
{
    IntChar ops(1234);

    std::cout << "begin" << ops.text <<"\n";
    return 0;
}
*/
