extern void do_hello();

#ifndef MAIN
#error You did not follow the instructions carefully.  You must define MAIN.
#endif

int main(int argc, char *argv[]) {
    do_hello();

    return 0;
}
