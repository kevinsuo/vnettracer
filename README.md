# vNetTracer
vNetTracer is a network tracing system, which enables flexible and programmable network performance monitoring for virtualized networks in a highly efficient manner. 

To adopt vNetTracer in your systems, please follow the steps below:
1, use the template bpf script to write and configure your own tracing scripts.
2, execute the tracing scripts to collect raw tracing data.
3, calculate the raw tracing data and analyze the potential problems. 

# Dependency 

You need:

> gcc, python and bcc (https://github.com/iovisor/bcc)

# Run 

To execute the bpf script:

> $ python script.py

# Configuration 

To configure your tracing:

> modify the files in the config folder based on your tracing purpose, such as IP addresses, ports, etc.


