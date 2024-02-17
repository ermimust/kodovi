clc;
clear;


%load('Yale_64x64.mat')
%load('Yale_32x32.mat')
load('ORL_64x64.mat')

% u matrici fea su zadane slike
pix = sqrt(size(fea,2)); %slike su pix X pix piksela

p = 40; % 40 osoba
e = 10; % 10 izraza lica
brsl = size(fea,1); % broj slika

% Algoritam opisan u clanku/seminaru
k = 1:pix;
KK = length(k);
pogadanja = zeros(p,p,KK);
tocni = zeros(KK,1);
for ind = 1:brsl
    ind
    indeksi = setdiff(1:brsl,ind);
    J = fea(ind,:);
    fn = fea(indeksi,:);
    jj =  PCA(fn,J,k);
    osoba = fix((ind-1)/e)+1;
    for l = 1:KK
        if jj(l) >= ind
            jj(l) = jj(l) + 1;
        end
        odaberi = fix((jj(l)-1)/e)+1;
        pogadanja(odaberi,osoba,l) = pogadanja(odaberi,osoba,l) + 1;
    end
end
for l = 1:KK
    tocni(l) = trace(pogadanja(:,:,l));
end

tocni
[m,i] = max(tocni)

% Tocnost = m / brsl