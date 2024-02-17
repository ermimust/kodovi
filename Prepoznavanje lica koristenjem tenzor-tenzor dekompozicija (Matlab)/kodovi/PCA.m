function jj = PCA(fea,J,k)
    % Standardni PCA algoritam
    
    M = mean(fea);
    p = size(fea,1);
    A = (fea - repmat(M,p,1))';
    [U,~,~] = svd(A);
    
    KK = length(k);
    if KK == 1
        G = U(:,1:k)'*A;
        T = (J - M)';
        c = U(:,1:k)'*T;
        norme = arrayfun(@(x) norm(G(:,x)-c,'fro'),1:p);
        [~,jj] = min(norme);
    else
        jj = zeros(KK,1);
        for i = 1:KK
            G = U(:,1:k(i))'*A;
            T = (J - M)';
            c = U(:,1:k(i))'*T;
            norme = arrayfun(@(x) norm(G(:,x)-c,'fro'),1:p);
            [~,jj(i)] = min(norme);
        end
    end
end

