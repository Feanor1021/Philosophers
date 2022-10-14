#include  "philo.h"

void start_screen(void)
{
    ft_printf("%s██████╗ ██╗  ██╗██╗██╗      ██████╗ ███████╗ ██████╗ ██████╗ ██╗  ██╗███████╗██████╗ ███████╗%s\n",BLUE,END);
    ft_printf("%s██╔══██╗██║  ██║██║██║     ██╔═══██╗██╔════╝██╔═══██╗██╔══██╗██║  ██║██╔════╝██╔══██╗██╔════╝%s\n",BLUE,END);
    ft_printf("%s██████╔╝███████║██║██║     ██║   ██║███████╗██║   ██║██████╔╝███████║█████╗  ██████╔╝███████╗%s\n",BLUE,END);
    ft_printf("%s██╔═══╝ ██╔══██║██║██║     ██║   ██║╚════██║██║   ██║██╔═══╝ ██╔══██║██╔══╝  ██╔══██╗╚════██║%s\n",BLUE,END);
    ft_printf("%s██║     ██║  ██║██║███████╗╚██████╔╝███████║╚██████╔╝██║     ██║  ██║███████╗██║  ██║███████║%s\n",BLUE,END);
    ft_printf("%s╚═╝     ╚═╝  ╚═╝╚═╝╚══════╝ ╚═════╝ ╚══════╝ ╚═════╝ ╚═╝     ╚═╝  ╚═╝╚══════╝╚═╝  ╚═╝╚══════╝%s\n",BLUE,END);
}


int main(int argc, char **argv)
{
    t_arg rules;

    if(argc != 5 && argc != 6)
        return (error_message("Wrong amount of arguments!!!"));
    if(set_rules(&rules,argv,argc))
        return (error_message("\nSomething happend at initilazion phase..."));
        
}