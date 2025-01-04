# Option Pricing Using Monte Carlo Simulation

## Context Diagram

![ContextDiagram](https://github.com/user-attachments/assets/225d1d88-8c3a-4b57-a728-d41e4271c08e)

The application consists of 8 parts.
The Mediator part is responsible for bringing all the rest parts of the application together.
According different pricers, there are different mediators derived from the Mediator abstract class.
The MonteCarloSimulation part is responsible for the Monte Carlo Simulation. That means to
2
simulate the random walk of the underlying asset price. The price path is to be used differently
according to different option types. It composes of the IRNG part which is responsible for the
random number generators.
The Pricer part takes care of the pricing formula for different kinds of options. For example, the
Vanilla European option, the Asian option. It works based on the output from the Monte Carlo
simulation part.
The FDMStrategy part contains various kind of FDM strategies. It is for the approximation of the
SDE equations. Therefore, it composes of the ISDE part.
The OptionInfo part holds the option information. It can be derived to have equity option
information or the interest rate product options. For this task, we only provide the equity option.
The MIS part is in charge of the management of information system. It tells about the information
about the pricing system. Can be a great API for the UI development to show the option
information and the corresponding option prices. It can even be extended to show the mark and
quote information by adding user interactive codes. But we do not extend to that far.

## UML Diagram

![FinalProjUML](https://github.com/user-attachments/assets/aaf70214-4834-4161-8904-a5f6f1d529a6)

The following UML Diagram describes the whole application design, and the relationships
between each part of the program in a specific way. Basically, it tells more details about the
context diagram. The inheritance hierarchy, aggregation, composition are included.
From the UML diagram, we can see that, the application currently provides three classes derived
from the Mediator class, which put every part that is required for the option pricing together, to the
users to use. They are the European option pricing, Asian option pricing, and the Barrier option
pricing. Users can simply create objects from these three to implement the option pricing of the
European option, Asian option, Barrier (knock-in & knock-out) according to needs.

# Techniques Used

## Design Pattern

The application uses these pattern design techniques, Strategy pattern, Bridge pattern, Factory
pattern, Observer pattern, and Builder pattern.
The Strategy pattern is used for random number generator, pricer, finite difference method strategy
parts. Because we want these parts to provide different algorithms to fulfill the functions they
should provide.
The Factory pattern is used only in option information part. Because we think that the option
information part is providing the option information which can be reused everywhere in the
program, even the MIS part. Therefore, the Factory pattern would be suitable since it provides the
convenience of creating the objects for different options.
The Bridge pattern is used for the stochastic differentiate equation part owing to the specialty of
the stochastic differentiate equations. Different kinds of stochastic differentiate equations are
almost the same, which contains drift, diffusion, drift correction, and diffusion derivatives.
However, the elements to compute these four values are quite different, even have different
numbers of data members to get the values. Hence, Bridge pattern is the best for this part.
The Observer pattern is used in the MIS part. Obviously, this part is in charge of the information
passing. Therefore, we consider that the Observer pattern should be the best.
The Builder pattern is used in the Mediator part. The advantage of using the Builder pattern is that,
it implements the same member functions in different ways in each concrete class. We are sure
this is perfect for the mediators which puts everything together.

## Concurrency

For Monte Carlo Simulation, the heaviest part is simulating the underlying asset path for the
computation of the option price. Therefore, we put the concurrency on the Monte Carlo
Simulation and the pricing part which include some numeric computations.
We tried multi-threads, future, and OpenMP. We finally chose OpenMP for its convenience and
5
good performance.
Since the simulation of the underlying asset price is sequential, the paths follows the “time”. That
means the later price depends on the former price. We cannot make this part concurrent. Moreover,
it is important to make sure the path generation is not interrupted. As a result, we put a lock there.
The lock only locks the simulation of the path. In this way, we can make sure the paths generated
are reliable.
As for the pricing part, we simply let it run concurrently because we do not care which price is
added first. We aim at getting the summary of all the prices got from the paths.
We tried to group the Monte Carlo simulations into small groups to make it less threads. However,
owing to my antiquarian machine, the performance does not show.

## Function Wrappers, Smart Pointers and Others

To reduce the inheritance hierarchy, we use function wrappers. For example, the random number
generator is quite simple. If we write in inheritance hierarchy, each class will just contain a
generate method to generate a sequence of random numbers. Using function wrappers can
simplify the hierarchy by just providing different methods to generate random numbers in one
class.
We also heavily use smart pointers in implementing the design patterns we chose. Smart pointers
can take care of themselves by deleting oneself when it is out of scope.
Other than that, we also include other techniques like lambda functions, timer, template template
parameters to make the program more flexible.

## STL Data Structures and Algorithms

For convenience, we also made use of the STL data structures and algorithms as much as possible.
Since the program is design to have compute the option price right after the path is generated, we
only make use of STL algorithms like accumulate, max_element, min_element.
We also made full use of tuples to pass multiple results. For example, we used tuple to pass two
generated paths to the mediator. We also used tuple to store the users information for the MIS part.

## Input Validation and Exception Handling

The program also include input validation and exception handling.
6
For example, for the CIR model, it may not work properly if $2ab<c^2$ . Therefore, the program
will warn the users if this condition does not hold, indicating whether the input parameters are
incorrect or the users should not use CIR model for the SDE equation.
Other than that, we also include quite some warnings for those SDE equations or FDM methods
that require extra input parameters. Certainly, if a user input wrong number for the option type, the
program will throw an exception.
