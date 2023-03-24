############ B1 #############
disc.area = function(a,b,c,esantion)
{
  nr=0;
  for(i in 1:esantion)
  {
    x=runif(1,-a,b)
    y=runif(1,-b,b)
    z=runif(1,-c,c)
    if(((x^2)/(a^2))+((y^2)/(b^2))+((z^2)/(c^2))<=1)
      nr=nr+1
  }
  estim=2*a*2*b*2*c*nr/esantion
  val_exacta = (4*pi*a*b*c)/3
  e_rel=abs(estim-val_exacta)/abs(val_exacta);
  cat("valoare estimata",estim,"valoare exacta",val_exacta,"\n")
  cat("eroare relativa:",e_rel,"\n");
}

disc.area(3,2,4,10000)
disc.area(3,2,4,20000)
disc.area(3,2,4,50000)

############ B2 #############
B2 = function(val)
{
  c=0;
  for(i in 1:val)
  {
    x=runif(1,0,2);
    y=runif(1,0,4);
    if(y<=x & 2*x+y<=4)
      c=c+1;
  }
  return(8*c/val);
}
B2(45000)

"
Zona in care putem incadra acest triunghi este un dreptunghi, 
aria acestui dreptunghi este de 2*4 = 8;
"

############ B3 (a) #############
MC.Integration = function(N)
{
  sum=0;
  for(i in 1:N)
  {
    u=runif(1,0,1);
    sum=sum+1/(1+u^(1/2));
  }
  estimare=sum/N;
  cat("estimare:",estimare,"val exac: 2-2ln2")
}
#MC.Integration(1000)


############ B3 (b)#############
B3_b= function(N,a)
{
  sum=0;
  for(i in 1:N)
  {
    u=runif(1,0,a);
    sum=sum+(1/(1+u^2));
  }
  estimare=a*sum/N;
  cat("estimare:",estimare,"val exacta:",pi/2);
}
B3_b(20000,100)


