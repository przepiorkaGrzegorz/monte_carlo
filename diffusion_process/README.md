## Diffusion process
Program simulates diffusion process in open system and computes the diffusion coefficients in function of time.

## Description
Diffusion is described by Poisson equation

$$
\begin{align}
\frac{\partial u}{\partial t} = D \frac{\partial^2 u}{\partial x^2}, \quad u = u(x, t)
\end{align}
$$

If we assume $u(x = 0, t = 0)$ = $\delta(x - x_0)$ the solution is the Gauss function

$$
\begin{align}
u(x, t) = \frac{1}{\sigma_t \sqrt{2 \pi}} \exp{(-\frac{(x - x_0)^2}{2 \sigma_t^2})}
\end{align}
$$

where $\sigma_t$ = $\sqrt{2Dt}$, $D$ is the diffusion coefficient.

Time evolution is achieved by drawing $\Delta X$ and $\Delta Y$ from normal distribution in every time step. 

$$
\begin{align}
X_i(t + \Delta t) &= X_i(t) + \Delta X \\
Y_i(t + \Delta t) &= Y_i(t) + \Delta Y
\end{align}
$$

Diffusion coeficients:

$$
\begin{align}
D_{xx}(t) &= \frac{\langle x^2(t) \rangle - \langle x(t) \rangle^2}{2t} \\
D_{yy}(t) &= \frac{\langle y^2(t) \rangle - \langle y(t) \rangle^2}{2t} \\
D_{xy}(t) &= \frac{\langle x(t) y(t) \rangle - \langle x(t) \rangle \langle y(t) \rangle}{2t}
\end{align}
$$

where

$$
\begin{align}
\langle x(t) \rangle &= \frac{1}{n} \sum_{i = 1}^n X_i(t) \\
\langle y(t) \rangle &= \frac{1}{n} \sum_{i = 1}^n Y_i(t) \\
\langle x(t) y(t) \rangle &= \frac{1}{n} \sum_{i = 1}^n X_i(t) Y_i(t) \\
\langle x^2(t) \rangle &= \frac{1}{n} \sum_{i = 1}^n X_i^2(t) \\
\langle y^2(t) \rangle &= \frac{1}{n} \sum_{i = 1}^n Y_i^2(t)
\end{align}
$$

## Example results
<img src=https://github.com/przepiorkaGrzegorz/praca_dyplomowa/assets/113951109/28070226-19e0-4d3e-baca-31205fea9285 width=50% height=50%>
<img src=https://github.com/przepiorkaGrzegorz/praca_dyplomowa/assets/113951109/b63f2ea3-de20-4f64-a04a-d9d4eb4e64c6 width=50% height=50%>
