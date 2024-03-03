## Simple integration
Program computes common area of overlapping circles composed of $N$ points from 2D random uniform distribution. 

## Description
At the beginning coordinates of a point were drawn from normal distribution, then normalized to 1, rescaled by a factor $q \cdot R_{\alpha}$ and finally translated by a vector $[x_{\alpha}, \ y_{\alpha}]$. $R_{\alpha}$ is a radius of a circle, $q$ $\sim$ $U(0, 1)$ is a parameter that locates points inside a circle, $x_{\alpha}, \ y_{\alpha}$ are coordinates of a center of a circle.

1.
$$
\begin{align}
x &= \sqrt{-2\ln(U_1)} \sin({2 \pi U_2}) \\
y &= \sqrt{-2\ln(U_1)} \cos({2 \pi U_2})
\end{align}
$$

2.
$$
\begin{align}
x &:= \frac{x}{\sqrt{x^2 + y^2}} \\
y &:= \frac{y}{\sqrt{x^2 + y^2}}
\end{align}
$$

3.
$$
\begin{align}
x &:= R_{\alpha} \cdot q \cdot x + x_{\alpha} \\
y &:= R_{\alpha} \cdot q \cdot y + y_{\alpha}
\end{align}
$$

## Example results

<img src=https://github.com/przepiorkaGrzegorz/praca_dyplomowa/assets/113951109/9c2e10bc-b310-415d-9f26-84fb471d8172 width=45% height=45%>

<img src=https://github.com/przepiorkaGrzegorz/praca_dyplomowa/assets/113951109/629261cc-8da7-4a05-8a6f-1b7e3c4839a4 width=45% height=45%>

