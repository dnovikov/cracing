#include <iostream>
#include <string>

#include "game.hpp"

using namespace std;


int main(int argc, char *argv[]) {
    Game game;
    std::string cli_arg;
    unsigned int seed = 1;

    for (int i = 1; i < argc; i++) {
        cli_arg.assign(argv[i]);

        if (!cli_arg.find("--help")) {
            printf("Arguments:\n");
            printf("  --help        Print this message\n");
            printf("  --rand=<int>  Initialize random numbers generator (essentially your track number)\n");
            return 0;
        } else if (!cli_arg.find("--rand")) {
            if (sscanf(cli_arg.c_str(), "--rand=%u", &seed) != 1) {
                printf("Wrong --rand option format.\n");
                return 1;
            }
        } else {
            printf("Wrong command-line option \"%s\".\n", argv[i]);
            return 1;
        }
    }

    try {
        game.run(seed);
    }
    catch (const std::runtime_error &e) {
        std::cerr << "Caught exception: " << e.what() << std::endl;
        return 1;
    }
    catch (...) {
        std::cerr << "Unknown exception" << std::endl;
        return 1;
    }

    return 0;
}
