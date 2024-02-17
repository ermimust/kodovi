function L = nashape( A,m,n ) 
%slaže matricu A reda k*mn u tenzor L dimenzija m*k*n
%tako da i-ti redak od A pretvori u matricu reda m*n
%i to ubaci u i-ti lateralni slice tenzora L
    k = size(A,1);
    L = zeros(m,k,n);
    for i = 1:k
        L(:,i,:) = reshape(A(i,:),m,n);
    end
end

