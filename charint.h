#ifndef CHARINT
#define CHARINT
class CharInt
{
    public:
        CharInt (char c[]);
        virtual ~CharInt();
        long int to_int(char*c);
        double to_float(char*c);
        long int integ;
        double dfloat;

    private:
        long int integ0;        
        char txt[];
};

#endif

