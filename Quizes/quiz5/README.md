                                      Computer Simulation Project
This project implements a Computer class that simulates a computer with one Memory unit and two CPU units as components. The Computer class provides various methods to manage and retrieve information about these components, including the total memory used by all computers and the total number of cores.

                                      Class Details

Computer Class
The Computer class includes:

-A Memory component.

-Two CPU components (CPU1 and CPU2).

-Public Methods

Constructors:

-Computer(float speed, int cores, int tot_mem, int used_mem) – Initializes the memory and CPUs with specified parameters.

-Computer() – Delegates to the parameterized constructor with default values.


Setters and Getters:

-setMem(const Memory&) – Sets the memory component.

-setCpu1(const CPU&) – Sets the first CPU component.

-setCpu2(const CPU&) – Sets the second CPU component.

-getMem() const – Returns the memory component.

-getCpu1() const – Returns the first CPU component.

-getCpu2() const – Returns the second CPU component.

Utility Functions:

-int total_cores() const – Returns the total number of cores in both CPUs.

-static int total_mem_usage() – Returns the total memory used by all computers created.

Memory Class (Already Provided)

-Stores and manages memory capacity and used memory.

-Methods include getTotalCapacity(), setTotalCapacity(int), getUsedMemory(), and setUsedMemory(int).

CPU Class (Already Provided)

-Stores and manages the clock speed and the number of cores in the CPU.

-Methods include getClockSpeed(), setClockSpeed(float), getCores(), and setCores(int).

UML Diagram
-The UML diagram provided in the assignment defines the structure of the Memory and CPU classes used as components in the Computer class.
