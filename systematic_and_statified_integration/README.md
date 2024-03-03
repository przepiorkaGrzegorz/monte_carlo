## Systematic and stratified integration
Program computes value of definite integral with standard deviation in a given range using basic, systematic and stratified methods. Form of an integral can be changed in `integration.cpp` file, range is passed through constructors in `main.cpp`.


## Description
### Basic method

Definite integral $C = \int_a^b g(x) dx$ may be written as $\int_a^b \frac{g(x)}{f(x)} f(x) dx$, where $f(x)$ = $const$ is probability density function. In range $[a, b]$ we have $f(x) = \frac{1}{b - a}$. Value of that integral is approximated by mean value

$$
\begin{align}
C \approx \overline{g} = \frac{1}{N} \sum_{i = 1}^N (b - a) \cdot g(x_i), \quad x_i \sim U(a, b)
\end{align}
$$

$U(0, 1)$ is uniform random number generator in range $[a, b]$.

Second moment and variance read 

$$
\begin{align}
\overline{g^2} &= \frac{1}{N} \sum_{i = 1}^N [(b - a) \cdot g(x_i)]^2 \\
\sigma^2 &= \frac{\overline{g^2} - \overline{g}^2}{N}
\end{align}
$$

### Systematic method

In this method range $[a, b]$ is divided into $M$ equally wide subranges. In every interval we may specify probability of assigning a random number to it $p_m$. For equal intervals and uniform probability distribution 

$$
\begin{align}
p_m = \int_a^b f(x) dx = \frac{1}{M}
\end{align}
$$

Mean value and variance are calculated for every integral

$$
\begin{align}
\overline{g_m} &= \frac{1}{N_m} \sum_{i = 1}^{N_m} (b - a) \cdot g(x_{i_m}), \quad x_{i_m} \sim U(x_m, x_{m + 1}) \\
\overline{g_m^2} &= \frac{1}{N_m} \sum_{i = 1}^{N_m} [(b - a) \cdot g(x_{i_m})]^2, \quad x_{i_m} \sim U(x_m, x_{m + 1}) \\ 
\sigma^2_m &= \overline{g^2}_m - \overline{g_m}^2 
\end{align}
$$

Total value of integral and variance are given as

$$
\begin{align}
C &\approx \overline{g} = \sum_{m = 1}^M p_m \cdot \overline{g_m} \\
\sigma^2 &= \sum_{m = 1}^M \frac{p^2_m}{N_m} \cdot \sigma_m^2
\end{align}
$$

where $N_m$ = $p_m \cdot N$ is the number of draws in intervals.

### Stratified method

Contrary to systematic method we change the number of draws in intervals $N_m$ and calculate it as

$$
\begin{align}
N_m = \frac{p_m \hat{\sigma_m}}{\sum \limits _{j=1}^M p_j \hat{\sigma_j}} N
\end{align}
$$

where $\hat{\sigma_j}$ is expected value of standard deviation in $j$ interval estimated by systematic method for small number of samples (e.g $N$ = 100). While performing calculations, more accurate values of $\sigma_m$ are continuously being determined.

## Example results
* $C$ = $\int_{-3}^3 (1 + tanh(x))dx$ = 6

<img src=https://github.com/przepiorkaGrzegorz/praca_dyplomowa/assets/113951109/0f94c8d3-609c-4b24-a648-7dc14a0aff4d width=40% height=40%>

* $C$ = $\frac{1}{2} \int_0^4 x^3 dx$ = 32

<img src=https://github.com/przepiorkaGrzegorz/praca_dyplomowa/assets/113951109/021d23f8-ca93-4ebf-a250-b87f702ba4fa width=40% height=40%>
