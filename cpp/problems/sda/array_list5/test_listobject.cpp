#include "ad_object.h"
//#include "ad_object.cpp"
#include "listobject.h"
#include "listobject.cpp"

void test_list_simple_implementation() {
    Ad_ListObject<ad_object::Ad_Object*> ad_lo;
    ad_object::Ad_IntObject *io = new ad_object::Ad_IntObject(5);
    ad_object::Ad_StringObject *so = new ad_object::Ad_StringObject("neata");

    ad_lo.Append(io);
    ad_lo.Append(so);

    ad_lo.TestPrint();
}