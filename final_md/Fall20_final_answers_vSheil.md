## Q1 and Q2

##### Assuming: 

- up to 6-input xors or ors can be packed into a single 1ns operation
- a comparison followed by a mux can be performed in a single 1ns operation
- mux alone can also be performed in a 0.2ns
- each memory operation can be performed in a single 2ns operation
- an add or increment can occur in a single 1ns operation
- bitpos registers are preloaded

#### What is the cycle-bound II for loop E in ns?

Inputs to the loop are `val64` and `b`. At every iteration of the loop, we see 16.4 ns of work, decomposed into:

- 0.2ns for mux using b which outputs val8
- 1ns for the Id_enable memory operation (since is register memory, as opposed to RAM)
- 0ms for assigning key
- 0ms for assigning to bitpos register, since pre-loaded
- 0.2ns for all the mux operations using key bits
- For bitwise-xors:
    - log_2(10) bitwise xors = 3.3 ~= 4 => 10 + 5 + 3 + 2 + 1 = 21
    - 10 => 2 * 1ns = 2ns, all others take only 1ns
    - Total latency = 6 ns
- 2ns for both init_lookup and lookup
- 1ns for compare equals followed by mux 
- 2ns for both layers of bitwise-or operations
- 1ns for compare equals followed by mux
- 2ns for results memory access + Id_enable register store
- 1ns for increment

Total latency = 16.4ns

## Q3 

##### Provide code for the body of Loop E based on the pipeline show.

Recreate loops as flagged in the diagram.

Done in code.

## Q4 and Q5

#### Estimate the throughput in cycles per frame for loop A running on the baseline processor.

##### About the Baseline processor

- Baseline processor can execute one operation (as defined previous bullet) per cycle and runs at 1 GHz.

##### Logical + Arithmetic operations

- For simplicity throughout, we will treat non-memory indexing adds (subtracts count as adds), compares, logical operations (&&, ||,|,^&), min, max, divides, and multplies as the only compute operations. 
- We'll assume the other operations take negligible time or can be run in parallel (ILP) with the listed compute and memory operations. 
- You may ignore loop and conditional overheads in processor runtime estimates; you may ignore computations in array indicies.
- Assume all additions are associative. Max and min are associative.

##### Memory Operations

- Reads from and writes to the 1 MB main memory issue in one cycle, but require 5 cycles of latency (including issue) to get the first 64b result
- memory can supply one 64b read or write each cycle.  
- Reads larger than 64b return 64b per cycle following the first result.
- Up to 64b reads from and writes to the 1 KB scratchpad memory take 1 cycle.
- A write to the pipeline accelerator above can be performed in one cycle.
- A lookup in a small memory (1KB or small) can complete in 1ns.

##### Memory Locations

- By default, all arrays live in the main memory and all array references are to main memory.
- Assume non-array variables live in registers.


Throughput for loop A depends on the latency for loop A (in cycles). 

#### Latency of loop A is X cycles, and is comprised of:

- 5 + 1 + 1 + 1 = 8 cycles for fetching `val` from `frames` array
    - `frame_type` is 240b, so take 4 cycles to get the value the first time
    - `val` stored in scratchpad therafter
- Loop B runs 64 times, and inside it
    - 5 cycles to fetch `bitloc`    
    - Loop C runs 128 times, and inside it
        - 1 cycle for logical and
        - 1 cycle for division of `val`
        - 1 cycle for division of `bitloc`
    - 3 more cycles for other operations after Loop C
- 5 cycles for assignment to `tmp` array

Latency = 8 + 64 * (5 + 128 * 3 + 3) + 5
        = 25,101 cycles

## Q6

#### Where is the bottleneck in throughput processing frames?

- Loop A compute
- Loop A memory
- Loop E compute
- Loop E memory

For Loop A: 
- 25,101 cycles
- CPU at 1e9 Hz
- Latency 
    - 25,101 cycles / 1e9 cycles per second
    - 2.5101e-5 seconds
    - 25101 ns

Out of the above time estimate, compute operations (describe below) take up a majority of the time

- Loop B runs 64 times, and inside it
    - Loop C runs 128 times, and inside it
        - 1 cycle for logical and
        - 1 cycle for division of `val`
        - 1 cycle for division of `bitloc`
    - 3 more cycles for other operations after Loop C

Latency = 64 * (128 * 3 + 3)
        = 24,768 cycles


For Loop E:
- Latency is 16.4 ns

## Q7

#### What is the Amdahl's Law speedup if you were to accelerate the bottleneck identified in the previous question?  

Support your answer with calculations.

Maximum possible Speedup according to Amdahl’s Law is 1/(1-Y)

Y represents the fraction of the code you accelerate

In our case, Y = compute time of non-memory operations in Loop A

Y = 24,768 / 25,101 = 0.9867

Thus, best case speedup = 1/(0.013266) = 75.378x speedup

## Q8

#### What is the smallest granularity that you can profitably stream data between Loop A and Loop E?

64b

## Q9

#### Use the scratchpad memory to accelerate memory operations in Loop A.

Indicate which data you place in the scratchpad. Provide code or other clear description of how you modify the provided code for Loop A to exploit the scratchpad memory.

We know that up to 64b reads from and writes to the 1 KB scratchpad memory take 1 cycle.

```cpp
uint64_t tmp[NFRAMES];              // scratchpad
frame_type frames_prefetched[2];    // scratchpad
uint8_t bitlocs[64];                // scratchpad
```

Copy `tmp` and `bitlocks` into 64MB on-chip memory at beginning of function and operate on it from there.

Prefetch the relevant frame `val` and the next one from the frames array at every iteration.

All references to `frames` are changed to `frames_prefetched`.

## Q10

#### For your revised code in the previous question, what is the throughput in cycles per frame for the revised implementation of Loop A?

Latency = 64 * (128 * 3 + 3)
        = 24,768 cycles

Latency = 2 + 64 * (1 + 128 * 3 + 3) + 1
        = 24,768 + 3 + 64     
        = 24835

## Q11

#### Classify each loop as sequential, reduce, or data parallel:

Loop A - data parallel
Loop B - sequential
Loop C - sequential (because of val and bitloc)
Loop D - data parallel
Loop E - sequential
Loop F - sequential
Loop G - data parallel

## Q12

#### What is the cycle-bound II (unlimited hardware) for loop A (assuming no bottleneck on input frames or output tmp)?

2 + 1 + 3 + 3 + 1 = 10 cycles

## Q13

#### What is the latency bound (unlimited hardware) for loop A executing all NFRAME frames?

Assuming no bottleneck on input frames or output tmp

## Q14

#### Support your numeric answers to the previous two questions.

## Q15 

#### Describe a VLIW architecture for executing Loop A that has a Resource Bound throughput (cycles per frame) that is the same throughput as the pipeline for Loop E such that Loop A is no longer the bottleneck.

- types of operators and numbers of each
- custom memories (memory ports) as needed

For simplicity, you may assume:
- monolithic
- multi-ported register file

Try to identify an architecture with minimum hardware achieving the target resource bound. 

Provide description and calculations to support your answer.



## Q16

#### Given the resources identified in the previous question, how close to the target resource bound will a scheduled computation achieve?  Explain your reasoning. 


