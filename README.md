# vNetTracer
vNetTracer is a network tracing system, which enables flexible and programmable network performance monitoring for virtualized networks in a highly efficient manner. 


# Dependency 

You need:

> gcc, python and bcc (https://github.com/iovisor/bcc)

Kernel modification: 

> sender side:

> receiver side:

# Usage 

To adopt vNetTracer in your systems, please follow the steps below:

1, Use the template bpf script to write and configure your own tracing scripts.

To configure your tracing:

> modify the files in the config folder based on your tracing purpose, such as IP addresses, ports, etc.

To write your tracing logic:

> modify the script.c file and add your c code inside.

2, Execute the tracing scripts to collect raw tracing data.

> $ python script.py

3, Calculate the raw tracing data and analyze the potential problems. 

# Example 

