[![Review Assignment Due Date](https://classroom.github.com/assets/deadline-readme-button-24ddc0f5d75046c5622901739e7c5dd533143b0c8e959d652212380cedb1ea36.svg)](https://classroom.github.com/a/76mHqLr5)
# Description
All relevant source codes are in src directory, with the relevant include libraries in the include directory, everything else is for test purposes.

To run first open the directory downloaded and compile the makefile using
```
make build
```
to run the shell
```
./final
```
# Assumptions
- echo with double quotation marks always end with double quatations
  eg: ``` echo "hi ``` is not valid, however ``` echo "hi    " ``` is, or even ``` echo hello       world```
- peek is always given with flags (atleast 1 flag) , by default the flag ```-a``` is run
- ``` pastevent execute``` is always entered without any spaces and with a ';' for example:
    ```pastevents``` No spaces (no ';' required only for pastevents)
    ```pastevents purge;``` (No spaces with a mandatory ';')
    ```pastevents execute 2;``` no spaces after ';' 
    ```echo hi;pastevents execute 1;echo test2``` (No spaces in pastevents execute 1)
   
