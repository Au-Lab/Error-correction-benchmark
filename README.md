# Generation of simulated maternal and paternal human genomes.

Two sets of SNPs (including positions and nucleostides) are randomly generated, and the simulated maternal and paternal genomes are obtained by modifiying the reference human genome using the simulated SNPs. This is completed by snp_simulate.cpp.


Compilation:

`g++ -O3 -std=c++0x snp_simulate.cpp -o snp_simulate`


Run:

`snp_simulate hg38.fa`

hg38.fa is the human reference genome.


Output:

maternal.fa: The simulated maternal genome.

paternal.fa: The simulated paternal genome.

simulated_snp.txt: All the simulated SNPs.


The file simulated_snp.txt in this repository records all the simulated SNPs that have been used in our paper.
