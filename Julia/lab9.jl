function CPM(A,P,T)
    
    temp = split.(P,",")
    holder = []

    for i in collect(1:length(temp))
         push!(holder, String.(strip.((temp[i])[:])))
    end

    P = holder
    nodes = zeros(length(A),4)
    
    for i in collect(1:length(A))
        if (P[i])[1] == "-"
            nodes[i,1] = 0
            nodes[i,2] = T[i]
        else
            brojPrethodnika = length(P[i])
            max = 0
            for j in collect(1:brojPrethodnika)
                node = (P[i])[j]
                redniNodea = 0
                
                for k in collect(1:length(A))
                    if A[k] == node
                        redniNodea = k
                        break
                    end
                end

                if nodes[redniNodea,2] > max
                    max = nodes[redniNodea,2]
                end
            end

            nodes[i,1] = max
            nodes[i,2] = T[i] + max
        end
    end

    maxKraj = nodes[1,2]
    indeksMaxKraj = 1

    for i in collect(1:size(nodes,1))
        if maxKraj < nodes[i,2]
            maxKraj = nodes[i,2]
            indeksMaxKraj = i
        end
    end

    nodes[indeksMaxKraj, 3] = nodes[indeksMaxKraj, 1]
    nodes[indeksMaxKraj, 4] = nodes[indeksMaxKraj, 2]
    
    for i in collect(1:length(A))
        found = false
        
        for k in collect(1:length(P))
            for j in collect(1:length(P[k]))
                if (P[k])[j] == A[i]
                    found = true
                    break
                end
            end
        end

        if !found && A[i] != A[indeksMaxKraj]
            nodes[i, 3] = nodes[indeksMaxKraj, 4] - T[i]
            nodes[i, 4] = nodes[indeksMaxKraj, 4]
        end
    end

    for i in collect(length(A):-1:1)
        for j in collect(1:length(P[i]))
            node = (P[i])[j]
            
            for k in collect(1:length(A))
                if node == A[k]
                    if nodes[k,3] == 0 || nodes[k,3] > nodes[i,3]
                        nodes[k,3] = nodes[i,3] - T[k]
                        nodes[k,4] = nodes[i,3]
                        break
                    end
                end
            end
        end
    end

    put = ""
    Z = 0

    for i in collect(1:length(A))
       if nodes[i,1] == nodes[i,3] && nodes[i,2] == nodes[i,4]
            Z += T[i]
            put = string(put,A[i],"-")
        end
    end
    put = SubString(put,1,length(put)-1)
    Z, put
end


A = ["A", "B", "C", "D", "E", "F", "G", "H", "I"]
P = [" - ", " - ", " - ", "C", "A", "A", "B, D", "E", "F, G"]
T = [3, 3, 2, 2, 4, 1, 4, 1, 4]
Z, put = CPM(A, P, T)


println("Z =  ", Z)
println("put = ”", put,"”")