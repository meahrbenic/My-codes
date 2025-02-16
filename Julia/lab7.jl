function obrisi_zavisne_nule!(M, red, kolona)
    M[red, :] .*= 0  
    M[:, kolona] .*= 0  
end

function rasporedi(A)
    #redukcija kolona
    for i in 1:size(A,1)
        min=minimum(A[i, :])
        for j in 1:size(A,2)
            A[i,j]= A[i,j]-min
        end
    end
    #redukcija redova
    for j in 1:size(A,2)
        min=minimum(A[:,j])
        for i in 1:size(A,1)
            A[i,j]= A[i,j]-min
        end
    end
    red=Inf
    kolona=Inf
    while true 
        #trazimo nulu
        for i in 1:size(A,1)
            for j in 1:size(A,2)
                if A[i,j]==0
                    red=i
                    kolona=j
                    break
                end
            end
        end
        #oznacavamo nule

        A[red,:] .*=-1
        A[:,kolona] .*=-1
        A[red,kolona]=1

        for i in 1:size(A, 1)
            if any(A[i, :] .== 1)
                obrisi_zavisne_nule!(A, i, kolona)
            end
        end

        for j in 1:size(A, 2)
            if any(A[:, j] .== 1)
                obrisi_zavisne_nule!(A, red, j)
            end
        end

    end

    raspored = A .==1
    Z=sum( A.==1)
    
    return raspored,Z
end

M = [80 20 23; 31 40 12; 61 1 1];
rasporedi(M)
M = [25 55 40 80; 75 40 60 95; 35 50 120 80; 15 30 55 65];
rasporedi(M)
