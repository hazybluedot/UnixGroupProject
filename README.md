## Central Limit Theorem Calculator 

The
[Central Limit Theorem](http://stattrek.com/statistics/dictionary.aspx?definition=central_limit_theorem)
(CLT) is a probabilistic law which states that the mean of a sample
population will be normally distributed (bell-shaped) provided that
there are enough members in the sample. This program will calculate
[confidence intervals](http://stattrek.com/statistics/dictionary.aspx?definition=confidence_interval)
for given sample data.

Elements of the Unix Philosophy incorporated into the CLT Calculator are: 1.) 
Rule of Clarity, 2.) Rule of Simplicity, and 3.) Rule of Modularity. The Rule of 
Clarity and the Rule of Simplicity will be used in designing the core algorithm 
of the CLT Calculator by minimizing the amount of extraneous operations required to 
execute the Central Limit Theorem, while maintaining a consistent style to aid
the reader in traversing the code. The Rule of Modularity will be enforced through
the usage of short, concise functions that all perform a single, clear task.

## Instructions

~~~~
$ make
~~~~

This will compile three programs:

stats
: calcualate mean and standard deviation of sample data

cint
: calculate confidence interval of sample data

## Test data

Test data is available in the `test` directory

~~~~
$ ./stats < test/weight_data
180, 29.2793
$ ./cint -c 95% < test/weight_data
180     1.81475 178.185 181.815
~~~~
