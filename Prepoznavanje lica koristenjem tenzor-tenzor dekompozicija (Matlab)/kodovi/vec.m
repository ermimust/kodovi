function v = vec(A)
    % Vektorizacija matrice A
    % Stupac po stupac slazemo jedan ispod drugog u jedan veliki vektor
    [l,m] = size(A);
    v = zeros(l*m,1);
    for i = 1:m
        v((i-1)*l + 1:i*l) = A(:,i);
    end
end

