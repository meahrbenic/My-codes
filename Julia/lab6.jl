
function nadji_pocetno_SZU(C, I, O)
    
    if sum(I) != sum(O)  
        if sum(I) > sum(O)
            push!(O, sum(I) - sum(O))
            C = hcat(C, zeros(Int8, size(C,2), 1))
        else
            push!(I, sum(O) - sum(I))
            C = vcat(C, zeros(Int8, size(C,1), 1))
        end
    end

    m = size(I)[1]
    n = size(O)[1]
    A = zeros(Int8, (m, n))

i=1
j=1
while true
    
     if I[i] < O[j] 
        A[i,j] = I[i]
        O[j] = O[j]-I[i]
        I[i] = 0
        i=i+1
     else
        if I[i]>O[j]
            A[i,j] = O[j]
            I[i] = I[i] - O[j]
            O[j] = 0
            j=j+1
         
        else 
            A[i,j] = I[i]
            I[i] = 0
            O[j] = 0
            j=j+1
            if j<=m
                A[i,j] = -1
            end
            i = i+1
        end
    end

      if i==m+1 && j==n+1 break end
end

T = 0
for i in 1:m
    for j in 1:n
        if A[i,j]!=0 && A[i,j]!=-1
            T=T+A[i,j]*C[i,j]
        end
    end
end

return A,T
end