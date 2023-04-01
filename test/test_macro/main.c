#include <stdio.h>

#undef PDEBUG             /* undef it, just in case */
#ifdef MC_DEBUG
     /* This one for user space */
#    define PDEBUG(fmt, args...) fprintf(stdout, fmt, ## args)
#else
#  define PDEBUG(fmt, args...) /* not debugging: nothing */
#endif

int main() {
    
    PDEBUG("Define MC_DEBUG\n");
    return 0;
}
