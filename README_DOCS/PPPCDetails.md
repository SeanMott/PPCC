# PPPC

PPCC is a four stage static transpiler

## Step 0 - Lexing
![alt text](../README_ASSETS/Step0.png)

After using DTK to generate symbols and assembly. The code can then be passed into the transpiler. It goes through the file using the DTK generated macro syntax sugar as a refrence when tokenizing everything. This first stage flags where functions start and end. Where objects/structs start and end, variables and their value, jump address, instructions, alignment (unused), section (unused), and other . directives.

## Step 1 - ASM First Pass AST
![alt text](../README_ASSETS/Step1.png)

Once we have a stream of tokens, we start the first pass of making a AST. This AST condenses the tokens and provides more specific bits of data.

## Step 2 - ASM Fine Grain AST

With the first pass done, we move onto taking that structure and refining it even furthur. This means functions and objects get compressed into a single Node. Variables get their internal datatype finalized and data, this means function pointers actually become function pointers and doubles/floats get their .0f needed for C++. This is also where instruction parameters are defined from loose tokens to real data.

## Step 3 - C++ First Pass AST

This step is where the Fine Grain AST starts to be turned into C++. This means objects become real structs with names for their variables and memory offets. Functions get their return type defined. And Assembly Instructions get turned into Sudo-C.

## Step 4 - C++ Fine Grain AST

This step is where the Sudo-C is finalized into Nodes and blocks of code. Jump Addesses become if else statments and code is validated

## Step 5 - C++ output

The Fine Grain C++ AST is converted to C++ code and written into a file, finishes the process.