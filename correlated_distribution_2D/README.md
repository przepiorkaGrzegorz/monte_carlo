## Correlated distribution 2D
Program generates 2D random distributions (gauss, circle, elipse), calculates covariance matrix and correlation coefficients between variables $x$ and $y$.

## Description
### 2D distributions

Samples from Gauss distribution are generated using following method

$$
\begin{align}
x &= \sqrt{-2\ln(U_1)} \sin({2 \pi U_2}) \\
y &= \sqrt{-2\ln(U_1)} \cos({2 \pi U_2})
\end{align}
$$

where $U_1$ and $U_2$ come from uniform distribution $U(0, 1)$.

If we want to create circular uniform distribution, we normalize distance of a point from coordinate system center to 1 and rescale by a factor $q \cdot R_{\alpha}$ to place points inside a circle. $R_{\alpha}$ is a radius of a circle, $q$ is a random number from $U(0, 1)$.

$$
\begin{align}
x &:= \frac{x}{\sqrt{x^2 + y^2}} \\
y &:= \frac{y}{\sqrt{x^2 + y^2}}
\end{align}
$$

In order to transform uniform distribution in circle into uniform distribution in elipse, rotation matrix $R_{\alpha}$ and scalling coefficients $b_1$, $b_2$ are used.

$$
\begin{align}
R_{\alpha} = {\left\lbrack \matrix{ \cos(\alpha) & -\sin(\alpha) \cr \sin(\alpha) & \cos(\alpha)} \right\rbrack}, \quad \alpha \in [0, 2\pi]
\end{align}
$$

$$
\begin{align}
\vec{r_1} &:= b_1 R_{\alpha} \hat{e_x} \\
\vec{r_2} &:= b_2 R_{\alpha} \hat{e_y}
\end{align}
$$

where $\hat{e_x}$ and $\hat{e_y}$ are versors of cartesian coordinate system ($[1, 0]^T$, $[0, 1]^T$) respectively and $\vec{r_1}$, $\vec{r_2}$ are semi-axis vectors. 

### Covariance matrix
Covariance matrix and correlation coefficients are given as

$$
\begin{align}
R_{\alpha} = {\left\lbrack \matrix{ \sigma^2_x & \sigma_{xy} \cr \sigma_{yx} & \sigma^2_y} \right\rbrack}, \quad \sigma_{xy} = \sigma_{yx}
\end{align}
$$

$$
\begin{align}
r_{xy} = \frac{\sigma_{xy}}{\sqrt{\sigma^2_x \sigma^2_y}}, \quad r \in [-1, 1]
\end{align}
$$

Elements of covariance matrix:

$$
\begin{align}
\sigma^2_x &= \langle x^2 \rangle - \langle x \rangle^2 \\
\sigma^2_y &= \langle y^2 \rangle - \langle y \rangle^2 \\
\sigma_{xy}& = \sigma_{yx} = \langle xy \rangle - \langle x \rangle \langle y \rangle \\
\langle x \rangle &= \frac{1}{N} \sum_{i = 1}^N{x_i} \\
\langle y \rangle &= \frac{1}{N} \sum_{i = 1}^N{y_i} \\
\langle x^2 \rangle &= \frac{1}{N} \sum_{i = 1}^N{x^2_i} \\
\langle y^2 \rangle &= \frac{1}{N} \sum_{i = 1}^N{y^2_i} \\
\langle xy \rangle &= \frac{1}{N} \sum_{i = 1}^N{x_i y_i}
\end{align}
$$

where $N$ is the number of samples.

## Example results
<img src=https://github.com/przepiorkaGrzegorz/praca_dyplomowa/assets/113951109/21c77995-3ec0-40fb-ab31-94ebd5f799ea width=45% height=45%>
<img src=https://github.com/przepiorkaGrzegorz/praca_dyplomowa/assets/113951109/e7b77d78-519e-4333-98f0-5be670f4d37b width=31% height=31%>

