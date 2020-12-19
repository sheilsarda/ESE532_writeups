## Q2

Loops A, B, C, E each run 1000 times-- each iteration takes the following time:
- Loop A takes 80 cycles for area, 150 cycles for time computation in each iteration assuming reads from main memory take 5 cycles to produce a result
- Loop B takes 12 cycles each iteration, including time for 2 reads
- Loop C takes 1000* 31 cycles each iteration due to nested for loop
- Loop E takes 7 cycles each iteration
- In total, `opt` takes 31,249,000 cycles

## Q3

Bottleneck is Loop C since it takes the most cycles

## Q4

We know that as S goes to infinity, T_Before / T_After = 1 / (1 - Y) where Y is % code

In our case, Loop C comprises (31e6 / 31.249e6) % of code = 99.20%
Thus, T_Before / T_After = 1 / 0.0122 = 125x

## Q5

A --> B
A --> C
A --> E
C --> E

## Q6

A, E, D

## Q7

- A is data parallel because it makes two independent function calls to `area_param` and `time_param` where neither depend on the other's result, and are stored in independent memory locations.
- B is not data parallel because each loop iteration references the previous iterations result, since it compares the smallest `min_area` seen in the previous cycle with `a[i]` of the current cycle and similarly for `min_time`
- C is data parallel because for each iteration of `i`, the inner for loop makes comparisons between variables which are unchanged between iterations. The only variable changed is `dom[i]` which is unique to each iteration of C, so no race conditions occur
- D is not data parallel because the result of each iteration's comparisons potentially increment the same variable, which could lead to concurrency issues like race conditions. To prevent this, the variable `dom[i]` needs to be modified sequentially instead of in parallel
- E is not data parallel because each iteration of the loop potentially increments the same variable `non_dom_count`, so they must be performed in sequence
- F and G are not data parallel because each iteration of the for loop references the `arg` computed in the previous iteration's `arg = arg >> 1` computation

## Q8

Ignoring resource limits we compute the critical path lower bound as follow:

- Parallelizing A means the loop now completes in 70 cycles
- Parallelizing C means the loop now completes in 1000 * 6 = 6000 cycles
- B and E take 1000 * ( 2 + 2) = 4000 cycles
- `opt()` completes in 70 + 6000 + 4000 = 10,070 cycles

## Q9

## Q10

## Q11

```cpp
      int b=(arg & 0x01); // 1 cycle
      arg=arg>>1;
      int tmp=(b*t1[i]+res); // 3 cycles 
      int t2i=t2[i]; // 1 cycle
      if (tmp==t2i) // 1 cycle
           res=res+1; // 1 cycle
      else
          res=max(t2i,res); // 1 cycle
```

7 cycles is the longest path

At 1GHz (10^9 cycles / sec), each loop iteration will take 7 / 10^9 seconds

## Q12

## Q13

Mapping of `multi_opt()` to the heterogenous system
- Loop B is assigned to a single-issue baseline pipe because it needs to happen sequentially, so running it on the vector pipeline will not provide a speed-up
- Loop C can be split up into segments of `NUM_POINTS / 5` and each of the segments can be assigned individually to a 64-bit width vector lane to run in parallel. Within each of the vector lanes, Loop D is run sequentially
- Loop E is run on the remaining single-issue baseline pipe since it has to run sequentially
- Loop A is dependent on the result of the area and time pipes and issues 3 write calls after getting the result. Use the remaining 3 vector pipeline to parallelize these write calls after reading in the result from the area and time pipeline

## Q14
- B takes 12 * 1000 ns
- C & D take 1000 . 5 * (6 + 5) = 2200 ns
- E takes 1000 * 7 ns
- A takes 1000 * max(4, 7) = 7000 ns

Throughput of pipeline is therefore 1 / 12000 ns

## Q15

Using above result, latency is 12000ns