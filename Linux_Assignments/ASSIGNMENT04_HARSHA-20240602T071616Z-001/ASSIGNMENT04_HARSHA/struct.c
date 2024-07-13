#include <stdio.h>

 struct s_vehicle
{
 char v_colour[10];
char v_module[10];
};

int main(){
 typedef struct s_vehicle v_struct;
 v_struct var1={"hello","world"};
 printf("record variable are %s%s",var1.v_colour,var1.v_module);
return 0;
}

