Project 10 - Blip Interpreter


Background: 

Project 10 is the final programming project for EE 312 where we implement a interpreter for a made up scripting language (called Blip). 

Minimal starter code is provided and students are granted a high degree of freedom in developing their solution.


Notes: 

The requirements and instructions for the project can be found in "InterpreterA.pdf" and "InterpreterB.pdf".


Summary of the required Blip commands/statements to be implented include: 

text := output string to console 

var := create variables 

set := set variables to the value of the following expression 

output := evaluate an expression and output to console 

do := while loops 

if, else := if/else conditional blocks 

defun := define a function 

params := define the parameter list inside a function definition 

return := used inside function definitions to return a value and end the function early 

call := invoke a predefined function 

args := used with call statements to pass arguments to the function


Our interpreter is also requried to keep track of Local/Global variable names, and Local/Global function names. 

Within a defined function's scope, there is preference to use local variable/function names first over global names.
