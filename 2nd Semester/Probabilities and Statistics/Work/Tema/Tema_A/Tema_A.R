############ A1 (a) #############
A1.poisson = function(lambda,k,l)
{
  x=k:l;
  #print(x);
  y=dpois(x,lambda);
  #plot(y,type='l',main='poisson graph');
  barplot(y, main = 'poisson graph')
  print(max(y));
}
A1.poisson(8,2,17)


############ A1 (b) #############
A1geom = function(p,k,l)
{
  x=k:l;
  print(x);
  y=dgeom(x,p);
  barplot(y);
  print(max(y));
}
A1geom(0.5,5,14)


############ A2 (a) #############
A2.a = function(file)
{
  var = scan(file)
  mij=median(var) #mijloc
  media=mean(var) #media
  distrib=sd(var) #deviatia standard
  q=quantile(var)
  v = c( mij, media, distrib, q)
  return (v)
}
A2.a("inputText.txt")


############ A2 (b) #############
A2.b = function(file)
{
  var = scan(file)
  v2=vector()
  mean=mean(var) #
  sd = sd(var) #
  
  # media si sd sa fie intre m-2s si m+2s
  
  tot=1
  for(i in 1:length(var))
  {
    if(var[i]>=mean-2*sd & var[i]<=mean+2*sd)
    {
      v2[tot] = var[i]
      tot=tot+1
    }
  }
  return(v2)
}
A2.b("inputText.txt")


############ A2 (c) #############
A2.c = function(file)
{
  #x = scan(file)

  x = A2.b(file);
  print(x);
  mini = min(x) - min(x)%%10;
  maxi = max(x) - max(x)%%10;
  
  interv = seq(mini, maxi, 10);
  hist(x, breaks=interv, main="Distributia Frecventelor", right=F, freq=T)
}

A2.c("inputText.txt")

