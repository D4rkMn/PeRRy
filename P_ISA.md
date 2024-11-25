# P0-Code

El nombre de la modificación del PCode es P0. Esto es porque es una  versión más primitiva de la misma. Pese a ello, se cuentan con nuevas instrucciones para mejorar el control de flujo en la ejecución del código. A continuación, se mostrarán las instruccion con las que cuenta el lenguaje.

# ISA

## Generales
- `POP`: Borra el objeto al top de la pila
- `STP`: Detiene el programa

## Scope y environment
- `MST`: Marca el estado actual de la pila, y abre un nuevo environment
- `RET`: Restaura la última marca, y cierra el último environment 

## Funciones y llamadas
- `ENT <function-name>`: Define el inicio o entrada a una función. Marca la pila con una firma de función
- `RETn`: Restaura la marca de función
- `RETv`: Restaura la marca de función, pero deja el valor actualmente al top de la pila (valor de retorno)
- `MSTp`: Marca la pila para una llamada a función
- `CUP <function-name>`: Llamada a una función. La función a ser llamada toma como parámetros los valores en la pila

## Cargar valores para la pila
- `LDA x`: Añade a la pila la "dirección" de x 
- `LODc x`: Añade a la pila el valor de x
- `LDCc n`: Añade a la pila la constante n

## Almacenar variables
- `STOc`: Almacena el valor del primer top a la dirección del segundo top (doble pop)
- `INCc`: Incrementa por el valor del primer top a la dirección del segundo top (doble pop)
- `SROc x`: Almacena el valor del top de la pila en la "dirección" de x (un pop)

## Branching
Para esta sección, se asume que `k` es un número:
- `Lk `: Define el label Lk
- `UJP Lk`: Salto incondicional al label Lk
- `FJP Lk`: Salto al label Lk si el top de la pila evalúa a false (un pop)

## Operaciones binarias
Cada una de estas operaciones hacen doble pop, e inmediatamente hacen push al resultado de la operación respectiva:
- `ADI`: Adición de enteros
- `SBI`: Substracción de enteros
- `MPI`: Multiplicación de enteros
- `DVI`: División de enteros
- `LESc`: 'Menor que' lógico
- `LEQc`: 'Menor o igual' lógico
- `GRTc`: 'Mayor que' lógico
- `GEQc`: 'Mayor o igual' lógico
- `EQUc`: 'Igual a' lógico
- `NEQc`: 'No igual a' lógico

## Operaciones unarias
Cada una de estas operaciones hacen un solo pop, e inmediatamente hacen push al resultado de la operación respectiva:
- `NGI`: Multiplica el valor entero por -1
- `NOT`: 'not' lógico

## Print
- `PRINT`: Imprime el top de la pila (un pop)
- `PRINTLN`: Imprime un salto de línea