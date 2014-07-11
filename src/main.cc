#include "parser.hh"

int main(int argc, char *argv[])
{
    int i = 0;

    if (argc == 1)
        return 1;

    for (i = 1; i < argc; i++)
    {
        Parser p = Parser(argv[i]);
        p.parse(argc, argv);
    }

    return 0;
}
