##Get Started

```
$ git clone git@github.com:r3fang/tfc.git
$ cd tfc
$ make
$ ./tfc predict exon.fa.gz A431-1-ABGHI_S1_L001_R1_001.fastq.gz A431-1-ABGHI_S1_L001_R2_001.fastq.gz
```

##Introduction

TFC is a super lightweight, stand-alone, ultrafast, C-implemented, mapping-free and sensitive software designed for fusion detection between candidate genes from RNA-seq data. It consists of two major components:
 
```
$ ./tfc 

Program: tfc (targeted gene fusion calling)
Version: 08.19-r15
Contact: Rongxin Fang <r3fang@ucsd.edu>

Usage:   tfc <command> [options]

Command: name2fasta     extract DNA sequences
         predict        predict gene fusions
```

- **name2fasta** 
  >extract *exon/transcript/CDS* sequences of targeted genes, the usage information is as below. Before running it, genes.gtf has to be sorted based on the 4th column `sort -k5,5n genes.gtf > genes.sorted.gtf`;
 
```
$./tfc name2fasta

Usage:   tfc name2fasta [options] <gname.txt> <genes.gtf> <in.fa> <out.fa> 

Details: name2fasta is to extract genomic sequence of gene candiates

Options: -g               'exon' or 'transcript' or 'CDS' 

Inputs:  gname.txt        .txt file contains the names of gene candiates
         genes.gtf        .gft file that contains gene annotations
         in.fa            .fa file contains the whole genome sequence e.g. [hg19.fa]
         out.fa           .fa files contains output sequences
```

- **predict** 
  >predict fusions between targeted genes. Before running it, user has to make sure R1.fq and R2.fq have their read's name matched up. Sort R1.fq and R2.fq based on id if necessary

```
# sort R1.fq and R2.fq if necessary
$ zcat R1.fq.gz | paste - - - - | sort -k1,1 -S 3G | tr '\t' '\n' | gzip > R1.sorted.fq.gz
$ zcat R2.fq.gz | paste - - - - | sort -k1,1 -S 3G | tr '\t' '\n' | gzip > R2.sorted.fq.gz

$ ./tfc predict

Usage:   tfc predict [options] <exon.fa> <R1.fq> <R2.fq>

Details: predict gene fusion from pair-end RNA-seq data

Options:
   -- Graph:
         -k INT    kmer length for indexing in.fa [15]
         -n INT    min unique kmer matches for a hit between gene and pair [10]
         -w INT    edges in graph of weight smaller than -w will be removed [3]
   -- Alignment:
         -m INT    score for match [2]
         -u INT    penality for mismatch[-2]
         -o INT    penality for gap open [-5]
         -e INT    penality for gap extension [-1]
         -j INT    penality for jump between genes [-10]
         -s INT    penality for jump between exons [-8]
         -a FLOAT  min identity score for alignment [0.80]
   -- Junction:
         -h INT    min hits for a junction [3]
         -l INT    length for junction string [20]
         -x INT    max mismatches allowed for junction string match [2]
   -- Fusion:
         -A INT    weight for junction containing reads [3]
         -p FLOAT  p-value cutoff for fusions [0.05]

Inputs:  exon.fa   .fasta file that contains exon sequences of 
                   targeted genes, which can be generated by: 
                   tfc name2fasta <gname.txt> <genes.gtf> <in.fa> <exon.fa>  
         R1.fq     5'->3' end of pair-end sequencing reads
         R2.fq     the other end of sequencing reads
```

## FAQ

 1. **How fast is TFC?**
 2. **Does TFC depend on any third-party software?**\n
    >No. TFC is compeletely stand-alone which means it depends on nothing.
 3. **How precise is tfc?**
 4. **Does tfc work for single-end reads?**

## Workflow

![workflow](https://github.com/r3fang/tfc/blob/master/img/workflow.jpg)


#### Version
08.19-r15

#### Author
Rongxin Fang (r3fang@eng.ucsd.edu)

