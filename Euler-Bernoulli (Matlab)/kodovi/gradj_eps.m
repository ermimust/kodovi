function p = gradj_eps(eps, n, c, v)    p = zeros(2*n+2, 1);    for i = 1:n+1        p(2*i-1) = -max(0, (c(2*i-1) - v(2*i-1)));    end    p = 1/eps * p;
end