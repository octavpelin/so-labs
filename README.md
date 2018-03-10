# so-labs
# PRIVATE REPO
# Debug construct:

#ifdef DEBUG
#define Dprintf(msg, ...) printf("[%s]:%d" msg, __FILE__, __LINE__, ##__VA_ARGS__)
#else
#define Dprintf(msg, ...)	/* do nothing */
#endif
