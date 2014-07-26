int utmp_open(char *);
struct utmp* utmp_next();
int utmp_reload();
void utmp_close();
