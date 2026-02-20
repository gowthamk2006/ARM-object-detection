# ARM-Object-Detection

## Real-Time Object Detection using Hardware-Accelerated YOLO CNN on Xilinx Zynq FPGA (ARM + FPGA Co-Design)

---

## 1. Introduction

This project presents the hardware–software co-design and implementation of a YOLO-based Convolutional Neural Network (CNN) accelerated on a Xilinx Zynq FPGA platform with an integrated ARM processing system.

The objective is to achieve real-time object detection with reduced latency and optimized power consumption by offloading computationally intensive CNN operations to the Programmable Logic (PL), while control and preprocessing are handled by the Processing System (PS).

---

## 2. System Architecture Overview

The system follows a heterogeneous ARM + FPGA architecture.

### Processing System (PS – ARM Cortex-A9)

- Image acquisition  
- Frame preprocessing  
- Data formatting  
- Post-processing (Bounding box decoding, NMS)  
- System control and FPGA communication  

### Programmable Logic (PL – FPGA Fabric)

- Convolution acceleration  
- Activation functions (ReLU / Leaky ReLU)  
- Pooling layers  
- Fully connected computation  
- Parallel MAC array implementation  

Communication between PS and PL is achieved using AXI interfaces (AXI4 / AXI-Lite / AXI-Stream).

---

## 3. Input Specifications

| Parameter | Value |
|-----------|--------|
| Camera Resolution | 1280 × 720 |
| Model Input Resolution | 640 × 640 |
| Color Format | RGB |
| Target Frame Rate | 20 FPS |

Frame size after resizing:

640 × 640 × 3 bytes ≈ 1.2 MB per frame

---

## 4. Software Pipeline (ARM Processor)

### 4.1 Preprocessing Stage

**Operations**

- Image resizing (bilinear interpolation)  
- Pixel normalization  
- Tensor transformation (HWC → CHW format)  

**Execution Time**

- Resize: ~6 ms  
- Normalization: ~2 ms  
- Tensor Conversion: ~2 ms  

Total preprocessing latency ≈ 10 ms.

---

### 4.2 Post-Processing Stage

- Bounding box decoding  
- Confidence threshold filtering  
- Non-Maximum Suppression (NMS)  
- Final object classification mapping  

Post-processing is executed on the ARM processor.

---

## 5. FPGA CNN Accelerator Architecture

The CNN accelerator is implemented using:

- Verilog RTL  
- High-Level Synthesis (HLS C++)  

### 5.1 Accelerated Layers

- Convolution layers  
- Activation layers  
- Max pooling layers  
- Fully connected layers  

### 5.2 Architectural Optimizations

- Parallel Multiply-Accumulate (MAC) units  
- Loop unrolling  
- Deep pipelining  
- On-chip BRAM buffering  
- Reduced off-chip DDR access  
- AXI burst-based memory transfer  

### 5.3 Dataflow Strategy

- Weight buffering in BRAM  
- Streaming input feature maps  
- Output feature map pipelining  
- Layer-wise processing  

---

## 6. Performance Metrics

- Input Resolution: 640 × 640  
- Preprocessing Latency: ~10 ms  
- FPGA Inference Latency: ~15–25 ms  
- Total System Latency: ~30–40 ms  
- Achieved Frame Rate: ~20 FPS  
- Power Consumption: Lower than GPU-based systems  

---

## 7. Hardware–Software Partitioning

### ARM (Processing System)

- Control logic  
- Memory management  
- Preprocessing  
- Post-processing  
- System orchestration  

### FPGA (Programmable Logic)

- Convolution operations  
- MAC-intensive layers  
- Feature map computation  

---

## 8. Project Directory Structure

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
│   └── yolo_training.ipynb  
│  
└── README.md  

---

## 9. FPGA Implementation Flow

1. CNN accelerator design (RTL / HLS)  
2. Synthesis using Vivado / Vitis HLS  
3. Implementation (Place & Route)  
4. Bitstream generation  
5. AXI integration with Zynq PS  
6. Deployment on hardware  
7. Real-time inference validation  

---

## 10. Applications

- Smart surveillance systems  
- Autonomous robotic systems  
- Industrial safety monitoring  
- Embedded vision platforms  
- Edge AI accelerators  

---

## Author

Gowtham S  
AICTE Internship – Embedded Systems  
Domain: FPGA Architecture | VLSI | Edge AI Acceleration
