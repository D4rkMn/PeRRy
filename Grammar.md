$$
\begin{align*}


Program \to (Function \mid VarDec\ \textbf{;})^* \\

VarDec \to \textbf{let}\ [\textbf{mut}]\ Id\ (\ \textbf{:}\ Type\ [\
\textbf{=}\ CExp\ ] \mid \textbf{=}\ CExp\ ) \\

Function \to \textbf{fn}\ Id\ \textbf{(}\ [ParamDecList]\ \textbf{)}\
[\textbf{->}\ Type]\ \textbf{\{}\ Body\ \textbf{\}} \\

\end{align*}
$$

$$
\begin{align*}

Type \to \textbf{i32} \mid \textbf{i64} \\

Body \to ( VarDec\ \textbf{;} \mid Stm )^* \\

ParamDecList \to Id\ \textbf{:}\ Type\
(\textbf{,}\ Id\ \textbf{:}\ Type)^* \\

\end{align*}
$$

$$
\begin{align*}

Stm \to \textbf{if}\ CExp\ \textbf{\{}\ Body\ \textbf{\}}\
[\ \textbf{else}\ \textbf{\{}\ Body\ \textbf{\}}\ ] \mid \\

\textbf{for}\ Id\ \textbf{in}\ CExp\ \textbf{..}\ Cexp\ \textbf{\{}
\ Body\ \textbf{\}} \mid \\

\textbf{println!}\ \textbf{(} \textbf{Text}\
(\ \textbf{,}\ CExp\ )^* \ \textbf{)}\ \textbf{;}  \mid \\

\textbf{return}\ [\ CExp\ ]\ \textbf{;} \mid \\

Id\ \textbf{+=}\ CExp\ \textbf{;} \mid \\

Id\ \textbf{=}\ CExp\ \textbf{;} \mid \\

CExp\ \textbf{;}\ \

\end{align*}
$$

$$
\begin{align*}


CExp \to Exp\ [\ (\ \textbf{<} \mid \textbf{<=} \mid\textbf{==})\ Exp\ ] \\

Exp \to Term\ (\ (+\mid-)\ Term\ )^* \\

Term \to Factor\ (\ (*\mid/)\ Factor\ )^* \\

Factor \to Id \mid Integer \mid \textbf{(} CExp \textbf{)} \mid 
Id(\ [\  ArgList\ ] \ ) \\

ArgList \to CExp (\ \textbf{,}\ CExp\ )^* \\

\end{align*}
$$
