** Compiler for the CPYRR language **

- Definition of syntax and semantics for the CPYRR language
- Syntax and semantic analysis and filling of lexical tables, declarations, etc...
- Transformation of CPYRR code into abstract instruction tree
- Reading the abstract tree via the stack at runtime (Virtual Machine)
- Executing the CPYRR code with the Virtual Machine (examples in the dir. programmes/prog_fonctionnels/)

Makefile : 
- make : create executable 
- make clean : clean up

Executable : 
./compilateur <programmes/subfolder/prog_name.cp> <-t (display. tables)> <-a (display. trees)> <-p (display.stack)> <-e (program execution)>

Authors :
- Mathevon Baptiste
- Yasser Assal
- Yildiz Tolga
- Gunes Ozan
