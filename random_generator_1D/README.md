## Random generator 1D
Pseudorandom numbers generator in 1D based on 2 methods - Markov Chain and Acceptance-Rejection method. Program generates and saves samples from given probability density function (pdf) and calculates $\chi^2$ value.

## Description

### Markov Chain
Samples are created using Metropolis algorithm:

$$
\begin{align}
X_{i + 1} &= X_i + (2U_1 - 1) \Delta \quad \text{when} \quad U_2 \leq p_{acc} \quad \wedge \quad x \in [a, b], \Delta \in [0, 1] \\
X_{i + 1} &= X_i \quad \text{otherwise}
\end{align}
$$

where $U_1$, $U_2$ $\sim$ $U(0, 1)$ and $a$, $b$ are the left and right boundaries of the range, $p_{acc}$ is the acceptance probability given as $min(1, \ pdf(X_{i + 1})/pdf(X_i))$.

### Acceptance-Rejection method

We draw 2 values $U_1$ $\sim$ $U(a, \ b)$ and $Y$ $\sim$ $U(0, \ pdf_{max})$, then

$$
\begin{align}
Y &\leq pdf(U_1), \quad U_1 \ \text{accepted} \\
Y &> pdf(U_1), \quad U_1 \ \text{rejected}
\end{align}
$$

$pdf_{max}$ is the maximum value of probability distribution function in a chosen range.

Probability density functions should be normalized and may be changed in generator.cpp file. Other parameters are passed in by parametric constructor, $pdf_{max}$ should be specified by user.

## Example results
* $f(x)$ = $3x^2$
<img src=https://github.com/przepiorkaGrzegorz/praca_dyplomowa/assets/113951109/b54eea82-1c80-4aab-8bdf-23c87f56a476 width=55% height=55%>

* $f(x)$ = $\frac{4}{5}$ ($1$ + $x$ - $x^3$)
<img src=https://github.com/przepiorkaGrzegorz/praca_dyplomowa/assets/113951109/f7096849-6f4e-4865-95cb-d0e388ad864f width=55% height=55%>

* $f(x)$ = $\frac{1}{2 - 122 e^{-10}}$  $x^2$ $e^{-x}$
<img src=https://github.com/przepiorkaGrzegorz/praca_dyplomowa/assets/113951109/1f8596a7-cf0c-4ecb-afeb-babe9ab0576e width=55% height=55%>


