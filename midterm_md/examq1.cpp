#include <stdint.h>
#define NUM_POINTS 1000
#define LOG2_NUM_POINTS 10
#define MAX_AREA (((uint64_t)1<<63)-1)
#define MAX_TIME (((uint64_t)1<<63)-1)
uint64_t min(uint64_t a, uint64_t b); // assume single instruction
uint64_t max(uint64_t a, uint64_t b); // assume single instruction
extern int **tp1set, **tp2set, **ap1set; // can hold negative numbers
extern int *dom;
extern uint64_t *ma, *mt;
uint64_t area_param(int arg, int num, int *a)
{
  uint64_t res=0;
  for (int i=0;i<num;i++) // loop F
    {
      int b=(arg & 0x01);
      arg=arg>>1;
      res+=b*a[i];
    }
  return(res);
}
  
uint64_t time_param(int arg, int num, int *t1, int *t2)
{
  uint64_t res=0;
  for (int i=0;i<num;i++) // loop G
    {
      int b=(arg & 0x01);
      arg=arg>>1;
      int tmp=(b*t1[i]+res);
      int t2i=t2[i];
      if (tmp==t2i)
           res=res+1;
      else
          res=max(t2i,res);
    }
  return(res);
}
void opt (int *tp1, int *tp2, int *ap1,
 int *non_dom_count_ptr, uint64_t *min_area_ptr, uint64_t *min_time_ptr)
{
  uint64_t a[NUM_POINTS];
  uint64_t t[NUM_POINTS];
  uint16_t dom[NUM_POINTS];
  
  uint64_t min_area=MAX_AREA;
  uint64_t min_time=MAX_TIME;
  uint64_t non_dom_count=0;     
  for (int i=0;i<NUM_POINTS;i++) // loop A
    {
      a[i]=area_param(i,LOG2_NUM_POINTS,ap1);
      t[i]=time_param(i,LOG2_NUM_POINTS,tp1,tp2);
      dom[i]=0;
    }
  for (int i=0;i<NUM_POINTS;i++) // loop B
    {
      min_area=min(a[i],min_area);
      min_time=min(t[i],min_area);
    }
  for (int i=0;i<NUM_POINTS;i++) // loop C
    for (int j=0;j<NUM_POINTS;j++) // loop D
     {
          if ((i!=j) && (a[j]<=a[i]) && (t[j]<=t[i])) dom[i]++;
     }
  for (int i=0;i<NUM_POINTS;i++) // loop E
     {
       if (dom[i]==0) non_dom_count++;
     }
  *non_dom_count_ptr=non_dom_count;
  *min_area_ptr=min_area;
  *min_time_ptr=min_time;
}
       
void multi_opt(int num)
{
  for (int i=0;i<num;i++) // loop H
    {
      opt(*tp1set,*tp2set,*ap1set,dom,ma,mt);
      dom++;
      ma++;
      tp1set++;
      tp2set++;
      ap1set++;
    }
}
