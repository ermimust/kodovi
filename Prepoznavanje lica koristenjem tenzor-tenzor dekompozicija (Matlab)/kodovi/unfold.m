function B = unfold(A)
    [l,m,n] = size(A);
    B = zeros(l*n,m);
    for i = 1:n
        B((i-1)*l+1:i*l,:) = A(:,:,i);
    end
end

