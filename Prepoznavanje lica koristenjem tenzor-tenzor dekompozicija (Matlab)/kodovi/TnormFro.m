function [ n ] = TnormFro( A )
    %Frobeniusova norma tenzora A
    n = sqrt(sum(sum(sum(A.^2))));
end

