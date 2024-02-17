function [ B ] = transp( A )
    %Transponiranje kako je definirano u clanku
    [l,m,n] = size(A);
    B = zeros(m,l,n);
    for i = 1:n 
        if i == 1
            B(:,:,i) = A(:,:,i)';
        else
            B(:,:,i) = A(:,:,n-i+2)';
        end
    end
end

