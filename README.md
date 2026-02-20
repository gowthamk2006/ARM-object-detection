**ARM-Object-Detection
Real-Time Object Detection using Hardware-Accelerated YOLO CNN on Xilinx Zynq FPGA (ARM + FPGA Co-Design)**
**1. Introduction**

This project presents the hardware–software co-design and implementation of a YOLO-based Convolutional Neural Network (CNN) accelerated on a Xilinx Zynq FPGA platform with an integrated ARM processing system.

The objective is to achieve real-time object detection with reduced latency and optimized power consumption by offloading computationally intensive CNN operations to programmable logic (PL), while control and preprocessing are handled by the ARM processing system (PS).

**2. System Architecture Overview**

The system follows a heterogeneous architecture:

Processing System (PS – ARM Cortex-A9)
Image acquisition
Frame preprocessing
Data formatting
Post-processing (NMS, bounding box decoding)
Control and communication with FPGA
Programmable Logic (PL – FPGA Fabric)
Convolution acceleration
Activation functions
Pooling layers
Fully connected computation
Parallel MAC array implementation
The PS and PL communicate using AXI interfaces.

**3. Input Specifications**

Camera Resolution : 1280 × 720
Model Input Resolution : 640 × 640
Color Format : RGB
Target Frame Rate : 20 FPS
Frame size after resizing:
640 × 640 × 3 bytes ≈ 1.2 MB per frame

**4. Software Pipeline (ARM Processor)**
4.1 Preprocessing Stage

Operations:

Image resizing (bilinear interpolation)
Pixel normalization
Tensor transformation (HWC → CHW)
Execution Time (approximate):
Resize : ~6 ms
Normalization : ~2 ms
Tensor conversion: ~2 ms
Total preprocessing latency ≈ 10 ms

4.2 Post-Processing Stage

Operations:

Bounding box decoding
Confidence threshold filtering
Non-Maximum Suppression (NMS)
Final object classification mapping
This stage executes on ARM to avoid unnecessary FPGA resource usage.

**5. FPGA CNN Accelerator Architecture**
The CNN accelerator is implemented using either:

Verilog RTL design
or
High-Level Synthesis (HLS C++)

5.1 Accelerated Layers

Convolution layers
Activation layers (ReLU / Leaky ReLU)
Max pooling layers
Fully connected layers

5.2 Architectural Optimizations

Parallel Multiply-Accumulate (MAC) units
Loop unrolling for throughput enhancement
Deep pipelining for latency reduction
On-chip BRAM buffering
Reduced off-chip memory access
AXI burst-based memory transfer

5.3 Dataflow Strategy

Weight buffering in BRAM
Streaming input feature maps
Output feature map pipelining
Layer-wise processing
This minimizes memory bottlenecks and increases hardware utilization efficiency.

**6. Performance Metrics**

Input Resolution : 640 × 640
Preprocessing Latency : ~10 ms
FPGA Inference Latency : ~15–25 ms
Total System Latency : ~30–40 ms
Achieved Frame Rate : ~20 FPS
Power Consumption : Significantly lower than GPU-based systems

**7. Hardware–Software Partitioning**

Task Allocation Strategy:

ARM (PS):

Control logic
Memory management
Preprocessing
Post-processing
System orchestration

FPGA (PL):

Convolution operations
MAC-intensive layers
Feature map computation
This partitioning ensures optimal utilization of both processing domains.

**8. Project Directory Structure**
ARM-Object-Detection
│
├── software/
│   ├── main.cpp
│   ├── preprocessing.cpp
│   ├── postprocessing.cpp
│
├── hardware/
│   ├── cnn_accel.h
│   ├── cnn_accel.cpp
│   ├── cnn_accel.v
│
├── training/
│   ├── yolo_training.ipynb
│
└── README.md
**9. FPGA Implementation Flow**
CNN accelerator design (RTL / HLS)
Synthesis using Vivado / Vitis HLS
Implementation (place & route)
Bitstream generation
AXI integration with Zynq PS
Deployment on hardware
Real-time inference testing



**10. Applications**
Smart surveillance systems
Autonomous robotic systems
Industrial safety monitoring
Embedded vision platforms
Edge AI accelerators
