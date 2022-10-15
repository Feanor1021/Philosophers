#include  "philo.h"

int main(int argc, char **argv)
{
    t_arg rules;

    if(argc != 5 && argc != 6)
        return (error_message("Wrong amount of arguments!!!"));
    if(set_rules(&rules,argv,argc))
        return (error_message("\nSomething happend at initilazion phase..."));
    start_screen();
    if(handle_resources(&rules))
        return (error_message("\nSomething happened at process phase...."));
    return 0;
}