var R = require("../lib/probability");
print("runif(10,1,2)=%s", R.runif(10, 1, 2));
print("dunif(1.6)=%s", R.dunif(1.6, 1, 2));
print("punif(1.6)=%s", R.punif(1.6, 1, 2));
print("qunif(0.6)=%s", R.qunif(0.6, 1, 2));
print("rnorm(10,5,1)=%s", R.rnorm(10, 5, 1));
print("dnorm(5,5,1)=%s", R.dnorm(5, 5, 1));
print("pnorm(5,5,1)=%s", R.pnorm(5, 5, 1));
print("qnorm(0.5,5,1)=%s", R.qnorm(0.5, 5, 1));
print("rexp(10,2)=%s", R.rexp(10, 2));
print("rexp=", R.rexp);
print("rexp1(2)=%s", R.rexp1(2));
print("dexp(1,2)=%s", R.dexp(1, 2));
print("pexp(1,2)=%s", R.pexp(1, 2));
print("qexp(0.5,2)=%s", R.qexp(0.5, 2));
print("rbinom(10, 5, 0.5)=%s", R.rbinom(10,5,0.5));
print("dbinom(4, 5, 0.5)=%s", R.dbinom(4,5,0.5));
print("dbinom(5, 5, 0.5)=%s", R.dbinom(5,5,0.5));
print("pbinom(4, 5, 0.5)=%s", R.pbinom(4,5,0.5));
print("qbinom(0.9, 5, 0.5)=", R.qbinom(0.9,5,0.5));
