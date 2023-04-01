# Philosophers

The Philosophers project is a multi-threading simulation that aims to demonstrate the problem of resource allocation and deadlocks in concurrent systems. The simulation is based on the classic dining philosophers problem, which is a problem in computer science and philosophy that illustrates how a group of philosophers might starve if they compete for limited resources without proper synchronization.

In the Philosophers project, a number of philosophers sit around a table and alternate between thinking and eating. Each philosopher is represented by a separate thread in the simulation, and the forks on the table are shared resources that the philosophers must acquire in order to eat. The simulation is designed to demonstrate how deadlocks can occur when two or more philosophers try to acquire the same set of resources at the same time.

The Philosophers project is implemented in C using the pthreads library, which provides a set of primitives for creating and managing threads. The project is intended for anyone interested in learning about multi-threading and concurrent programming, and provides a hands-on way to explore the challenges and complexities of concurrent systems.

## Usage

To run the Philosophers simulation, simply clone the repository and run the `make` command to compile the code. Then, run the `./philo` executable to start the simulation. The program takes several arguments that control the parameters of the simulation, such as the number of philosophers and the time limit.

    bash
    $ git clone https://github.com/Feanor1021/Philosophers.git
    $ cd Philosophers/philosophers/philo
    $ make
    $ ./philo 5 800 200 200

### Screenshot

Mandatory:
![man](man.jpg)

