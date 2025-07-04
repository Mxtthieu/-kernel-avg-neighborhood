# OpenCL Kernel for Local Neighborhood Averaging
This project implements an OpenCL kernel that computes the average of elements based on a user-defined local neighborhood. Each element is replaced by the average of its surrounding values within a specified window size. 
The kernel supports two input arrays and writes the computed averages to an output buffer.
<br>This technique is commonly used in signal processing, smoothing operations, and local filtering.<br>
The kernel is designed to be efficient and scalable, making use of parallel execution to process large datasets.
