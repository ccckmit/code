

//======================== Structure =======================================
typedef struct {
  char 	*name;
  void  *value;
} Field;

typedef struct {
  short cSize, oSize;
  Field *cMembers, *oMembers;
} Class;

typedef struct {
  void **members;
} Obj;

typedef Obj* (*Method)(Obj*, Obj* p[], int);

#define FieldId short

#define DefMethod(f) 		Obj* f(Obj*, Obj* p[], int)
#define DefMethodAndPtr(f,fp)	Obj* f(Obj*, Obj* p[], int); Obj* (*fp)(Obj*, Obj* p[], int)=&f;

extern Class ObjClass;
extern Class StrClass;

//========================= Machine Dependent ===============================
#define Printf	printf
