function A = fold(B,n)
    l = size(B,1)/n;
    m = size(B,2);
    A = zeros(l,m,n);
    for i = 1:n
        A(:,:,i) = B((i-1)*l+1:i*l,:);
    end
end
