############ E1 #############
E1=function(alfa,tip_ipoteza,sample_mean,population_mean,n,sigma)
{
  z_score=(sample_mean - population_mean)/(sigma/sqrt(n))
  #cazul asimetric la dreapta
  if(tip_ipoteza=='right')
  {
    critical_z=qnorm(1-alfa)
    if(z_score<critical_z)
      return('se accepta ipoteza alternativa')
  }

  #left
  if(tip_ipoteza=='left')
  {
    critical_z=qnorm(alfa)
    if(z_score<critical_z)
      return('se accepta ipoteza alternativa')
    
  }
  #simetric
  if(tip_ipoteza=='s')
  {
    critical_z=qnorm(1-alfa/2)
    if(abs(z_score)>abs(critical_z))
      return('se accepta ipoteza alternativa')
  }
  return('nu avem suficiente dovezi pentru a respinge ipoteza nula')
}
E1(0.01,'left',27,30,50,3.5)

############ E2 #############
E2=function(alfa,tip_ipoteza,z_score)
{
  if(tip_ipoteza=='right')
  {
    critical_z=qnorm(1-alfa)
    if(z_score<critical_z)
      return('se accepta ipoteza alternativa')
  }
  
  #left
  if(tip_ipoteza=='left')
  {
    critical_z=qnorm(alfa)
    if(z_score<critical_z)
      return('se accepta ipoteza alternativa')
  }
  
  #simetric
  if(tip_ipoteza=='s')
  {
    critical_z=qnorm(1-alfa/2)
    if(abs(z_score)>abs(critical_z))
      return('se accepta ipoteza alternativa')
  }
  
  return('nu avem suficiente dovezi pentru a respinge ipoteza nula')
}
E2(0.01,'s',2.05)
E2(0.05,'s',2.05)

############ E3 #############
E3=function(tip_ipoteza,m0,n1,n2,sample1_mean,sample2_mean,sigma1,sigma2,alfa)
{
  combined.sigma = sqrt(sigma1^2/n1 + sigma2^2/n2)
  z_score= (sample1_mean - sample2_mean -m0)/combined.sigma
if(tip_ipoteza=='right')
{
  critical_z=qnorm(1-alfa)
  if(z_score<critical_z)
    return('se accepta ipoteza alternativa')
}
  
#left
if(tip_ipoteza=='left')
{
  critical_z=qnorm(alfa)
  if(z_score<critical_z)
    return('se accepta ipoteza alternativa')
}
  
#simetric
if(tip_ipoteza=='s')
{
  critical_z=qnorm(1-alfa/2)
  if(abs(z_score)>abs(critical_z))
    return('se accepta ipoteza alternativa')
}
  
return('nu avem suficiente dovezi pentru a respinge ipoteza nula')
} 
E3('s',0,200,224,7.8,8.1,1.15,0.92,0.01)
E3('s',0,200,224,7.8,8.1,1.15,0.92,0.05)

############ E4 #############
E4=function(tip_ipoteza,m0,n,sample1_mean,sample2_mean,sigma1,sigma2,alfa)
{
combined.sigma = sqrt(sigma1^2/n + sigma2^2/n)
z_score= (sample1_mean - sample2_mean - m0)/combined.sigma

if(tip_ipoteza=='right')
{
  critical_z=qnorm(1-alfa)
  if(z_score<critical_z)
    return('se accepta ipoteza alternativa')
}

#left
if(tip_ipoteza=='left')
{
  critical_z=qnorm(alfa)
  if(z_score<critical_z)
    return('se accepta ipoteza alternativa')
}

#simetric
if(tip_ipoteza=='s')
{
  critical_z=qnorm(1-alfa/2)
  if(abs(z_score)>abs(critical_z))
    return('se accepta ipoteza alternativa')
}

return('nu avem suficiente dovezi pentru a respinge ipoteza nula')
}
E4('right',0,50,102,109,8.3,7.5,0.01)

############ E5 #############
E5=function(tip_ipoteza,n,sigma1,sigma2,alfa)
{
  f_score=(sigma1^2)/(sigma2^2)
  if(tip_ipoteza=='r')
  {
    critical_f=qf(1-alfa,n-1,n-1)
    if(f_score>critical_f)
      return('se accepta ipoteza alternativa')
  }
  
  #cazul simetric
  if(tip_ipoteza=='s')
  {
    critical_fs=qf(alfa/2,n-1,n-1)
    critical_fd=qf(1-alfa/2,n-1,n-1)
    if(f_score<critical_fs || f_score>critical_Fd)
      return('se accepta ipoteza alternativa')
  }
  
  return('nu avem suficiente dovezi pentru a respinge ipoteza nula')
  #caz asm la dr
}
E5("right",22,2.15,1.95,0.01)


