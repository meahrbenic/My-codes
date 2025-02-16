function najkraci_put(M)

putevi=zeros(size(M,1),3)

for i in 1:size(M,1)
  for j in 1:3
    if(i!=1)
      putevi[i,1] = i
      putevi[i,2] = Inf
    else
      putevi[1,1] = 1
      putevi[1,3] = 1
    end
  end
end

for j in 1:size(M,1)
  for i in 1:size(M,1)
    if(M[i,j]!=0 && i<j && M[i,j]+putevi[i,2]<=putevi[j,2])
    putevi[j,2] = M[i,j] + putevi[i,2]
    putevi[j,3] = i 
    end  
  end
end

return putevi
end


M1 = [0 1 3 0 0 0; 0 0 2 3 0 0; 0 0 0 -4 9 0; 0 0 0 0 1 2; 0 0 0 0 0 2; 0 0 0 0 0 0]; 
putevi = najkraci_put(M1);
print(putevi);
