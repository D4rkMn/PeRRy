# Gramática Rust 

Esta es la gramática que representa el lenguaje de cadenas aceptadas por mi parser. Puede que hayan algunas diferencias entre esta y la implementación real, pero conceptualmente se da a entender la idea.

$test \to when$

$$
\begin{align*}


Program \to (Function \mid VarDec\ \textbf{;})^* \\

VarDec \to \textbf{let}\ [\textbf{mut}]\ Id\ (\ \textbf{:}\ Type\ [\
\textbf{=}\ BExp\ ] \mid \textbf{=}\ BExp\ ) \\

Function \to \textbf{fn}\ Id\ \textbf{(}\ [ParamDecList]\ \textbf{)}\
[\textbf{->}\ Type]\ \textbf{\{}\ Body\ \textbf{\}} \\

\end{align*}
$$

$$
\begin{align*}

Type \to \textbf{i32} \mid \textbf{i64} \mid \textbf{u32} \mid \textbf{u64} \mid \textbf{bool} \\

Body \to ( VarDec\ \textbf{;} \mid Stm )^* \\

ParamDecList \to Id\ \textbf{:}\ Type\
(\textbf{,}\ Id\ \textbf{:}\ Type)^* \\

\end{align*}
$$

$$
\begin{align*}

Stm \to \textbf{if}\ BExp\ \textbf{\{}\ Body\ \textbf{\}}\
[\ \textbf{else}\ \textbf{\{}\ Body\ \textbf{\}}\ ] \mid \\

\textbf{for}\ Id\ \textbf{in}\ BExp\ \textbf{..}\ Bexp\ \textbf{\{}
\ Body\ \textbf{\}} \mid \\

\textbf{println!}\ \textbf{(} \textbf{Text}\
(\ \textbf{,}\ BExp\ )^* \ \textbf{)}\ \textbf{;}  \mid \\

\textbf{return}\ [\ BExp\ ]\ \textbf{;} \mid \\

Id\ \textbf{+=}\ BExp\ \textbf{;} \mid \\

Id\ \textbf{=}\ BExp\ \textbf{;} \mid \\

BExp\ \textbf{;}\ \

\end{align*}
$$

$$
\begin{align*}

BExp \to [\ \textbf{!}\ ]\ CExp \\

CExp \to Exp\ [\ (\ \textbf{<} \mid \textbf{<=} \mid\textbf{==})\ Exp\ ] \\

Exp \to Term\ (\ (+\mid-)\ Term\ )^* \\

Term \to Factor\ (\ (*\mid/)\ Factor\ )^* \\

Factor \to Id \mid Integer \mid \textbf{(} BExp \textbf{)} \mid 
Id(\ [\  ArgList\ ] \ ) \\

ArgList \to BExp (\ \textbf{,}\ BExp\ )^* \\

\end{align*}
$$
