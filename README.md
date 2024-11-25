# PeRRy
## *P* ascal PCode Interpreter - *R* ust Compiler
### Por: Alejandro Joel Ore Garcia

Esta es una implementación de un compilador simple de un subset de Rust a una modificación propia de código de pila Pascal PCode; a la vez que un intérprete para este último. Todo esto fue escrito en C++.

Este proyecto se compone de dos partes:

1. Un compilador de un subset de Rust:
    ```c++
    const bool isDebug = true; // Modo con debug prints
    R::Compiler compiler(isDebug);
    compiler.setInputFile(inputFile); // Rust input
    compiler.setOutputFile(outputFile); // PCode output
    compiler.compile();
    ```
2. Un intérprete de una modificación de PCode:
    ```c++
    const bool isDebug = true; // Modo con debug prints
    P::Interpreter interpreter(isDebug);
    interpreter.setInputFile(inputFile); // PCode input
    interpreter.interpret();
    ```

## Ejecución

Para compilar el código, se utiliza:
```
make
```
Para ejecutar el código (para Linux), se utiliza:
```
./PeRRy <archivo-input> <archivo-output> [T|F]
```
Donde `[T|F]` representa si se entrará en modo debug o no. Este parámetro es opcional, y en caso de ser omitido se asumirá que `isDebug = true`.

(No se ha probado el funcionamiento del código en windows sin WSL)

## Información adicional

- Información sobre la gramática utilizada se puede encontrar en:
`Grammar.md`
- Información sobre el ISA de la modificación del código PCode se puede encontrar en:
`P_ISA.md`