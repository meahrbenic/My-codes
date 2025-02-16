function nadji_pivot(A)

    vodeca_kolona = 0

    for i in 2 : size(A, 2)
        if A[size(A, 1), i] > 0
            vodeca_kolona = i
            break
        end
    end

    for i in vodeca_kolona + 1 : size(A, 2)
        if A[size(A, 1), i] > A[size(A, 1), vodeca_kolona]
            vodeca_kolona = i
        end
    end

    t = []
    for i in 1 : size(A, 1) - 1
        if A[i, vodeca_kolona] < 0 && A[i, 1] == 0
            append!(t, -1)
        else
            append!(t, A[i, 1]/A[i, vodeca_kolona])
        end
    end

    vodeci_red = 0

    for i in 1 : size(t, 1)
        if t[i] >= 0
            vodeci_red = i
            break
        end
    end

    if vodeci_red == 0
        return -1, -1, -1 
    end 

    for i in vodeci_red + 1 : size(t, 1)
        if t[vodeci_red] > t[i] && t[i] >=0
            vodeci_red = i
        end
    end
    return A[vodeci_red, vodeca_kolona], vodeci_red, vodeca_kolona
end


function provjeri_tabelu(A)

    z_red = 0

    for i in 2 : size(A, 2)
        if A[size(A, 1), i] > 0
            z_red = i
            break
        end
    end

    if z_red == 0
        return 2
    else
        return 1
    end
end

using Pkg;
Pkg.add("LinearAlgebra")

using LinearAlgebra
using DelimitedFiles

function rijesi_simplex(A, b, c)

    tabela = [
    [b A I(size(b, 1))];
    [zeros(1, 1) transpose(c) zeros(1, size(b, 1))]
    ]

    if(!all( x->x>=0, b)) 
        printlf("Neispravni podaci!") 
    end

    variable = String[]

    for i in size(c, 1) + 1 : size(b, 1) + size(c, 1)
        s=string("x", string(i))
        push!(variable, s)
    end
    provjera=provjeri_tabelu(tabela)

    while(provjera!=2)
        pivot, red, kolona = nadji_pivot(tabela)

        if pivot == -1 && red == -1 && kolona == -1
            println("Nema rješenja")
            return
        end

        variable[red] = string("x", kolona - 1)
        #a r k
        #tabela red kolona
        d = tabela[red, kolona]
    
        tabela[red, :] ./= d

        for i in 1:size(tabela, 1)
            if i == red
                continue
            end

            e = tabela[i, kolona]
            tabela[i, :] .-= e * tabela[red, :]
        end

        provjera=provjeri_tabelu(tabela)
    end

    println("Imamo rješenje")
    push!(variable, "Z")

    tabela = [variable tabela]
    
    writedlm(stdout, tabela)

    return
end

#Zadatak1 
# Primjer: Koristeći grafičku analizu, riješiti problem linearnog programiranja
# arg max Z = 3 x1 + x2
# p.o.
# 0.5 x1 + 0.3 x2 <=150
# 0.1 x1 + 0.2 x2 <= 60
# x1 >= 0, x2 >= 0

A1 = [0.5 0.3; 0.1 0.2]
b1 = [150 60;]'
c1 = [3 1;]'

rijesi_simplex(A1, b1, c1)

#Zadatak2 Primjer: Grafičkim metodom riješiti problem linearnog programiranja
# arg max Z = 3 x1 + 5 x2
# p. o.

# x1 <= 4
# 2 x2 <= 12
# 3 x1 + 2 x2 <= 18
# x1 + 3 x2 <= 21
# 2 x1 + 3 x2 <= 6

# x1 >= 0, x2 >= 0

A2 = [1 0; 0 2; 3 2;1 2;2 3]
b2 = [4 12 18 21 6;]'
c2 = [3 5;]'
rijesi_simplex(A2, b2, c2)
        
#Zadatak3

# arg max Z = 800 x1 + 1000 x2
# p. o.
# 30 x1 + 16 x2 <=  22800
# 14 x1 + 19 x2 <=  14100
# 11 x1 + 26 x2 <=  15950
#  x2 <= 550
# x1 >= 0, x2 >= 0

A3 = [30 16; 14 19; 11 26; 0 1]
b3 = [22800 14100 15950 550;]'
c3 = [800 1000;]'

rijesi_simplex(A3, b3, c3)