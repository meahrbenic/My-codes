import Pkg
using Pkg
Pkg.add("JuMP")
Pkg.add("GLPK")

using JuMP, GLPK

#Zadatak1 

using JuMP,GLPK
m1=Model(GLPK.Optimizer)

@variable(m1,x11>=0)
@variable(m1,x22>=0)

@objective(m1,Max,3x11+2x22)

@constraint(m1,c,0.5x11+0.3x22<=150)
@constraint(m1,cc, 0.1x11+0.2x22<=60)

optimize!(m1)
print("Status: ", termination_status(m1))

print("Rješenje: ")
print("x1=" ,value(x11))
print("x2=" ,value(x22))
print("Vrijednost cilja: ",objective_value(m1))

#Zadatak 2

m2=Model(GLPK.Optimizer)

@variable(m2, a>=0)
@variable(m2, b>=0)

@objective(m2,Min,40a+30b)

@constraint(m2,c1, 0.1a>=0.2)
@constraint(m2,c2, 0.1b>=0.3)
@constraint(m2,c3, 0.5a+0.3b>=3)
@constraint(m2,c4, 0.1a+0.2b>=1.2)

optimize!(m2)

print(termination_status(m2))
print("Rješenje: ")
print("x1=" ,value(a))
print("x2=" ,value(a))
print("Vrijednost cilja: ",objective_value(m2))


#Zadatak 3 

m4=Model(GLPK.Optimizer)

@variable(m4,x1>=0)
@variable(m4,x2>=0)
@variable(m4,x3>=0)

@objective(m4,Max,10x1+5x2+8x3)

@constraint(m4,const1,x1+x2+x3==100)
@constraint(m4,const2,2x1+1.5x2+0.5x3<=110)
@constraint(m4,const3, 2x1+x2+x3>=120)

optimize!(m4)

print("Status :", termination_status(m4))
print("Rješenje: ")
print("x1=" ,value(x1))
print("x2=" ,value(x2))
print("x3=" ,value(x3))
print("Vrijednost cilja: ",objective_value(m4))

delete(m4,const1)
unregister(m4,:const1)

delete(m4,x1)
unregister(m4,:x1)

delete(m4,x2)
unregister(m4,:x2)

delete(m4,x3)
unregister(m4,:x3)

delete(m4,const2)
unregister(m4,:const2)

delete(m4,const3)
unregister(m4,:const3)
 
#Zadatak 4

# Fabrika pravi tri vrste proizvoda (A, B i C). Pri proizvodnji, tri grupe mašina M1, M2 i M3 su kritične, jer
# su dostupne samo određeni broj sati. Broj raspoloživih sati za prvu, drugu i treću grupu mašina iznosi
# zbirno 630, 1680 i 2520 sati respektivno. Normativi vremena izrade ovih proizvoda u satima po kilogramu,
# prihod u KM po kilogramu i troškovi proizvodnje po kilogramu dati su u sljedećoj tabeli

m = Model(GLPK.Optimizer)
@variable(m,A>=0)
@variable(m,B>=0)
@variable(m,C>=0)

@objective(m,Max,100A+125B+100C)

@constraint(m,kon1,A+B+C<=630)
@constraint(m,kon2,2A+3B+C<=1680)
@constraint(m,kon3,2A+4B+7C<=2520)
@constraint(m,kon4,A<=39)
optimize!(m)

print("Status :", termination_status(m))
print("Rješenje: ")
print("A=" ,value(A))
print("B=" ,value(B))
print("C=" ,value(C))
print("Vrijednost cilja: ",objective_value(m))

#Zadatak 5

# Za oplemenjivanje tla koriste se dvije vrste vještačkog đubriva, koje imaju dvije vrste aktivnih sastojaka N
# i P. U svakom kilogramu prve vrste đubriva nalazi se po 15 grama sastojaka N i P, dok se u svakom
# kilogramu druge vrste đubriva nalazi 20 grama sastojka N i 10 grama sastojka P. Da bi parcela koja se
# razmatra bila na odgovarajući način oplemenjena, neohodno je najmanje 100 grama N i 70 grama P.
# Cijena prvog đubriva je 5 KM/kg, a drugog 2 KM/kg. Potrebno je odrediti koliko kilograma jednog i
# drugog đubriva treba kupiti da bi se zadovoljile potrebe uz najmanju cijenu.

model = Model(GLPK.Optimizer)
@variable(model,x>=0)
@variable(model,y>=0)

@objective(model,Min,5x+2y)

@constraint(model,kon11,15x+20y>=100)
@constraint(model,kon22,15x+10y>=70)

optimize!(model)

print("Status :", termination_status(model))
print("Rješenje: ")
print("x=" ,value(x))
print("y=" ,value(y))
print("Vrijednost cilja: ",objective_value(model))

#Zadatak 6

# Za pravilnu ishranu potrebno je unositi minimalno po 10 jedinica hranljivih komponeneta A i B. Trenutno
# je moguće nabaviti samo dva prehrambena proizvoda P1 i P2. Proizvod P1 sadrži po dvije jedinice
# komponente A i B po jednoj količinskoj jedinici proizvoda P1. Proizvod P2 sadrži četiri jedinice
# komponenete A i šest jedinica komponente B po jednoj količinskoj jedinici proizvoda P2. Jedinične cijena
# proizvoda su tri novčane jedinice za P1 i pet novčanih jedinica za P2. Potrebno je napraviti plan ishrane,
# odnosno nabavke prehrambenih proizvoda, koji će uz najmanje troškove zadovoljiti specificirane potrebe.

mod = Model(GLPK.Optimizer)
@variable(mod,a>=0)
@variable(mod,b>=0)

@objective(mod,Min,3a+5b)

@constraint(mod,ko1,2a+4b>=10)
@constraint(mod,kon2,a+6b>=10)

optimize!(mod)

print("Status :", termination_status(mod))
print("Rješenje: ")
print("a=" ,value(a))
print("b=" ,value(b))

print("Vrijednost cilja: ",objective_value(mod))

