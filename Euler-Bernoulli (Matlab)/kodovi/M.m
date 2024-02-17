function P = M(n, c, v, pen)    d = zeros(2*n+2, 1);    for i = 1:n+1        d(2*i-1) = pen(i, c, v);    end    P = diag(d);
end