## About
### Introduction
The methodology of School 21 makes sense only if peer-to-peer reviews are done seriously. Please read all guidelines carefully before starting the review.
- Please, stay courteous, polite, respectful and constructive in all communications during this review.
- Highlight possible malfunctions of the work done by the person and take the time to discuss and debate it.
- Keep in mind that sometimes there can be differences in interpretation of the tasks and the scope of features. Please, stay open-minded to the vision of the other.
- If you have not finished the project yet, it is compulsory to read the entire instruction before starting the review.

### Guidelines
- Evaluate only the files that are in src folder on the GIT repository of the student or group.
- Ensure to start reviewing a group project only when the team is present in full.
- Use special flags in the checklist to report, for example, an “empty work” if repository does not contain the work of the student (or group) in the src folder of the develop branch, or “cheat” in case of cheating or if the student (or group) are unable to explain their work at any time during review as well as if one of the points below is not met. However, except for cheating cases, you are encouraged to continue reviewing the project to identify the problems that caused the situation in order to avoid them at the next review.
- Doublecheck that the GIT repository is the one corresponding to the student or the group.
- Meticulously check that nothing malicious has been used to mislead you.
- In controversial cases, remember that the checklist determines only the general order of the check. The final decision on project evaluation remains with the reviewer.

## Main part
### smartcalc-v1.0.
- The program is developed in C language of C11 standard using gcc compiler. Additional QT libraries and modules are allowed
- The code of the program is in the src folder
- The program is built using Makefile with standard set of targets for GNU-programs: all, install, uninstall, clean,  dvi, dist, test, gcov_report.
- Executing the "all" target leads to the correct build of the program
- Executing the "install" target results in installing the program to some other directory
- Executing the "uninstall" target uninstalls the program from the installation directory
- Executing the "test" target builds and runs tests
- The program works
- The program is developed according to the principles of structured programming: the program is decomposed into files and functions; top-down design is used
- The expression calculation code is abstracted from the user interface code (there is no direct dependency, which means it can be run independently)
- There is no code duplication
- There is one input and one output in all program structures (functions and loops). This excludes the cases when multiple outputs are allowed at the beginning of functions to handle erroneous situations
- No goto statement is used
- Unit-tests cover all the modules, related to calculating expressions
- The program has a graphical user interface
- The program supports working with fractional numbers
- The program can calculate arbitrary bracketed arithmetic expressions in infix notation
- The program can calculate arbitrary bracketed arithmetic expressions in infix notation and substitute the values of the variable x
- The program can graph a function defined by an expression in infix notation with the variable x
- When drawing a graph of a function, the coordinate axes are plotted
- When drawing a graph of a function, the scale used is marked
- When plotting the graph, an adaptive grid is marked
- Expressions support brackets ()
- Expressions support the + operation
- Expressions support the - operation
- Expressions support the * operation
- Expressions support the / operation
- Expressions support the ^ operation
- Expressions support the mod operation
- Expressions support the unary + operation
- Expressions support the unary - operation
- Expressions support cos(x) function
- Expressions support sin(x) function
- Expressions support tan(x) function
- Expressions support acos(x) function
- Expressions support asin(x) function
- Expressions support atan(x) function
- Expressions support sqrt(x) function
- Expressions support ln(x) function
- Expressions support log(x) function
- The program correctly calculates expressions (check in the Google calculator on the example of at least 5 cases)
- The program correctly handles the case of division by zero
- The program correctly handles the case of calculating the root of a negative value
- The program correctly handles the case of multiplication of a set of factors (including bracket structures) by 0
- The program correctly handles the case of a nesting more than 3 parentheses

## Bonus part
### Part_2
- There is a special "credit calculator" mode in the program
- You can enter the total credit amount in this mode
- You can enter the term in this mode
- You can enter the interest rate in this mode
- You can enter the type of interest calculation in this mode
- The result of calculations in this mode is the monthly payment
- The result of calculations in this mode is the overpayment on credit
- The result of calculations in this mode is the total repayment
- The program correctly performs calculations (check with similar calculator in calcus.ru on the example of at least 3 cases, taking into account boundary cases - the term of 1 month and term of 50 years)

### Part_3
- There is a special "deposit calculator" mode in the program.
- You can enter the deposit amount in this mode
- You can enter the term of deposit in this mode
- You can enter the interest rate in this mode
- You can enter the tax rate in this mode
- You can enter the periodicity of payments in this mode
- You can enter the capitalization of interests in this mode
- You can enter the placements list in this mode
- You can enter the partial withdrawals list in this mode
- The result of calculations in this mode is the accrued interest
- The result of calculations in this mode is the tax sum
- The result of calculations in this mode is the deposited amount by the end of the deposit period
- The program correctly performs calculations (check with the similar calculator in calcus.ru on the example of at least 3 cases, taking into account boundary cases)
