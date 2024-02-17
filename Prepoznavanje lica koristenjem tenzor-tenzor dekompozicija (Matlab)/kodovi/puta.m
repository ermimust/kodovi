function C = puta( A,B )
    %matricno mnozenje definirano u clanku
    n = size(A,3);
    A1 = fft(A,[],3); %FFT po nitima u trecoj niti
    B1 = fft(B,[],3);
    cc = ceil((n+1)/2);
    for i = 1:cc
        C(:,:,i) = A1(:,:,i)*B1(:,:,i);
    end
    for i = (cc+1):n
        C(:,:,i) = conj(C(:,:,n-i+2));
    end
    
    C = ifft(C,[],3);
end

