function X = twist( X )
    % X je matrica
    % squeeze(twist(X)) = X
    l = size(X,1);
    n = size(X,2);
    X = reshape(X,[l,1,n]);
end