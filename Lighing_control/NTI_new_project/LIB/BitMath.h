


#ifndef BITMATH_H_
#define BITMATH_H_


#define SET_BIT(R,N) ((R)|=(1<<(N)))
#define CLR_BIT(R,N) (R&=(~(1<<(N))))
#define GET_BIT(R,N) (((R)>>(N))&1)

#define TOG_BIT(R,N) ((R)^=(~(1<<(N))))
#define IS_HIGH(R,N) (((R)>>(N))&1)
#define IS_LOW(R,N)  (!(((R)>>(N))&1))



#endif /* BITMATH_H_ */