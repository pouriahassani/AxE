
// good info about typedefs:
// https://stackoverflow.com/a/23660072

typedef struct {
    
    int id;
    int arch;
    int id_flag;
    int addr_assign;
    int prg;
    
} node_t;

typedef struct {
    
    char* name;
    int   addr [ NUM_ARCHS ];
    int   exec_interval;
    int   exec_again_at;
    int   skip_after;
    int   skip_cnt_down;
    
} prg_t;
