############ D1 #############
D1=function(n,sample_mean,alfa,s)
{
  
  critical_t=qt(1-alfa/2,n-1)
  a=sample_mean-critical_t*s/(sqrt(n))
  b=sample_mean+critical_t*s/(sqrt(n))
  cat("intervalul de incredere este (",a, ",",b,"),\n")

  }
D1(150,490,0.05,85)

############ D2 #############
D2=function(n,sample_mean,alfa,s)
{
  
  critical_z=qnorm(1-alfa/2,0.1)
  a=sample_mean-critical_z*s/(sqrt(n))
  b=sample_mean+critical_z*s/(sqrt(n))
  cat("intervalul de incredere este (",a, ",",b,"),\n")

}
D2(25,101.5,0.01,5)

############ D3 #############
D3=function(n,p0,pprim,alfa,tip)
{
  zscore=(pprim-p0)/sqrt(p0*(1-p0)/n)
  if(tip=='left')
  {
    cat("asimetrica la stanga:\n")
    critical_z=qnorm(alfa,0,1)
    if(zscore<critical_z)
      cat("ipoteza nula e respoinsa si accept ip alternativa")
    else
      cat("nu avem suficiente dovezi.\n")
  }
  if(tip=='right')
  {
    cat("asimetirca la dreapta:\n")
    critical_z=qnorm(1-alfa,0,1)
    if(zscore>critical_z)
      cat("ip nula este respinsa si accept ip alternativa")
    else
      cat("nu avem suficiente dovezi.\n")
  
  }
  if(tip=='s')
  {
    cat("Simetrica:\n")
    critical_z=qnorm(1-alfa/2,0,1)
    if(abs(zscore)>abs(critical_z))
      cat("Ipoteza nula este respinsa si accept ipoteza alternativa")
    else cat("Nu avem suficiente dovezi.\n")
  }
  cat("Scorul:", zscore," Valoarea critica: ", critical_z, "\n");
}
D3(1179,0.08,0.085,0.01,"left")
D3(1179,0.08,0.085,0.05,"left")
#testez daca p != p0 => simetrica 

############ D4 #############
D4 = function(n,p0,succese,alfa,tip)
{
  
  pprim=succese/n
  zscore=(pprim-p0)/sqrt(p0*(1-p0)/n)
  if(tip=='left')
  {
    cat("asimetrica la stanga:\n")
    critical_z=qnorm(alfa,0,1)
    if(zscore<critical_z)
      cat("ipoteza nula e respinsa si accept ip alternativa")
    else
      cat("nu avem suficiente dovezi.\n")
  }
  if(tip=='right')
  {
    cat("asimetirca la dreapta:\n")
    critical_z=qnorm(1-alfa,0,1)
    if(zscore>critical_z)
      cat("ip nula este respinsa si accept ip alternativa")
    else
      cat("nu avem suficiente dovezi.\n")
    
  }
  if(tip=='s')
  {
    cat("Simetrica:\n")
    critical_z=qnorm(1-alfa/2,0,1)
    if(abs(zscore)>abs(critical_z))
      cat("Ipoteza nula este respinsa si accept ipoteza alternativa")
    else cat("Nu avem suficiente dovezi.\n")
  }
  cat("Scorul:", zscore," Valoarea critica: ", critical_z, "\n");
}
D4(250,0.4,95,0.01,"s")
D4(250,0.4,95,0.05,"s")

