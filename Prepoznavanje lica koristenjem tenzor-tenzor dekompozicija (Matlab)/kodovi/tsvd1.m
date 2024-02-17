function jj = tsvd1( fea, J, k, pix) 
    %fea matrica dimenzije p*pix^2 (training slike), 
    %J test slika, 
    %k parametar iz TSVDA, broj ili vektor 
    %pix - slike su pix*pix velicine
    M = mean(fea); %Aritmeticka sredina po redcima
    p = size(fea,1); %koliko slika ima u training setu
    A = nashape(fea-repmat(M,p,1),pix,pix); %tenzor reda pix*p*pix
    
    AA = fft(A,[],3); %FFT transformacija po frontalnim slicevima
    U = zeros(pix,pix,pix); %U matrica iz tenzorskog SVDA tenzora AA
    
    cc = ceil((pix+1)/2);
    for i = 1:cc
        %Provodimo svd po frontalnim slicevima od AA
        [UU,~,~] = svd(squeeze(AA(:,:,i)));
        
        %Dobivene matrice UU iz svd-ova stavljamo u frontalne sliceve
        %matrice U
        U(:,:,i) = UU;
    end
    
    for i = cc+1:pix
        U(:,:,i) = conj(U(:,:,pix-i+2));
    end
    
    
    %Inverzna Fourierova transformacija po frontalnim slicevma
    U = ifft(U,[],3);
    
    KK = length(k); 
    %Gledamo kada je k vektor a kada broj
    if KK == 1
        %Transponiramo tenzor U_k
        UT = transp(U(:,1:k,:)); %Ovo je prvi put da koristimo k
        C = puta(UT,A);
        T = twist(reshape(J-M,pix,pix));
        B = puta(UT,T);


        norme = arrayfun( @(x) TnormFro(B-C(:,x,:)), 1:p);
        [~,jj] = min(norme);
    else
        jj = zeros(KK,1);
        for i = 1:KK
            %Transponiramo tenzor U_k
        UT = transp(U(:,1:k(i),:)); 
        C = puta(UT,A);
        T = twist(reshape(J-M,pix,pix));
        B = puta(UT,T);

        norme = arrayfun( @(x) TnormFro(B-C(:,x,:)), 1:p);
%         for j = 1:p
%             norme(j) = TnormFro(B-C(:,j,:));
%         end
        [~,jj(i)] = min(norme);
        end
    end
end

