#include <inttypes.h>
#include <stdio.h>

#define DEFINE_PAIR(type)                           \
    typedef struct {                                \
        type a;                                     \
        type b;                                     \
    } pair_##type ;                                 \
    void print_pair_##type(pair_##type a) {         \
        printf("( ");                               \
        print_##type(a.a);                          \
        print_##type(a.b);                          \
        printf(")");                                \
    }

void error(const char *s) {
    fprintf(stderr, "%s", s);
    abort();
}

void print_int64_t(int64_t a) {
    printf("%" PRId64 " ", a);
}

void print_double(double a) {
    printf("%lf ", a);
}


#define DEFINE_LIST(type)                                               \
  struct list_##type {                                                  \
    type value;                                                         \
    struct list_##type* next;                                           \
  };                                                                    \
  void print_list_##type(struct list_##type const* l) {                 \
      while(l) {                                                        \
          print_##type(l->value);                                       \
          l = l->next;                                                  \
      }                                                                 \
      printf("\n");                                                     \
  }                                                                     \

#define print(x)                                                        \
    _Generic((x),                                                       \
         struct list_int64_t * : print_list_int64_t(x),                 \
         struct list_double * : print_list_double(x),                   \
         struct list_pair_double * : print_list_pair_double(x),         \
         default: error("Unsupported operation")                        \
    )


DEFINE_LIST(int64_t)

DEFINE_LIST(double)

DEFINE_PAIR(double)

DEFINE_LIST(pair_double)

int main() {

    struct list_double ld1 = (struct list_double) {1.1, NULL};
    struct list_double ld2 = (struct list_double) {2.1, &ld1};
    struct list_double ld3 = (struct list_double) {3.1, &ld2};
    struct list_double ld4 = (struct list_double) {4.1, &ld3};


    struct list_int64_t li1 = (struct list_int64_t) {1, NULL};
    struct list_int64_t li2 = (struct list_int64_t) {2, &li1};
    struct list_int64_t li3 = (struct list_int64_t) {3, &li2};
    struct list_int64_t li4 = (struct list_int64_t) {4, &li3};


    struct list_pair_double lp1 = (struct list_pair_double) {(pair_double) {1.1, 1.1}, NULL};
    struct list_pair_double lp2 = (struct list_pair_double) {(pair_double) {2.1, 2.1}, &lp1};
    struct list_pair_double lp3 = (struct list_pair_double) {(pair_double) {3.1, 3.1}, &lp2};
    struct list_pair_double lp4 = (struct list_pair_double) {(pair_double) {4.1, 4.1}, &lp3};


    print_list_int64_t(&li4);
    print_list_double(&ld4);
    print_list_pair_double(&lp4);

    print(&li4);
    print(&ld4);
    print(&lp4);

    return 0;
}
