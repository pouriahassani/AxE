
// good info about typedefs:
// https://stackoverflow.com/a/23660072

typedef struct {
    
    int id;
    int arch;
    int id_flag;
    int addr_assign;
    int prg;
    unsigned int charge;
    
} node_t;

typedef struct {
    
    char* name;
    int   addr [ NUM_ARCHS ];
    int   exec_t [ NUM_ARCHS ];
    int   exec_inv [ NUM_ARCHS ];
    int   exec_e [ NUM_ARCHS ];
    int   skip_after;
    int   skip_cnt_down;
    int   overflows;
    
} prg_t;

typedef struct {
    
    unsigned int node_mask;
    unsigned int power;
    
} arch_t;

typedef struct {
    
    unsigned int  cnt;
    unsigned char event;
    
} queue_t;
