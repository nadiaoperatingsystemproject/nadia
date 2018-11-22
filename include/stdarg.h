#ifndef NOS_STDARG_H
#define NOS_STDARG_H

typedef char *list_arg;


#define nos_rounded_size(TYPE)  \
  (((sizeof (TYPE) + sizeof (int) - 1) / sizeof (int)) * sizeof (int))


#define start_arg(AP, LASTARG) 						\
 (AP = ((list_arg) &(LASTARG) + nos_rounded_size (LASTARG)))


void end_arg (list_arg);
#define end_arg(AP)

#define get_arg(AP, TYPE)						\
 (AP += nos_rounded_size (TYPE),					\
  *((TYPE *) (AP - nos_rounded_size (TYPE))))

#endif /* _STDARG_H */