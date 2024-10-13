#ifndef TESTS_STRUCT_H  
#define TESTS_STRUCT_H  

struct s_joueur {  
    int joueur_y;  
    int joueur_x;  
}; 

typedef struct s_joueur position;  

struct s_Boite {  
    int Boite_y;  
    int Boite_x;  
}; 

typedef struct s_Boite position2; 

struct s_obj {  
    int obj_y;  
    int obj_x;  
}; 

typedef struct s_obj position3; 


#endif//TESTS_STRUCT_H