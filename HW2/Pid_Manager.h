//header file with pre-defined value and functions
#define MIN_PID 300

#define MAX_PID 5000

int allocate_map(void);
int allocate_pid(void);
int release_pid(int pid);

char *pid_map = NULL;